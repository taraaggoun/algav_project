/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/uint128.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* -------------------------------- DEFINES --------------------------------- */

#define UINT64_STR_LEN_B16 16
// nombre de chiffres dans le nombre + 2 (0x) + 1 (\0)
#define UINT64_BUF_LEN_B16 UINT64_STR_LEN_B16 + 2 + 1

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

/** Renvoie 
 * 1  si cle1 > cle2
 * 0  si cle1 = cle2
 * -1 si cle1 < cle2
 **/
static int compare_uint64(uint64_t cle1, uint64_t cle2) {
	if (cle1 > cle2) return  1;
	if (cle1 < cle2) return -1;
	return 0;
}

/** Renvoie 
 * 1  si cle1 > cle2
 * 0  si cle1 = cle2
 * -1 si cle1 < cle2
 **/
static int compare(uint128_t cle1, uint128_t cle2) {
	int res = compare_uint64(cle1.i1, cle2.i1);
	if (res != 0)
		return res;

	res = compare_uint64(cle1.i2, cle2.i2);
	if (res != 0)
		return res;

	return 0;
}

// Convertie une chaine de caractere en uint32
static uint64_t str_to_uint64(char *str) {
	char *endptr = NULL;
	uint64_t res = strtoul(str, &endptr, 16);

	if (!(strcmp(str, "\0") != 0 && strcmp(endptr, "\0") == 0)) {
		dprintf(STDERR_FILENO, "Erreur invalide valeur\n");
		exit(EXIT_FAILURE);
	}
	return res;
}

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

bool inf(uint128_t cle1, uint128_t cle2) {
	return compare(cle1, cle2) == -1;
}

bool eg(uint128_t cle1, uint128_t cle2) {
	return compare(cle1, cle2) == 0;
}

void str_to_uint128(char *str, uint128_t *cle) {
	size_t len = strlen(str);
	int pos = (len - UINT64_STR_LEN_B16 > 1) ? len - UINT64_STR_LEN_B16 : 2;
	char buf[UINT64_BUF_LEN_B16] = { 0 };

	snprintf(buf, UINT64_BUF_LEN_B16, "0x%s", str + pos);
	cle->i2 = str_to_uint64(buf);
	pos = (pos - UINT64_STR_LEN_B16 > 1) ? pos - UINT64_STR_LEN_B16 : 2;

	memset(buf, 0, UINT64_BUF_LEN_B16);
	snprintf(buf, UINT64_BUF_LEN_B16, "0x%s", str + pos);
	cle->i1 = str_to_uint64(buf);
}

void uint128_to_str(uint128_t cle, char *str, size_t maxlen) {
	snprintf(str, maxlen, "%lu.%lu", cle.i1, cle.i2);
}

/* -------------------------------------------------------------------------- */