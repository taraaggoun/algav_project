/* -------------------------------- INCLUDE --------------------------------- */

#include "../include/MD5.h"

#include "test_utils.h"

/* -------------------------------- DEFINE ---------------------------------- */

#define BUFSIZE 4096

/* ---------------------------------- MAIN ---------------------------------- */

int main(int argc, char *argv) {
	char str[BUFSIZE] = { 0 };
	if (argc == 2)
		snprintf(str, strlen(argv[1]), "%s", argv[1]);
	else
		snprintf(str, 4, "test");
	uint128_t *u = MD5(str);
	char str[BUF_UINT128_LEN_B16] = { 0 };
	uint128_to_str(*u, str, BUF_UINT128_LEN_B16);
	printf("%s \n", str);
	return 0;
}

/* -------------------------------------------------------------------------- */