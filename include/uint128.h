#pragma once

/* -------------------------------- INCLUDES -------------------------------- */

#include <stddef.h> // size_t
#include <stdint.h> // uint64_t
#include <stdbool.h>

/* -------------------------------- STRUCTURE ------------------------------- */

/**
 * Structure unsigned int sur 128 bit
*/
typedef struct uint128_t {
	uint64_t high;
	uint64_t low;
} uint128_t;

/* -------------------------------- FUNCTIONS ------------------------------- */

/**
 * Renvoie si cle1 < cle2
*/
bool inf(uint128_t cle1, uint128_t cle2);

/**
 * Renvoie si cle1 = cle2
*/
bool eg(uint128_t cle1, uint128_t cle2);

/**
 * Convertie une chaine de caratere en uint128
*/
void str_to_uint128(char *str, uint128_t *cle);

/**
 * Convertie un uint128 en chaine de caractere
*/
void uint128_to_str(uint128_t cle, char *str, size_t maxlen);

/* -------------------------------------------------------------------------- */
