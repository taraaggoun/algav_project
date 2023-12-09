#include "profiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

static int out_fd = -1;

void begin_session(const char* filename)
{
	if (out_fd != -1) {
		printf("Erreur session en cours !");
		exit(3);
		return;
	}
	int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd < 0) {
		dprintf(STDERR_FILENO, "Erreur open");
		exit(EXIT_FAILURE);
	}

	out_fd = fd;
}

void end_session(void)
{
	close(out_fd);
	out_fd = -1;
}

#define ASSEZ_GRAND 256

void write_profile(ProfileResult result)
{
	char writebuf[ASSEZ_GRAND] = { 0 };
	double time = ((double) (result.end - result.start)) / (CLOCKS_PER_SEC / 1000);

	snprintf(writebuf, ASSEZ_GRAND, "%s %lu %f\n", result.name, result.size, time);

	if (write(out_fd, writebuf, strlen(writebuf)) < 0) {
		dprintf(STDERR_FILENO, "Erreur write");
		exit(EXIT_FAILURE);
	}
}

clock_t begin_profile()
{
	return clock();
}

void end_profile(const char* name, size_t size, clock_t start)
{
	clock_t end = clock();
	write_profile((ProfileResult){ name, size, start, end });
}
