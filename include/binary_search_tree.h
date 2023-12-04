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
bst* create_bst_empty(void);

/**
 * Renvoie l'abr qui a pour valeur de racine k
 * et comme fils gauche: left et fils droit: right
*/
bst* create_bst(uint128_t k, bst *left, bst *right);

/**
 * Libere la memoire d'un abr
*/
void free_bst(bst *t);

/**
 * Renvoie si l'abr est un arbre vide
*/
bool is_bst_empty(bst *t);

/**
 * Renvoie le max de b
*/
bst* max_bst(bst *t);

/**
 * Renvoie le min de b
*/
bst* min_bst(bst *t);

/**
 * Renvoie si l'arbre est un abr
*/
bool is_bst(bst *t);

/**
 * Renvoie l'abr avec la valeur k ajouté
*/
bst* add_bst(uint128_t k, bst *t);

/**
 * Renvoie l'abr avec la valeur k supprimé
 * si il est pas dans l'arbre renvoie NULL
*/
bst* supp_bst(bst *t, uint128_t k);

/**
 * Cherche si k appartient a l'arbre
*/
bst* search_bst(bst *t, uint128_t k);

/**
 * fonction d'affichage.
*/
void print_bst (bst *t);

/* -------------------------------------------------------------------------- */