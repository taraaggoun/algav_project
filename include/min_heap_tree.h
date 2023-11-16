#pragma once

/* -------------------------------- INCLUDE --------------------------------- */

#include "binary_tree.h"

/* ------------------------------- STRUCTURES ------------------------------- */

typedef struct min_heap_tree {
	binary_tree *root;
	binary_tree *last_leave; // pointe vers la derniere feuille rempli
	binary_tree *leave_empty; // pointe vers la premiere feuille vide
} min_heap_tree;

/* -------------------------------- FUNCTIONS ------------------------------- */

// Renvoie le tas vide
min_heap_tree* tree_heap_empty(void);

// Libere la memoire d'un tas
void free_min_heap_tree(min_heap_tree *h);

// Test si le tas est vide
bool mhtree_EstVide(min_heap_tree *h);

// Supprime le minimum du tas
tree_value SupprMin(min_heap_tree *h);

// Ajoute v dans me tas
void Ajout(tree_value v, min_heap_tree *h);

// Ajoute au tas toutes les clé contenue dans v
int AjoutsIteratifs(tree_value *v, size_t v_len, min_heap_tree *h);

// Construit un tas a partir des clé contenue dans v
int Construction(tree_value *v, size_t v_len, min_heap_tree *h);

/* -------------------------------------------------------------------------- */