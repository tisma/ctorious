#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

static const char* const evval[3] = {
	"RELEASED",
	"PRESSED",
	"REPEATED"
};

int main(int argc, char const *argv[])
{
	const char* dev = "/dev/input/by-id/usb-Generic_USB_Keyboard-event-kbd";
	struct input_event ev;
	ssize_t n;
	int fd;

	fd = open(dev, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
		return EXIT_FAILURE;
	}

	do {
		n = read(fd, &ev, sizeof(ev));
		if (n == (ssize_t)-1) {
			if (errno == EINTR)
				continue;
			else
				break;
		} else if (n != sizeof(ev)) {
			errno = EIO;
			break;
		}
		if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2) {
			fprintf(stdout, "\t%s\t 0x%04x\t (%d)\n", evval[ev.value], (int)ev.code, (int)ev.code);
		}
	} while(1);

	fflush(stdout);
	fprintf(stderr, "%s.\n", strerror(errno));

	return EXIT_SUCCESS;
}

