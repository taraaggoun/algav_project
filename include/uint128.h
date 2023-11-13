#pragma once

/* -------------------------------- INCLUDES -------------------------------- */

#include <stdint.h>
#include <stdbool.h>

/* -------------------------------- STRUCTURE ------------------------------- */

typedef struct uint128_t {
	uint32_t i1;
	uint32_t i2;
	uint32_t i3;
	uint32_t i4;
} uint128_t;

/* -------------------------------- FUNCTIONS ------------------------------- */

// Renvoie si cle1 < cle2
bool inf(uint128_t cle1, uint128_t cle2);

// Renvoie si cle1 = cle2
bool eg(uint128_t cle1, uint128_t cle2);

// Convertie une chaine de caratere en uint128
void str_to_uint128(char *str, uint128_t *cle);

// Convertie un uint128 en chaine de caractere
void uint128_to_str(uint128_t cle, char *str);

/* -------------------------------------------------------------------------- */