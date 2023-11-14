/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/uint128.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* -------------------------------- DEFINES --------------------------------- */

#define UINT32_STR_LEN_B16 8
// nombre de chiffres dans le nombre en base 16 + 2 (0x) + 1 (\0)
#define UINT32_BUF_LEN_B16 UINT32_STR_LEN_B16 + 2 + 1

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

/** Renvoie 
 * 1  si cle1 > cle2
 * 0  si cle1 = cle2
 * -1 si cle1 < cle2
 **/
static int compare_uint32(uint32_t cle1, uint32_t cle2) {
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
	int res = compare_uint32(cle1.i1, cle2.i1);
	if (res != 0)
		return res;

	res = compare_uint32(cle1.i2, cle2.i2);
	if (res != 0)
		return res;

	res = compare_uint32(cle1.i3, cle2.i3);
	if (res != 0)
		return res;

	res = compare_uint32(cle1.i4, cle2.i4);
	if (res != 0)
		return res;

	return 0;
}

// Convertie une chaine de caractere en uint32
static int str_to_uint32(char *str) {
	char *endptr;
	uint32_t res = strtol(str, &endptr, 16);
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
	int str_pos = strlen(str) - UINT32_STR_LEN_B16;
	char buf[UINT32_BUF_LEN_B16] = { 0 };

	snprintf(buf, UINT32_BUF_LEN_B16, "0x%s", str + str_pos);
	cle->i1 = str_to_uint32(buf);
	str_pos -= (str_pos - UINT32_STR_LEN_B16 >= 2) ? UINT32_STR_LEN_B16 : 2;

	snprintf(buf, UINT32_BUF_LEN_B16, "0x%8s", str + str_pos);
	cle->i2 = str_to_uint32(buf);
	str_pos -= (str_pos - UINT32_STR_LEN_B16 >= 2) ? UINT32_STR_LEN_B16 : 2;

	snprintf(buf, UINT32_BUF_LEN_B16, "0x%8s", str + str_pos);
	cle->i3 = str_to_uint32(buf);
	str_pos -= (str_pos - UINT32_STR_LEN_B16 >= 2) ? UINT32_STR_LEN_B16 : 2;

	snprintf(buf, UINT32_BUF_LEN_B16, "0x%8s", str + str_pos);
	cle->i4 = str_to_uint32(buf);
}

void uint128_to_str(uint128_t cle, char *str) {
	sprintf(str, "%u.%u.%u.%u", cle.i1, cle.i2, cle.i3, cle.i4);
}

/* -------------------------------------------------------------------------- */