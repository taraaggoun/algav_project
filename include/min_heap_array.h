#pragma once

/* -------------------------------- INCLUDE --------------------------------- */

#include "uint128.h"

/* -------------------------------- FUNCTIONS ------------------------------- */

/**
 * Test si le tableau est un tas
*/
bool is_heap(uint128_t *tas,int len);

/**
 * Supprime le plus petit element du tas
*/
void mharray_suppr_min(uint128_t *tas);

/**
 * Ajoute au tas avec l'élément
*/
void mharray_ajout(uint128_t element, uint128_t *tas);

/**
 * Rajoute au tas les elemennt de la liste
*/
void mharray_ajout_iteratif(uint128_t* listeElement, int len, uint128_t *tas);

/**
 * Construit un tas
*/
void mharray_construction(uint128_t *listeElement,int len);

/**
 * Fais l'union de deux tas
*/
uint128_t* mharray_union(uint128_t * A,uint128_t * B,int lenA,int lenB);

/* -------------------------------------------------------------------------- */
