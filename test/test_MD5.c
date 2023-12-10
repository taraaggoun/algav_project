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
		snprintf(buf, 45, "Et l’unique cordeau des trompettes marinEs");
	uint128_t *u = MD5(buf);
	char str[BUF_UINT128_LEN_B16] = { 0 };
	uint128_to_str(*u, str, BUF_UINT128_LEN_B16);
	printf("%s \n", str);
	free(u);
	return 0;
}

/* -------------------------------------------------------------------------- */