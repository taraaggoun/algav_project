#pragma once

/* -------------------------------- INCLUDE --------------------------------- */

#include "uint128.h"

/* -------------------------------- STRUCTURES ------------------------------ */

typedef union tree_value {
	uint128_t u128;
	char  str[128];
} tree_value;

typedef enum type {uint128, str} type;

typedef struct binary_tree {
	enum type type;
	tree_value *val;

	struct binary_tree *left;
	struct binary_tree *right;
	struct binary_tree *parent;
} binary_tree;

/* -------------------------------- FUNCTIONS ------------------------------- */

/**
 * Renvoie l'arbre vide
**/
binary_tree* bt_empty(void);

/** Renvoie l'abre binaire qui a pour fils gauche l fils droit r et 
 *  en valeur de racine v et de type t
**/
binary_tree* bt_new(tree_value v, type t, binary_tree *l, binary_tree *r);

/**
 * Libere la memoire d'un arbre
**/
void bt_free(binary_tree *bt);

/**
 * Test si l'arbre est vide
**/
bool bt_is_empty(binary_tree *bt);

/**
 * Construit un arbre binaire parfait
**/
binary_tree* bt_construction(tree_value *v, size_t len, type t);

/**
 * Convertie un arbre binaire parfait en tas
**/
void btp_to_mhtree(binary_tree *bt);

/* -------------------------------------------------------------------------- */