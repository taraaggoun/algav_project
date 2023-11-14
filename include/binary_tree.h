#pragma once

/* -------------------------------- INCLUDE --------------------------------- */

#include "uint128.h"

/* -------------------------------- STRUCTURES ------------------------------ */

typedef union tree_value {
	uint128_t u128;
	char  str[128];
} tree_value;

typedef struct binary_tree {
	tree_value *val;
	struct binary_tree *left;
	struct binary_tree *right;
	struct binary_tree *parent;
} binary_tree;

/* -------------------------------- FUNCTIONS ------------------------------- */

// Renvoie l'arbre vide
binary_tree* ArbreVide(void);

/** Renvoie l'abre binaire qui a pour fils gauche l fils droit r et 
 *  en valeur de  racine v
 */
binary_tree* ArbreBinaire(const tree_value *v, binary_tree *l, binary_tree *r);

// Libere la memoire d'un arbre
void free_binary_tree(binary_tree *bt);

// Test si l'arbre est vide
bool EstVide(binary_tree *bt);

/* -------------------------------------------------------------------------- */