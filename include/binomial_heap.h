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
*/
typedef struct binomial_heap {
	uint128_t *key;
	size_t degre;
	struct binomial_heap *childs;
} binomh;

/* -------------------------------- FUNCTIONS ------------------------------- */

/**
 * Cree un tournois binomiale vide
*/
binomh* binomh_create_empty();

/**
 * Crée un B1
*/
binomh* binomh_create(uint128_t k);

/**
 * Libere la memoire d'un tournois binomiale
*/
void binomh_free(binomh *bh);

/**
 * Test si un tournois binomiale est vide
*/
bool binomh_is_empty(binomh *bh);

/**
 * Fais l'union de deux tournois
*/
binomh* binomh_union(binomh *bh1, binomh *bh2);

/**
 * Affiche un tournois binomiale
*/
void binomh_print(binomh *bh);

/* -------------------------------------------------------------------------- */
