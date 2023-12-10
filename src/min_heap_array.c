/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/min_heap_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../graph/profiler.h"

/* -------------------------------- DEFINES --------------------------------- */

#define BUF_UINT128_LEN_B10 38
#define BUF_UINT128_LEN_B16 36

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

/*
 *  Fonction qui permet de changer de valeur entre elle
 */
static void interchangerAB(uint128_t *a, uint128_t *b) {
	uint128_t tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
 * Fonction qui supprime la racine du tas et la remplace pas la dernière feuille
 */
static void supprTete(table_dynamique *tas) {
	/*La clé la plus petite d'un tas est à la racine, donc on la supprime
	 *et on la remplace par le dernière clé du tas
	 * */
	tas->data[0] = tas->data[tas->size - 1];

	supprElementInd(tas,tas->size - 1);
}

/**
 *  Affiche une clé à la sortie 
*/
void print_cles(uint128_t cle) {
	char cle_tmp[BUF_UINT128_LEN_B10] = { 0 };
	uint128_to_str(cle, cle_tmp, BUF_UINT128_LEN_B10);
	printf(" %s ", cle_tmp);
}

/**
 * Affiche un tableaux de clé à la sortie
*/
void print_tas(uint128_t *tas, int taille) {
	printf("[\n");
	for(int i = 0 ; i < taille; i++) {
		print_cles(tas[i]);
		if(i != (taille - 1))
			printf(";\n");
	}
	printf("]\n");
}

/**
 *  Organise un arbre/sous_arbre en tas 
*/
static void remonteTas(table_dynamique *tas,int i){
	int k = i;

	while (true) {
		int id_NodeP = k;
		int id_ChildL = 2 * id_NodeP + 1;
		int id_ChildR = 2 * id_NodeP + 2;

		// Compare avec le fils gauche
		if (id_ChildL < tas->size && inf(tas->data[id_ChildL], tas->data[id_NodeP]))
		    id_NodeP = id_ChildL;

		// Compare avec le fils droit
		if (id_ChildR < tas->size &&  inf(tas->data[id_ChildR], tas->data[id_NodeP]))
			id_NodeP = id_ChildR;

		// Si le plus grand n'est pas la racine
		if (id_NodeP != k) {
		    interchangerAB(&tas->data[k],&tas->data[id_NodeP]);
		    k = id_NodeP;
		} else
			break;
	}
}

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

bool is_heap(table_dynamique *tas) {
	for (int i = tas->size / 2 - 1; i >= 0; i--) {
		int id_NodeP = i;
		int id_ChildL = 2 * i + 1;
		int id_ChildR = 2 * i + 2;

		if (id_ChildL < tas->size && inf(tas->data[id_ChildL], tas->data[id_NodeP]))
            		return false;

		if (id_ChildR < tas->size && inf(tas->data[id_ChildR],tas->data[id_NodeP]))
			return false;
	}
	return true;
}

void mharray_suppr_min(table_dynamique *tas) {
	supprTete(tas);

	int i = 0;

	remonteTas(tas,i);
}

void mharray_ajout(uint128_t cle, table_dynamique *tas) {
	addElement(tas,cle);

	if (tas->size <= 0) {
		dprintf(STDERR_FILENO, "Erreur de taille ajout min heap tab\n");
		exit(EXIT_FAILURE);
	}

	if (tas->size == 1) return; // Si le tas a un element, c'est un tas

	// Si plus d'elements, il faut  s'assurer que c'est toujours un tas
	int i = tas->size - 1;

	while (i != 0) {
		int parent = (i % 2 == 1) ? (i - 1) / 2 : (i - 2) / 2;
		if (!inf(tas->data[parent], tas->data[i])) {
			interchangerAB(&tas->data[i], &tas->data[parent]);
         		i = parent;
        	} else
        		break;
	}
}

void mharray_ajout_iteratif(uint128_t *listeElement, int len, table_dynamique *tas) {
	clock_t cl = BEGIN_PROFILE_FUNCTION();
	for(int i = 0; i < len; i++)
    		mharray_ajout(listeElement[i], tas);
	END_PROFILE_FUNCTION(len, cl);
}

void mharray_construction(table_dynamique *listeElement) {
	clock_t cl = BEGIN_PROFILE_FUNCTION();
	for (int i = listeElement->size / 2 - 1; i >= 0; i--)
	   remonteTas(listeElement, i);
	END_PROFILE_FUNCTION(listeElement->size, cl);
}

table_dynamique mharray_union(table_dynamique *A,table_dynamique *B) {
	clock_t cl = BEGIN_PROFILE_FUNCTION();
	table_dynamique res;
	constTabDyn(&res, A->size + B->size);
	for(int i = 0; i < A->size; i++)
		addElement(&res, A->data[i]);
	for(int i = 0; i < B->size; i++)
		addElement(&res,B->data[i]);

	mharray_construction(&res);

	END_PROFILE_FUNCTION(A->size + B->size, cl);

	return res;
}

/* -------------------------------------------------------------------------- */
