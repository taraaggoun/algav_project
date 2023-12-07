#pragma once

/* -------------------------------- INCLUDE --------------------------------- */

#include "uint128.h"
#include "tab_dynamique.h"

/* -------------------------------- FUNCTIONS ------------------------------- */

/**
 * Test si le tableau est un tas
*/
bool is_heap(table_dynamique *tas);

/**
 * Supprime le plus petit element du tas
*/
void mharray_suppr_min(table_dynamique *tas);

/**
 * Ajoute au tas avec l'élément
*/
void mharray_ajout(uint128_t cle, table_dynamique *tas);

/**
 * Rajoute au tas les elemennt de la liste
*/
void mharray_ajout_iteratif(uint128_t *listeElement,int len,table_dynamique *tas);

/**
 * Construit un tas
*/
void mharray_construction(table_dynamique *listeElement);

/**
 * Fais l'union de deux tas
*/
table_dynamique mharray_union(table_dynamique * A,table_dynamique * B);

/* -------------------------------------------------------------------------- */