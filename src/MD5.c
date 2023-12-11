#include <stdio.h>
/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/MD5.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

/**
 * Fonction de rotation vers la gauche
*/
static uint32_t leftrotate(uint32_t value, uint32_t shift) {
	return (value << shift) | (value >> (32 - shift));
}

/* ---------------------------- PUBLIC FUNCTION ----------------------------- */
 
uint128_t md5(char *str) {
	//Définir r comme suit :
	const uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7,
			      12, 17, 22, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9,
			      14, 20, 5,  9, 14, 20, 4, 11, 16, 23, 4, 11, 16,
			      23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21,
			      6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

	uint32_t h0 = 0x67452301;
	uint32_t h1 = 0xefcdab89;
	uint32_t h2 = 0x98badcfe;
	uint32_t h3 = 0x10325476;

	// MD5 utilise des sinus d'entiers pour ses constantes :
	uint32_t k[64] = { 0 };
	for (int i = 0; i < 64; i++)
		k[i] = floor(fabs(sin(i + 1)) * pow(2, 32));

	//Préparation du message (padding) :
	size_t str_len = strlen(str);
	size_t new_len;
    	for (new_len = str_len + 1; new_len % (512/8) != 448/8; new_len++)
        	;

	char *msg = calloc(1, new_len + 8);
	memcpy(msg, str, str_len);
	msg[str_len] = 0x80; // bit = 1
	uint64_t bit_len = (uint64_t)str_len * 8; // taille en bit
	memcpy(msg + new_len, &bit_len, sizeof(uint64_t));

	// Découpage en blocs de 512 bits :
	for(size_t i = 0; i < new_len; i += (512/8)) {
 		uint32_t w[16] = { 0 };
		for (int j = 0; j < 16; j++) {
			memcpy(&w[j], msg + (i * 512) + (j * sizeof(uint32_t)), sizeof(uint32_t));
		}

		uint32_t a = h0;
		uint32_t b = h1;
		uint32_t c = h2;
		uint32_t d = h3;

		// Boucle principale :
		for(int j = 0; j < 64; j++) {
			uint32_t f = 0;
			uint32_t g = 0;

			if (j < 16) {
				f = (b & c) | ((~b) & d);
				g = j;
			} else if (j < 32) {
				f = (d & b) | ((~d) & c);
				g = (5 * j + 1) % 16;
			} else if (j < 48) {
				f = b ^ c ^ d;
				g = (3 * j + 5) % 16;
			} else {
				f = c ^ (b | (~d));
				g = (7 * j) % 16;
			}
		
			uint32_t tmp = d;
			d = c;
			c = b;
			b = b + leftrotate((a + f + k[j] + w[g]), r[j]);
			a = tmp;
	
		}
	
		// ajouter le résultat au bloc précédent :
		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
    	}
	free(msg);

	// Inversement des bits
	h0 = ((h0 & 0xFF) << 24) | (((h0 >> 8) & 0xFF) << 16) |
	     (((h0 >> 16) & 0xFF) << 8) | (h0 >> 24);
	h1 = ((h1 & 0xFF) << 24) | (((h1 >> 8) & 0xFF) << 16) |
	     (((h1 >> 16) & 0xFF) << 8) | (h1 >> 24);
	h2 = ((h2 & 0xFF) << 24) | (((h2 >> 8) & 0xFF) << 16) |
	     (((h2 >> 16) & 0xFF) << 8) | (h2 >> 24);
	h3 = ((h3 & 0xFF) << 24) | (((h3 >> 8) & 0xFF) << 16) |
	     (((h3 >> 16) & 0xFF) << 8) | (h3 >> 24);

	uint128_t u = { 0 };
	u.high = ((uint64_t)h0 << 32) | h1;
	u.low = ((uint64_t)h2 << 32) | h3;
	return u;
}

/* -------------------------------------------------------------------------- */
