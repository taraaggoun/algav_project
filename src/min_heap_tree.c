/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/min_heap_tree.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../graph/profiler.h"

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

/**
 * Echange les valeurs de deux noeud
*/
static void swap_node_value(mhtree_node *node1, mhtree_node *node2) {
	uint128_t *temp = node1->key;
	node1->key = node2->key;
	node2->key = temp;
}

/**
 * Renvoie si le tas est une feuille
*/
static bool is_leave(mhtree *h) {
	return h->left == NULL && h->right == NULL;
}

/**
 * Echange les noeud pour que l'arbre soit un tas, de la racine jusqu'au feuille
*/
static void swap_root_to_leave(mhtree *h) {
	if (mhtree_is_empty(h)) {
		dprintf(STDERR_FILENO, "Erreur: Tas vide dans swap_rtol\n");
		exit(EXIT_FAILURE);
	}

	if (is_leave(h)) return;

	// Test si le fils gauche est le fils le plus petit
	bool left_is_min;
	if (h->left == NULL) left_is_min = false;
	else {
		if (h->right == NULL) left_is_min = true;
		else left_is_min = inf(*(h->left->key), *(h->right->key));
	}

	// Test si la racine est plus petite que le min de ses fils
	bool root_is_min;
	if (left_is_min) {
		root_is_min = inf(*(h->key), *(h->left->key));
		if(!root_is_min) {
			swap_node_value(h, h->left);
			swap_root_to_leave(h->left);
		}
	}
	else {
		root_is_min = inf(*(h->key), *(h->right->key));
		if(!root_is_min) {
			swap_node_value(h, h->right);
			swap_root_to_leave(h->right);
		}
	}
}

/**
 * Echange les noeuds pour que l'arbre soit un tas
 * des feuilles jusqu'a la racine
*/
static void swap_leave_to_root(mhtree *h) {
	if (mhtree_is_empty(h)) {
		dprintf(STDERR_FILENO, "Erreur: Tas vide dans swap_rtol\n");
		exit(EXIT_FAILURE);
	}

	if(h->parent == NULL) // Si on est la racine
		return;

	bool parent_is_min;
	parent_is_min = inf(*(h->parent->key), *(h->key));
	if(!parent_is_min)
		swap_node_value(h, h->parent);

	swap_leave_to_root(h->parent);
}

/**
 * Mise a jour des pointeurs pour ajout d'un element
*/
static void maj_ptr(mhtree_node *new_node) {
	if (new_node->parent == NULL) return;

	// On rattache le fils à son parent
	if (new_node->parent->left == NULL)
		new_node->parent->left = new_node;
	else if (new_node->parent->right == NULL)
		new_node->parent->right = new_node;
	else { // Erreur : le parent a déjà deux enfants
        	dprintf(STDERR_FILENO, "Erreur: ajout pas possible\n");
        	exit(EXIT_FAILURE);
	}

	// MAJ des pointeurs du dernier ajouté et du père du prochain a ajouté
	mhtree_node *cur = new_node;
	mhtree_node *new_empty = new_node->parent;

	if (new_node->parent->right == NULL)
		new_empty = new_node->parent;

	else {
		new_empty = new_node->left;
		while(cur->parent != NULL && cur == cur->parent->right)
			cur = cur->parent;

		if(cur->parent != NULL) {
			cur = cur->parent->right;
			if(cur == NULL)
				new_empty = cur->parent;
		}
		while(cur->left != NULL)
			cur = cur->left;
		new_empty = cur;
	}
	cur = new_node;
	while(cur->parent != NULL) {
		cur->parent->last_leaf = new_node;
		new_node->parent->empty_leaf_parent = new_empty;
		cur = cur->parent;
	}
	cur->empty_leaf_parent = new_empty;
	new_node->empty_leaf_parent = new_empty;
}

/**
 * Crée un noeud d'un tas
 * de valeur k 
 * de parent parent
 * de fils gauche l
 * de fils droit r
*/
static mhtree_node* create_min_heap_leave(uint128_t k, mhtree_node *parent) {
	mhtree_node *new_node = (mhtree_node*) calloc(1, sizeof(mhtree_node));
	if (new_node == NULL) {
		dprintf(STDERR_FILENO, "Erreur: calloc creation noeud tas\n");
		exit(EXIT_FAILURE);
	}
	new_node->key = (uint128_t*) calloc(1, sizeof(uint128_t));
	if (new_node->key == NULL) {
		dprintf(STDERR_FILENO, "Erreur: calloc valeur noeud tas\n");
		exit(EXIT_FAILURE);
	}
	*(new_node->key) = k;
	new_node->right = NULL;
	new_node->left = NULL;
	new_node->parent = parent;
	new_node->last_leaf = new_node;
	new_node->empty_leaf_parent = new_node;
	maj_ptr(new_node);
	return new_node;
}

/**
 * Supprime le noeud et met a jours les pointeurs
*/
static void mhtree_remove_node(mhtree_node **h) {
	(*h)->empty_leaf_parent = (*h)->last_leaf->parent;
	// test si l'element a supprimé est l'enfant gauche
	bool supp_is_left = false;
	mhtree_node *supp = (*h)->last_leaf;
	// MAJ pointeur, last_leaf
	// Si fils droit de son pere, devient le fils gauche
	if((*h)->last_leaf == (*h)->last_leaf->parent->right)
		(*h)->last_leaf = (*h)->last_leaf->parent->left;
	else  { // Si je suis le fils gauche,
		supp_is_left = true;
		mhtree_node *cur = (*h)->last_leaf->parent;
		// On remonte au premier pere qui n'est pas un fils gauche
		while(cur->parent != NULL && cur == cur->parent->left)
			cur = cur->parent;
		// Si je ne suis pas a la racine
		if (cur != (*h)) {
			// Je vais chercher dans le frere a gauche
			cur = cur->parent->left;
			// Si je suis vide, je deviens le prochain a inserer
			if (mhtree_is_empty(cur))
				(*h)->last_leaf = cur;
			// Sinon je descend dans la feuille la plus a gauche
			while (!mhtree_is_empty(cur->right))
				cur = cur->right;
		}
		(*h)->last_leaf = cur;
	}
	// Libere la memoire du noeud
	mhtree_node *supp_parent = supp->parent;
	mhtree_free(supp);
	if (supp_is_left)
		supp_parent->left = NULL;
	else
		supp_parent->right = NULL;
}

/**
 * Renvoie la taille du tas
*/
static size_t mhtree_size(mhtree *h) {
	if (h == NULL)
		return 0;
	return mhtree_size(h->right) + mhtree_size(h->left) + 1;
}

/**
 * Transforme un tas (arbre) en tableau
*/
static void mhtree_to_tab(mhtree *h, uint128_t *tab, int *id) {
    if (!mhtree_is_empty(h)) {
        mhtree_to_tab(h->left, tab, id);

        tab[(*id)++] = *(h->key);

	mhtree_to_tab(h->right, tab, id);
    }
}

/**
 * Renvoie le nombre de noeud dans le tas
*/
static int nb_node(size_t index, size_t len) {
	if (index > len)
		return 0;
	return nb_node(2 * index + 1 ,len) + nb_node(2 * index + 2 ,len) + 1;
}


/**
 * Construit par recuturence un arbre binaire
*/
static mhtree* mhtree_construction_rec(uint128_t *v, size_t index, size_t len) {
	if (index > len)
		return NULL;

	mhtree *new_node = create_min_heap_leave(v[index], NULL);
	new_node->left = mhtree_construction_rec(v, 2 * index + 1 ,len);
	new_node->right = mhtree_construction_rec(v, 2 * index + 2, len);
	int nb_child_left = nb_node(2 * index + 1, len);
	int nb_child_right = nb_node(2 * index + 2, len);
	int prof_max_l = log2(nb_child_left);
	int prof_max_r = log2(nb_child_right);

	if (new_node->left != NULL) {
        	new_node->left->parent = new_node;
		new_node->last_leaf = new_node->left->last_leaf;
		new_node->empty_leaf_parent = new_node->left->empty_leaf_parent;
	}

	if (new_node->right != NULL) {
		new_node->right->parent = new_node;
		if (prof_max_l == prof_max_r)
			new_node->last_leaf = new_node->right->last_leaf;
		if (nb_child_left > nb_child_right)
			new_node->empty_leaf_parent = 
			new_node->right->empty_leaf_parent;
	}
	if (new_node->right == NULL)
		new_node->empty_leaf_parent = new_node;

	return new_node;
}

/**
 * transforme un arbre binaire en tas
*/
void bt_to_heap(mhtree *h) {
	if (mhtree_is_empty(h))
		return;

	if (h->right != NULL)
		bt_to_heap(h->right);
	if (h->left != NULL)
		bt_to_heap(h->left);
	swap_root_to_leave(h);
}

/**
 * Fonction d'affichage
*/
static void print_head (int depth, int addr) {
    if (depth > 1) {
	int pre = addr / 2;
	print_head (depth - 1, pre);
	printf ("%s", (pre % 2) != (addr % 2) ? "|    " : "     ");
	return;
    }
    if (depth == 1)
	printf ("     ");
}

#define BUF_UINT128_LEN_B10 38
static void print_rec(mhtree_node *h, int depth, int addr) {
    if (mhtree_is_empty(h)) {
	print_head(depth, addr);
	printf("|----N\n");
	return;
    }
    print_rec(h->right, depth + 1, 2 * addr + 1);
    print_head(depth, addr);
    char c = (depth == 0) ? '-' : '|';
    char buf[BUF_UINT128_LEN_B10] = { 0 };
    uint128_to_str(*(h->key), buf, BUF_UINT128_LEN_B10);
    printf("%c----%s\n", c, buf);
    print_rec(h->left, depth + 1, 2 * addr);
}

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

mhtree* mhtree_empty(void) {
	mhtree *new_heap = (mhtree *)calloc(1, sizeof(mhtree));
	if (new_heap == NULL) {
		dprintf(STDERR_FILENO, "Erreur: calloc creation noeud tas\n");
		exit(EXIT_FAILURE);
	}
	new_heap->last_leaf = new_heap;
	new_heap->empty_leaf_parent = new_heap;

	return new_heap;
}

void mhtree_free(mhtree *node) {
	if (node == NULL)
		return;
	mhtree_free(node->right);
	mhtree_free(node->left);
	free(node->key);
	free(node);
}

bool mhtree_is_empty(mhtree *h) {
	return h == NULL || h->key == NULL;
}

void mhtree_print (mhtree *h) {
	printf("\n");
	print_rec (h, 0, 0);
	printf("\n");
}

bool is_mhtree(mhtree *h) {
	if (h->left != NULL) {
		if (inf(*(h->left->key), *(h->key)) == true)
			return false;
		if (is_mhtree(h->left) == false)
			return false;
	}
	if (h->right != NULL) {
		if (inf(*(h->right->key), *(h->key)) == true)
			return false;
		if (is_mhtree(h->right) == false)
			return false;
	}
	return true;
}

uint128_t mhtree_suppr_min(mhtree **h) {
	if(mhtree_is_empty(*h)) {
		dprintf(STDERR_FILENO, "Erreur: Arbre vide dans SupprMin\n");
		exit(EXIT_FAILURE);
	}
	uint128_t k = *((*h)->key);
	if ((*h)->left == NULL && (*h)->right == NULL) {
		mhtree_free(*h);
		*h = mhtree_empty();
		return k;
	}
	*((*h)->key) = *((*h)->last_leaf->key);
	mhtree_remove_node(h);
	swap_root_to_leave(*h);
	return k;
}

void mhtree_ajout(uint128_t k, mhtree **h) {
	if (mhtree_is_empty(*h)) {
		free(*h); // On libere la memoire si tas alloué mais vide
		*h = create_min_heap_leave(k, NULL);
		return;
	}
	mhtree *new_node = create_min_heap_leave(k, (*h)->empty_leaf_parent);
	swap_leave_to_root(new_node);
}

void mhtree_ajout_iteratifs(uint128_t *k, size_t len, mhtree **h) {
	clock_t cl = BEGIN_PROFILE_FUNCTION();
	for (size_t i = 0; i < len; i++)
		mhtree_ajout(k[i], h);
	END_PROFILE_FUNCTION(len, cl);
}

mhtree* mhtree_construction(uint128_t *v, size_t len) {
	clock_t cl = BEGIN_PROFILE_FUNCTION();
	if (len == 0)
		return mhtree_empty();

	mhtree *res = mhtree_construction_rec(v, 0,  len - 1);
	bt_to_heap(res);

	END_PROFILE_FUNCTION(len, cl);

	return res;
}

mhtree* mhtree_union(mhtree *h1, mhtree *h2, int size) {
	clock_t cl = 0;
	if (size != -1) // Pour chronometrer pour les graphes
		cl = BEGIN_PROFILE_FUNCTION();

	if (mhtree_is_empty(h1))
		return h2;
	if (mhtree_is_empty(h2))
		return h1;
	size_t s = mhtree_size(h1) + mhtree_size(h2);
	uint128_t *tab = (uint128_t *) malloc(s * sizeof(uint128_t));
    	int id = 0;

    	mhtree_to_tab(h1, tab, &id);
    	mhtree_to_tab(h2, tab, &id);

	mhtree *res = mhtree_construction(tab, s);
	free(tab);

	if (size != -1)
		END_PROFILE_FUNCTION(size, cl); // graphes

	return res;
}

/* -------------------------------------------------------------------------- */
