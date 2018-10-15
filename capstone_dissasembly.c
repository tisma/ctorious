#include <stdio.h>
#include <inttypes.h>
#include <capstone/capstone.h>

#define X86_CODE \
    "\x55\x48\x8b\x05\xb8\x13\x00\x00\xe9\x14\x9e\x08\x00\x45\x31\xe4"

int main(int argc, char* argv[])
{
	csh handle;
	cs_insn *insn;
	size_t count;
	int rc = 0;

	if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK) {
		return 1;
	}

	cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);

	count = cs_disasm(handle, (const uint8_t*) X86_CODE, sizeof(X86_CODE) - 1, 0x1000, 0, &insn);

	if (count > 0) {
		printf("count = %zu\n", count);
		for (size_t i = 0; i < count; i++) {
			printf("0x%"PRIx64": % - 6s %s\n", insn[i].address, insn[i].mnemonic, insn[i].op_str);
		}
		cs_free(insn, count);
	} else {
		puts("ERROR: Failed to dissasemble given code!\n");
		rc = 1;
	}

	cs_close(&handle);

	return rc;
}

