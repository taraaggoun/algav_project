/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/tprioritetab.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CAP_INIT 20
#define MIN_ALLOC 1/4

int tab_len = 0;
int tab_capacity = CAP_INIT;

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
static void supprTete(uint128_t **tas) {
	// La clé la plus petite d'un tas est à la racine, donc on la supprime
	// et on la remplace par le dernière clé du tas
	(*tas)[0] = (*tas)[tab_len - 1];

	//La taille du tableau diminue donc de 1
	tab_len--;

	// Réalloue la mémoire afin d'en libéré les case qu'on utilise plus
	// si le nombre de case occupé est inferieur a 1/4 de la capacité
	if (tab_len <= tab_capacity * MIN_ALLOC) {
		*tas = realloc(*tas, 2 * tab_len * sizeof(uint128_t));
		if (*tas == NULL) {
			dprintf(STDERR_FILENO, "Erreur realloc supprTete\n");
			exit(EXIT_FAILURE);
		}
		tab_capacity = 2 * tab_len;
	}
}

/*
 * Fonction qui insère une clé dans un tas
 */
static void insertCle(uint128_t cle, uint128_t **tas) {
	//La taille du tableau augmente donc de 1
	tab_len++;

	// Réalloue la mémoire afin de faire de la place dans le tas
	if (tab_len == tab_capacity) {
		*tas = realloc(*tas, 2 * tab_capacity * sizeof(uint128_t));
		if (tas == NULL) {
			dprintf(STDERR_FILENO, "Erreur realloc insertCle\n");
			exit(EXIT_FAILURE);
		}
		memset(tas + tab_len, 0, tab_capacity - tab_len);
		tab_capacity *= 2;
	}

	//insère l'élément en fin du tableaux
	(*tas)[tab_len - 1] = cle;
}

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

void supprMin(uint128_t *tas) {
	supprTete(&tas);

	int i = 0;
	int id_child = 2 * i + 1;
	while (i < tab_len && tab_len > id_child) {
		// Si fils gauche < racine
		bool left_inf = inf(tas[id_child], tas[i]);
		// Si fils droit < racine
		bool right_inf = inf(tas[id_child + 1], tas[i]);

		// Si un des fils < racine
		if (left_inf || right_inf) {
			if (inf(tas[id_child], tas[id_child + 1])) {
				interchangerAB(&tas[i], &tas[id_child]);
				i += 1 + i;
			} else {
				interchangerAB(&tas[i], &tas[id_child + 1]);
				i += 2 + i;
			}
		} else
			break;

		id_child = 2 * i + 1;
	}
}

void ajout(uint128_t cle, uint128_t *tas) {
	insertCle(cle, &tas);

	if (tab_len <= 0) {
		fprintf(stderr, "Erreur de taille ajut min heap tab\n");
		exit(EXIT_FAILURE);
	}

	if (tab_len == 1) return; // Si le tas a un element, c'est un tas

	// Si plus d'elements, il faut  s'assurer que c'est toujours un tas
	int i = tab_len - 1;

	while (i != 0) {
		int parent = (i % 2 == 1) ? (i - 1) / 2 : (i - 2) / 2;
		if (!inf(tas[parent], tas[i])) {
			interchangerAB(&tas[i], &tas[parent]);
         		i = parent;
        	} else
	            	break;

	}
}

void ajoutIteratif(uint128_t *listeElement, int len, uint128_t *tas) {
    for(int i = 0; i < len; i++) {
    	ajout(listeElement[i], tas);
    }
}

/* -------------------------------------------------------------------------- */