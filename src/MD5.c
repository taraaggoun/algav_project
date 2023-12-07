/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/MD5.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------- DEFINES --------------------------------- */

/**
 * Fonction de rotation vers la gauche
*/
static uint32_t leftrotate(uint32_t value, uint32_t shift) {
	return (value << shift) | (value >> (32 - shift));
}

/**
 * Verifie si la machine est en little-endian
*/
static bool is_little_endian() {
	uint32_t value = 0x12345678;
	uint8_t *byteArray = (uint8_t *)&value;
    	// Si le premier octet est 0x78, la machine est little-endian
    	if (byteArray[0] == 0x78)
        	return true; // Little-endian
        return false; // Big-endian
}

/**
 * Convertie un uint64 en little endian
*/
static uint64_t uint64_little(uint64_t u) {
	if(is_little_endian())
		return u;
	// Tableau d'octects
	uint8_t oct[8] = { 0 };
	for (int i = 0; i <  8; i++)
		oct[i] = (u >> (i * 8)) & 0xff;
	uint64_t res = 0;
	for (int i = 0; i < 8; i ++)
		res |= oct[i] << (i * 8);
	return res;
}

/**
 * Convertie un uint32 en little endian
*/
static uint32_t uint32_little(uint64_t u) {
	if(is_little_endian())
		return u;
	// Tableau d'octects
	uint8_t oct[4] = { 0 };
	for (int i = 0; i <  4; i++)
		oct[i] = (u >> (i * 8)) & 0xff;
	uint32_t res = 0;
	for (int i = 0; i < 4; i ++)
		res |= oct[i] << (i * 8);
	return res;
}

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

#include <stdio.h>
uint128_t* MD5(char *str) {
	//Définir r comme suit :
	uint32_t r[64] = {7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12,
			 17, 22, 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
			 5,  9, 14, 20, 4, 11, 16, 23,  4, 11, 16, 23,  4, 11,
			 16, 23,  4, 11, 16, 23, 6, 10, 15, 21,  6, 10, 15, 21,
			 6, 10, 15, 21, 6, 10, 15, 21};
	uint32_t k[64] = { 0 };
	uint32_t h0 = 0x67452301;
	uint32_t h1 = 0xEFCDAB89;
	uint32_t h2 = 0x98BADCFE;
	uint32_t h3 = 0x10325476;

	// MD5 utilise des sinus d'entiers pour ses constantes :
	for (int i = 0; i < 64; i++)
		k[i] = floor(fabs(sin(i + 1)) * pow(2, 32));

	//Préparation du message (padding) :
	size_t str_len = strlen(str);
	uint64_t taille = str_len * 8;
	int i = taille % 512;
	taille += i;
	char *message = calloc(1, (taille / 8) + sizeof(uint64_t) + 1);
	uint64_t taille_little = uint64_little(taille);
	memcpy(message, &taille_little, sizeof(uint64_t));
	strncpy(message + sizeof(uint64_t), str, str_len);
	message[str_len] = (char) (1 << 7);

	// Découpage en blocs de 512 bits :
	for (uint64_t i = 0; i < ((taille + 64) / 512); i ++) {
		uint32_t w[16] = { 0 };
		for (int j = 0; j < 16; j++) {
			memcpy(&w[j], message + (i * 512) + (j * sizeof(uint32_t)), sizeof(uint32_t));
			w[j] = uint32_little(w[j]);
		}

		// initialiser les valeurs de hachage :
		uint32_t a = h0;
		uint32_t b = h1;
		uint32_t c = h2;
		uint32_t d = h3;

		// Boucle principale :
		for (int j = 0; j < 64; j++) {
			uint32_t f = 0;
			uint32_t g = 0;
			if (j < 16) {
				f = (b & c) | ((~b) & d);
                		g = j;
			}
			if (j > 15 && j < 32) {
				f = (d & b) | ((~d) & c);
                		g = (5 * j + 1) % 16;
			}
			if (j > 31 && j < 48) {
				f = b ^ c ^ d; //xor
                		g = (3 * j + 5) % 16;
			}
			if (j > 47 && j < 64) {
				f = c ^ (b | (~d));
                		g = (7 * j) % 16;
			}
			uint32_t temp = d;
            		d = c;
            		c = b;
            		b = b + leftrotate((a + f + k[j] + w[g]), r[j]);
            		a = temp;
		}
		// ajouter le résultat au bloc précédent :
		h0 += a;
        	h1 += b;
        	h2 += c;
        	h3 += d;
	}
	uint128_t *u = calloc(1, sizeof(uint128_t));
	u->high = ((uint64_t)h3 << 32) | h2;
	u->high = uint64_little(u->high);
	u->low  = ((uint64_t)h1 << 32) | h0;
	u->low = uint64_little(u->low);
	free(message);
	return u;
}

/* -------------------------------------------------------------------------- */
