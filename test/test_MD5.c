/* -------------------------------- INCLUDE --------------------------------- */

#include "../include/MD5.h"

#include <string.h>

#include "test_utils.h"

/* -------------------------------- DEFINE ---------------------------------- */

#define BUFSIZE 4096

/* ---------------------------------- MAIN ---------------------------------- */

int main(int argc, char **argv) {
	char buf[BUFSIZE] = { 0 };
	if (argc == 2)
		snprintf(buf, strlen(argv[1]), "%s", argv[1]);
	else
		snprintf(buf, 45, "Et l’unique cordeau des trompettes marines");
	uint128_t u = md5(buf);
	printf("md5(%s) = %lx%lx\n", buf, u.high, u.low);

	snprintf(buf, 45, "Et l’unique cordeau des trompettes marinEs");
	u = md5(buf);
	printf("md5(%s) = %lx%lx\n", buf, u.high, u.low);

	return 0;
}

/* -------------------------------------------------------------------------- */
