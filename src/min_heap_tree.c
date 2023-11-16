/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/min_heap_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

// Supprime le noeud et met a jours les pointeurs
static void mhtree_remove_node(min_heap_tree *h) {
	free_min_heap_tree(h->last_leave);
	h->last_leave = ArbreVide();
	h->leave_empty = h->last_leave;
	// Mettre a jours last_leave
	// Si je suis le fils droit de mon pere
	if(h->last_leave == h->last_leave->parent->right)
		h->last_leave = h->last_leave->parent->left;
	else  {// Si je suis le fils gauche,
		binary_tree *tmp = NULL;
		while()
		// je deviens le fils droit du frere de mon pere
		// h->last_leave = h->last_leave->parent->parent->right;
	}
}

// Echange les valeurs de deux noeud
static void rotation_node(binary_tree *bt1, binary_tree *bt2) {
	tree_value tmp = *(bt1->val);
	*(bt1->val) = *(bt2->val);
	*(bt2->val) = tmp;
}

// Echange les noeud pour que l'arbre soit un tas, de la racine jusqu'au feuille
static void rotation_rtol(binary_tree *bt) {
	if (bt_EstVide(bt)) {
		dprintf(STDERR_FILENO, "Erreur: L'arbre est vide dans rotation_rtol");
		exit(EXIT_FAILURE);
	}

	if (bt->left == NULL && bt->right == NULL)
		return;

	// Trouver qui est le min dans les deux fils
	bool left_is_min;
	if (bt_EstVide(bt->left)) left_is_min = false;
	else {
		if (bt_EstVide(bt->right)) left_is_min = true;
		else left_is_min = inf(bt->left->val->u128, bt->right->val->u128);
	}

	bool root_is_min;
	if (left_is_min) {
		root_is_min = inf(bt->val->u128, bt->left->val->u128);
		if(!root_is_min) {
			rotation_node(bt, bt->left);
			rotation_rtol(bt->left);
		}
	}
	else {
		root_is_min = inf(bt->val->u128, bt->right->val->u128);
		if(!root_is_min) {
			rotation_node(bt, bt->left);
			rotation_rtol(bt->right);
		}
	}
}

// Echange les noeud pour que l'arbre soit un tas, des feuilles jusqu'a la racine
static void rotation_ltor(binary_tree *bt) {
	if (bt_EstVide(bt)) {
		dprintf(STDERR_FILENO, "Erreur: L'arbre est vide dans rotation_rtol");
		exit(EXIT_FAILURE);
	}

	if(bt_EstVide(bt->parent)) // Si on est la racine
		return;

	bool parent_is_min;
	parent_is_min = inf(bt->parent->val->u128, bt->val->u128);
	if(!parent_is_min) {
		rotation_node(bt, bt->parent);
		rotation_rtol(bt->parent);
	}
}

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

min_heap_tree* tree_heap_empty(void) {
	min_heap_tree *h = calloc(1, sizeof(min_heap_tree));
	h->root = ArbreVide();
	h->last_leave = h->root;
	h->leave_empty = h->root;
	return h;
}

void free_min_heap_tree(min_heap_tree *h) {
	free_binary_tree(h->root);
	h->root = NULL;
	h->last_leave = NULL;
	h->leave_empty = NULL;
	free(h);
}

bool mhtree_EstVide(min_heap_tree *h) {
	return EstVide(h->root);
}

tree_value SupprMin(min_heap_tree *h) {
	if (mhtree_EstVide(h)) {
		dprintf(STDERR_FILENO, "Erreur: Pas de min a extraire dans SupprMin");
		exit(EXIT_FAILURE);
	}
	
	tree_value v = *(h->root->val);
	if (h->root == h->last_leave) { // Si arbre a un element
		free_min_heap_tree(h);
		h = ArbreVide();
		return v;
	}

	h->root->val = h->last_leave->val;
	mhtree_remove_node(h);
	rotation_rtol(h);

	return v;
}

void Ajout(tree_value v, min_heap_tree *h) {
	h->leave_empty = ArbreBinaire(v, NULL, NULL);
	rotation_ltor(h->leave_empty);

	// Mettre a jour leave_empty
	// Si je suis le fils gauche de mon pere
	if(h->leave_empty == h->leave_empty->parent->left)
		h->leave_empty = h->leave_empty->parent->left;
	else // Si je suis le fils droit,
		// je deviens le fils gauche du frere de mon pere
		// h->last_leave = h->last_leave->parent->parent->right;
}

void AjoutsIteratifs(tree_value *v, size_t len, min_heap_tree *h) {
	for (int i = 0; i < len; i++)
		Ajout(v[i], h);
}

int Construction(tree_value *v, size_t len, min_heap_tree *h) {
	return 0;
}

/* -------------------------------------------------------------------------- */