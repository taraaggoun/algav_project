/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/min_heap_array.h"
#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CAP_INIT 20
#define MIN_ALLOC 1/4
#define BUF_UINT128_LEN_B10 38
#define BUF_UINT128_LEN_B16 36

// int tab_len = 0;
// int tab_capacity = CAP_INIT;

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

// /**
//  *  Fonction qui permet de changer de valeur entre elle
//  */
// static void swapAB(uint128_t *a, uint128_t *b) {
// 	uint128_t tmp = *a;
// 	*a = *b;
// 	*b = tmp;
// }

// /**
//  * Fonction qui supprime la racine du tas et la remplace pas la dernière feuille
//  */
// static void supprTete(uint128_t **tas) {
// 	// La clé la plus petite d'un tas est à la racine, donc on la supprime
// 	// et on la remplace par le dernière clé du tas
// 	(*tas)[0] = (*tas)[tab_len - 1];

// 	//La taille du tableau diminue donc de 1
// 	tab_len--;

// 	// Réalloue la mémoire afin d'en libéré les case qu'on utilise plus
// 	// si le nombre de case occupé est inferieur a 1/4 de la capacité
// 	if (tab_len <= tab_capacity * MIN_ALLOC) {
// 		*tas = realloc(*tas, 2 * tab_len * sizeof(uint128_t));
// 		if (*tas == NULL) {
// 			dprintf(STDERR_FILENO, "Erreur realloc supprTete\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		tab_capacity = 2 * tab_len;
// 	}
// }

// /**
//  * Fonction qui insère une clé dans un tas
//  */ 
// static void insertCle(uint128_t cle, uint128_t **tas) {
// 	//La taille du tableau augmente donc de 1
// 	tab_len++;

// 	// Réalloue la mémoire afin de faire de la place dans le tas
// 	if (tab_len == tab_capacity) {
// 		*tas = realloc(*tas, 2 * tab_capacity * sizeof(uint128_t));
// 		if (tas == NULL) {
// 			dprintf(STDERR_FILENO, "Erreur realloc insertCle\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		memset(tas + tab_len, 0, tab_capacity - tab_len);
// 		tab_capacity *= 2;
// 	}

// 	//insère l'élément en fin du tableaux
// 	(*tas)[tab_len - 1] = cle;
// }

// /**
//  * Affiche une clé à la sortie
// */
// void print_cles(uint128_t cle) {
// 	char cle_tmp[BUF_UINT128_LEN_B10] = { 0 };
// 	uint128_to_str(cle, cle_tmp, BUF_UINT128_LEN_B10);
// 	printf(" %s ", cle_tmp);
// }

// /**
//  * Affiche un tableaux de clé à la sortie
// */
// void print_tass(uint128_t *tas, int taille) {
// 	printf("[\n");
// 	for(int i = 0 ; i < taille; i++) {
// 		print_cles(tas[i]);
// 		if(i == (taille - 1)) {
// 		} else {
// 			printf(";\n");
// 		}
// 	}
// 	printf("]\n");
// }

// /**
//  * Organise un arbre/sous_arbre en tas
// */
// static void remonteTas(uint128_t *tas,int i){
// 	int k = i;
// 	while(true) {
// 		int id_NodeP = k;
// 		int id_ChildL = 2 * id_NodeP + 1;
// 		int id_ChildR = 2 * id_NodeP + 2;
// 		// Compare avec le fils gauche
// 		if (id_ChildL < tab_len && inf(tas[id_ChildL], tas[id_NodeP])) {
// 		    id_NodeP = id_ChildL;
// 		}
// 		// Compare avec le fils droit
// 		if (id_ChildR < tab_len &&  inf(tas[id_ChildR], tas[id_NodeP])) {
// 			id_NodeP = id_ChildR;
// 		}

// 		// Si le plus grand n'est pas la racine
// 		if (id_NodeP != k) {
// 		    swapAB(&tas[k],&tas[id_NodeP]);
// 		    k = id_NodeP;
// 		    // Récursivement effectuer le heapify sur le sous-arbre affecté
// 		    //remonteTas(tas,id_NodeP);
// 		} else {
// 			break;
// 		}
// 	}
// }

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

// bool is_heap(uint128_t *tas,int len) {
// 	for (int i = len / 2 - 1; i >= 0; i--) {
// 		int id_NodeP = i;
// 		int id_ChildL = 2 * i + 1;
// 		int id_ChildR = 2 * i + 2;

// 		if (id_ChildL < len && inf(tas[id_ChildL], tas[id_NodeP])) {
//         		return false;
// 		}

// 		if (id_ChildR < len && inf(tas[id_ChildR], tas[id_NodeP])) {
// 			return false;
// 	    }
// 	}
// 	return true;
// }

// void mharray_suppr_min(uint128_t *tas) {
// 	supprTete(&tas);

// 	int i = 0;
// 	remonteTas(tas, i);
// }

// void mharray_ajout(uint128_t cle, uint128_t *tas) {
// 	insertCle(cle, &tas);

// 	if (tab_len <= 0) {
// 		fprintf(stderr, "Erreur de taille ajut min heap tab\n");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (tab_len == 1) return; // Si le tas a un element, c'est un tas

// 	// Si plus d'elements, il faut  s'assurer que c'est toujours un tas
// 	int i = tab_len - 1;

// 	while (i != 0) {
// 		int parent = (i % 2 == 1) ? (i - 1) / 2 : (i - 2) / 2;
// 		if (!inf(tas[parent], tas[i])) {
// 			swapAB(&tas[i], &tas[parent]);
//          		i = parent;
//         	} else
// 	            	break;
// 	}
// }

// void mharray_ajout_iteratif(uint128_t *listeElement, int len, uint128_t *tas) {
//     for(int i = 0; i < len; i++) {
//     	mharray_ajout(listeElement[i], tas);
//     }
// }

// void mharray_construction(uint128_t *listeElement, int len) {
// 	for (int i = len / 2 - 1; i >= 0; i--) {
// 	   remonteTas(listeElement,i);
// 	}
// }

// uint128_t * mharray_union(uint128_t * A,uint128_t * B,int lenA,int lenB) {
// 	uint128_t * tmp = A;
// 	printf("%d %d\n", lenA, lenB);
// 	for(int i = 0;i < lenB; i++) {
// 		insertCle(B[i], &tmp);
// 	}

// 	mharray_construction(tmp, lenA + lenB);
// 	return tmp;
// }

/* -------------------------------------------------------------------------- */

int main()  {
	return 0;
}