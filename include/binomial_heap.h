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
	size_t degree;
	struct binomial_heap **children;
} binomh;

/* -------------------------------- FUNCTIONS ------------------------------- */

/**
 * Cree un tournois binomiale vide
*/
binomh* binomh_create_empty();

/**
 * Crée un B0
*/
binomh* binomh_create(uint128_t k);

/**
 * Test si un tournois binomiale est vide
*/
bool binomh_is_empty(binomh *bh);

/**
 * Affiche un tas
*/
void binomh_print(binomh *bh);

/**
 * Fais l'union de deux tournois
*/
binomh* binomh_union(binomh *bh1, binomh *bh2);

/**
 * Renvoie la copie d'un tas binomiale
 * si more child est vrai alloue de l'espace pour 
 * un fils de plus
*/
binomh* binomh_copy(binomh *bh, bool more_child);

/**
 * Libere la memoire d'un tournois binomiale
*/
void binomh_free(binomh *bh);

/**
 * Cree un tas binomiale Bk a partir d'une liste de cles
*/
binomh* binomh_createK(size_t k, uint128_t *list);

/**
 * Test si c'est un tas binomiale
*/
bool isBinomialHeap(binomh *heap);

/* -------------------------------------------------------------------------- */
