#pragma once

/* -------------------------------- INCLUDES -------------------------------- */

#include "uint128.h"

/* -------------------------------- STRUCTURE ------------------------------- */

typedef struct binary_search_tree {
	uint128_t *key;
	struct binary_search_tree *left;
	struct binary_search_tree *right;
} bst;

/* -------------------------------- FUNCTIONS ------------------------------- */

/**
 * Renvoie l'arbre binaire de recherche vide
*/
bst* bst_create_empty(void);

/**
 * Renvoie l'abr qui a pour valeur de racine k
 * et comme fils gauche: left et fils droit: right
*/
bst* bst_create(uint128_t k, bst *left, bst *right);

/**
 * Libere la memoire d'un abr
*/
void bst_free(bst *t);

/**
 * Renvoie si l'abr est un arbre vide
*/
bool bst_is_empty(bst *t);

/**
 * Renvoie le max de b
*/
bst* bst_max(bst *t);

/**
 * Renvoie le min de b
*/
bst* bst_min(bst *t);

/**
 * Renvoie si l'arbre est un abr
*/
bool is_bst(bst *t);

/**
 * Renvoie l'abr avec la valeur k ajouté
*/
bst* bst_add(uint128_t k, bst *t);

/**
 * Renvoie l'abr avec la valeur k supprimé
 * si il est pas dans l'arbre renvoie NULL
*/
bst* bst_supp(bst *t, uint128_t k);

/**
 * Cherche si k appartient a l'arbre
*/
bst* bst_search(bst *t, uint128_t k);

/**
 * fonction d'affichage.
*/
void bst_print (bst *t);

/* -------------------------------------------------------------------------- */
