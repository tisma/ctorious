#include <err.h>
#include <fcntl.h>
#include <linux/kvm.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	const uint8_t code[] = {
		0xba, 0xf8, 0x03,		// mov $0x3f8, %dx
		0x00, 0xd8,				// add %bl, %al
		0x04, '0',				// add $'0', %al
		0xee,					// out %al, (%dx)
		0xb0, '\n',				// mov $'\n', %al
		0xee,					// out %al, (%dx)
		0xf4,					// hlt
	};

	int kvm, vmfd, vcpufd, ret;

	uint8_t *mem;
	struct kvm_sregs sregs;
	struct kvm_run *run;
	size_t mmap_size;

	kvm = open("/dev/kvm", O_RDWR | O_CLOEXEC);
	if (kvm == -1)
		err(1, "/dev/kvm");

	ret = ioctl(kvm, KVM_GET_API_VERSION, NULL);
	if (ret == -1)
		err(1, "KVM_GET_API_VERSION");
	if (ret != 12)
		errx(1, "KVM_GET_API_VERSION %d, expected 12", ret);

	vmfd = ioctl(kvm, KVM_CREATE_VM, (unsigned long)0);
	if (vmfd == -1)
		err(1, "KVM_CREATE_VM");

	mem = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (!mem)
		err(1, "allocating guest memory");
	memcpy(mem, code, sizeof(code));

	struct kvm_userspace_memory_region region = {
		.slot = 0,
		.guest_phys_addr = 0x1000,
		.memory_size = 0x1000,
		.userspace_addr = (uint64_t)mem,
	};

	ret = ioctl(vmfd, KVM_SET_USER_MEMORY_REGION, &region);
	if (ret == -1)
		err(1, "KVM_SET_USER_MEMORY_REGION");

	vcpufd = ioctl(vmfd, KVM_CREATE_VCPU, (unsigned long)0);
	if (vcpufd == -1)
		err(1, "KVM_CREATE_VCPU");

	mmap_size = ioctl(kvm, KVM_GET_VCPU_MMAP_SIZE, NULL);
	if (mmap_size == -1)
		err(1, "KVM_GET_VCPU_MMAP_SIZE");

	if (mmap_size < sizeof(*run))
		errx(1, "KVM_GET_VCPU_MMAP_SIZE unexpectedly small");

	run = mmap(NULL, mmap_size, PROT_READ | PROT_WRITE, MAP_SHARED, vcpufd, 0);
	if (!run)
		err(1, "mmap vcpu");

	ret = ioctl(vcpufd, KVM_GET_SREGS, &sregs);
	if (ret == -1)
		err(1, "KVM_GET_SREGS");

	sregs.cs.base = 0;
	sregs.cs.selector = 0;
	ret = ioctl(vcpufd, KVM_SET_REGS, &sregs);
	if (ret == -1)
		err(1, "KVM_SET_REGS");

	struct kvm_regs regs = {
		.rip = 0x1000,
		.rax = 2,
		.rbx = 2,
		.rflags = 0x2,
	};

	ret = ioctl(vcpufd, KVM_SET_REGS, &regs);
	if (ret == -1)
		err(1, "KVM_SET_REGS");

	while (1) {
		ret = ioctl(vcpufd, KVM_RUN, NULL);
		if (ret == -1)
			err(1, "KVM_RUN");
		switch (run->exit_reason) {
		case KVM_EXIT_HLT:
			puts("KVM_EXIT_HLT");
			return 0;
		case KVM_EXIT_IO:
			if (run->io.direction == KVM_EXIT_IO_OUT && run->io.size == 1 && run->io.port == 0x3f8 && run->io.count == 1)
				putchar(*(((char*)run) + run->io.data_offset));
			else
				errx(1, "unhandled KVM_EXIT_IO");
			break;
		case KVM_EXIT_FAIL_ENTRY:
			errx(1, "KVM_EXIT_FAIL_ENTRY: hardware_entry_failure_reason = 0x%llx",
				(unsigned long long)run->fail_entry.hardware_entry_failure_reason);
		case KVM_EXIT_INTERNAL_ERROR:
			errx(1, "KVM_EXIT_INTERNAL_ERROR: suberror = 0x%x", run->internal.suberror);
		default:
			errx(1, "exit_reason = 0x%x", run->exit_reason);
		}
	}
}
