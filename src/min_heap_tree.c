/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/min_heap_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/utils.h"

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

/**
 * Echange les valeurs de deux noeud
**/
static void swap_node_value(binary_tree *bt1, binary_tree *bt2) {
	tree_value tmp = *(bt1->val);
	*(bt1->val) = *(bt2->val);
	*(bt2->val) = tmp;
}

/**
 * Echange les noeud pour que l'arbre soit un tas, de la racine jusqu'au feuille
**/
static void swap_root_to_leave(binary_tree *bt) {
	if (bt_is_empty(bt)) {
		dprintf(STDERR_FILENO, "Erreur: L'arbre est vide dans rotation_rtol");
		exit(EXIT_FAILURE);
	}

	if (bt->left == NULL && bt->right == NULL)
		return;

	// Trouver qui est le min dans les deux fils
	bool left_is_min;
	if (bt_is_empty(bt->left)) left_is_min = false;
	else {
		if (bt_is_empty(bt->right)) left_is_min = true;
		else left_is_min = is_inf(*(bt->left->val), *(bt->right->val), bt->type);
	}

	bool root_is_min;
	if (left_is_min) {
		root_is_min = is_inf(*(bt->val), *(bt->left->val), bt->type);
		if(!root_is_min) {
			swap_node_value(bt, bt->left);
			swap_root_to_leave(bt->left);
		}
	}
	else {
		root_is_min = is_inf(*(bt->val), *(bt->right->val), bt->type);
		if(!root_is_min) {
			swap_node_value(bt, bt->left);
			swap_root_to_leave(bt->right);
		}
	}
}

/**
 * Echange les noeud pour que l'arbre soit un tas, des feuilles jusqu'a la racine
**/
static void swap_leave_to_root(binary_tree *bt) {
	if (bt_is_empty(bt)) {
		dprintf(STDERR_FILENO, "Erreur: L'arbre est vide dans rotation_rtol");
		exit(EXIT_FAILURE);
	}

	if(bt_is_empty(bt->parent)) // Si on est la racine
		return;

	bool parent_is_min;
	parent_is_min = is_inf(*(bt->parent->val), *(bt->val), bt->type);
	if(!parent_is_min) {
		swap_node_value(bt, bt->parent);
		swap_leave_to_root(bt->parent);
	}
}

/**
 * Supprime le noeud et met a jours les pointeurs
**/
static void mhtree_remove_node(min_heap_tree *h) {
	// Libere la memoire du noeud
	bt_free(h->last_leave);
	// Remplace par l'arbre vide
	h->last_leave = bt_empty();
	h->empty_leave = h->last_leave;
	// MAJ pointeur, last_leave
	// Si fils droit de son pere, devient le fils gauche
	if(h->last_leave == h->last_leave->parent->right)
		h->last_leave = h->last_leave->parent->left;
	else  { // Si je suis le fils gauche,
		binary_tree *cur = h->last_leave->parent;
		// On remonte au premier pere qui n'est pas un fils gauche
		while(cur == cur->parent->left)
			cur = cur->parent;
		// Si je ne suis pas a la racine
		if (cur != h->root) {
			// Je vais chercher dans le frere a gauche
			cur = cur->parent->left;
			// Si je suis vide, je deviens le prochain a inserer
			if (bt_is_empty(cur))
				h->last_leave = cur;
			// Sinon je descend dans la feuille la plus a gauche
			while (!bt_is_empty(cur->right))
				cur = cur->right;
		}
		h->last_leave = cur;
	}
}

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

min_heap_tree* mhtree_empty(void) {
	min_heap_tree *h = calloc(1, sizeof(min_heap_tree));
	h->root = bt_empty();
	h->last_leave = h->root;
	h->empty_leave = NULL;
	return h;
}

void mhtree_free(min_heap_tree *h) {
	bt_free(h->root);
	h->root->val = NULL;
	h->last_leave = NULL;
	h->empty_leave = NULL;
	// free(h);
}

bool mhtree_is_empty(min_heap_tree *h) {
	return bt_is_empty(h->root);
}

tree_value SupprMin(min_heap_tree *h) {
	if (mhtree_is_empty(h)) {
		dprintf(STDERR_FILENO, "Erreur: Arbre vide dans SupprMin");
		exit(EXIT_FAILURE);
	}

	tree_value v = *(h->root->val);
	if (h->root == h->last_leave) { // Si arbre a un element
		mhtree_free(h);
		h = mhtree_empty(); // h devient l'arbre vide
		return v;
	}

	h->root->val = h->last_leave->val;
	mhtree_remove_node(h);
	swap_root_to_leave(h->root);

	return v;
}

void Ajout(tree_value v, type t, min_heap_tree *h) {
	// Ajoute un nouveau noeud en feuille
	binary_tree *parent = NULL;
	if (h->empty_leave != NULL) {
		parent = h->empty_leave->parent;
		bt_free(h->empty_leave);
	}
	h->empty_leave = bt_new(v, t, NULL, NULL);
	h->empty_leave->parent = parent;
	h->last_leave = h->empty_leave;

	if (mhtree_is_empty(h)) {
		free(h->root);
		h->root = h->empty_leave;
		h->empty_leave = h->root->left;
		return;
	}

	swap_leave_to_root(h->last_leave);

	// MAJ pointeur, empty_leave
	// Si fils gauche de son pere, devient fils droit
	if(h->empty_leave == h->empty_leave->parent->left)
		h->empty_leave = h->empty_leave->parent->right;
	else { // Si fils droit
		binary_tree *cur = h->empty_leave->parent;
		// Tant que je suis le fils droit de mon pere
		while(cur == cur->parent->right)
			cur = cur->parent;
		// Si je ne suis pas a la racine
		if (cur != h->root) {
			cur = cur->parent->right;
			// Si je suis vide, je deviens le prochain a inserer
			if (bt_is_empty(cur))
				h->empty_leave = cur;
			// Sinon je descend dans la feuille la plus a droite
			while (!bt_is_empty(cur->left))
				cur = cur->left;
		}
		h->empty_leave = cur;
	}
}

void AjoutsIteratifs(tree_value *v, type t, size_t len, min_heap_tree *h) {
	for (int i = 0; i < len; i++)
		Ajout(v[i], t, h);
}

min_heap_tree* Construction(tree_value *v, size_t len, type t) {
	if (len == 0) {
		return mhtree_empty();
	}
	min_heap_tree *res = mhtree_empty();
	bt_free(res->root);
	res ->root = bt_construction(v, len, t);

	btp_to_mhtree(res->root);
	// mettre a jours les pointeur;
	return res;
}

/* -------------------------------------------------------------------------- */