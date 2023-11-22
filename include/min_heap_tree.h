#pragma once

/* -------------------------------- INCLUDE --------------------------------- */

#include "binary_tree.h"

/* ------------------------------- STRUCTURES ------------------------------- */

typedef struct min_heap_tree {
	binary_tree *root;
	binary_tree *last_leave; // pointe vers la derniere feuille rempli
	binary_tree *empty_leave; // pointe vers la premiere feuille vide
} min_heap_tree;

/* -------------------------------- FUNCTIONS ------------------------------- */

/**
 * Renvoie le tas vide
**/
min_heap_tree* mhtree_empty(void);

/**
 * Libere la memoire d'un tas
**/
void mhtree_free(min_heap_tree *h);

/**
 * Test si le tas est vide
**/
bool mhtree_is_empty(min_heap_tree *h);

/**
 * Supprime le minimum du tas
**/
tree_value SupprMin(min_heap_tree *h);

/**
 * Ajoute v de type t dans le tas h
**/
void Ajout(tree_value v, type t, min_heap_tree *h);

/**
 * Ajoute au tas len clés contenue dans v de type t
**/
void AjoutsIteratifs(tree_value *v, type t, size_t len, min_heap_tree *h);

/**
 * Construit un tas a partir des clé contenue dans v
**/
min_heap_tree* Construction(tree_value *v, size_t len, type t);

/* -------------------------------------------------------------------------- */