#pragma once

/* -------------------------------- INCLUDES -------------------------------- */

#include "uint128.h"

/* -------------------------------- STRUCTURE ------------------------------- */

/**
 * Noeud d'un tas min binaire, contenant:
 * la valeur: key, entier codée sur 128 bits
 * un pointeur vers le fils droit: right
 * un pointeur vers le fils gauche: left
 * un pointeur vers le parent: parent
 * un pointeur vers la derniere feuille ajouter: last_leaf
 * un pointeur vers le pere de l'endroit ou on doit ajouter le prochain element
*/
typedef struct MinHeapTreeNode {
	uint128_t *key;

	struct MinHeapTreeNode *right;
	struct MinHeapTreeNode *left;

	struct MinHeapTreeNode *parent;
	struct MinHeapTreeNode *last_leaf;
	struct MinHeapTreeNode *empty_leaf_parent;
} mhtree_node;

typedef mhtree_node mhtree;

/* -------------------------------- FUNCTIONS ------------------------------- */

/**
 * Crée un tas vide
*/
mhtree* mhtree_empty(void);

/**
 * Libere la memoire d'un tas
*/
void mhtree_free(mhtree *node);

/**
 * Test si le tas est vide
*/
bool mhtree_is_empty(mhtree *h);

/**
 * Affiche un Tas
*/
void mhtree_print(mhtree *h);

/**
 * Test si l'arbre est un tas
*/
bool is_mhtree(mhtree *h);

/**
 * Supprime le min du tas
*/
uint128_t mhtree_suppr_min(mhtree **h, size_t size);

/**
 * Ajoute au tas, un element
*/
void mhtree_ajout(uint128_t k, mhtree **h, size_t size);

/**
 * Ajoute au tas, len elements
*/
void mhtree_ajout_iteratifs(uint128_t *k, size_t len, mhtree **h);

/**
 * Construit un arbre a partir des elements de la liste
*/
mhtree* mhtree_construction(uint128_t *v, size_t len);

/**
 * Fais l'union des deux tas
*/
mhtree* mhtree_union(mhtree *h1, mhtree *h2, int size);

/* -------------------------------------------------------------------------- */
