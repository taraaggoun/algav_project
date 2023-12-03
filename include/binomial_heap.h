#pragma once

/* -------------------------------- INCLUDES -------------------------------- */

#include "uint128.h"

/* -------------------------------- STRUCTURE ------------------------------- */

/**
 *  Noeud d'un tas binomiale contenant:
 * la valeur: key, encodée sur 128 bits
 * le degres de l'arbre: degre
 * un pointeur vers ses fils: childs
 * un pointeur vers ses freres: siblings
**/
typedef struct binomial_heap {
	uint128_t key;
	size_t degre;
	struct binomial_heap *childs;
	struct binomial_heap *siblings;
} binomh;

/* -------------------------------- FUNCTIONS ------------------------------- */

/* -------------------------------------------------------------------------- */
