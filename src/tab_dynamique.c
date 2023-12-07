/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/tab_dynamique.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

/* -------------------------------- DEFINES --------------------------------- */

#define BUF_UINT128_LEN_B16 36
#define BUF_UINT128_LEN_B10 38
#define MIN_ALLOC 1/4

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

/**
 * Affiche une clé à la sortie
*/
void printKey(uint128_t cle) {
	char cle_tmp[BUF_UINT128_LEN_B10] = { 0 };
	uint128_to_str(cle, cle_tmp, BUF_UINT128_LEN_B10);
	printf(" %s ", cle_tmp);
}

/**
 * Echange les valeur a et b;
*/
static void swapAB(uint128_t *a, uint128_t *b) {
	uint128_t tmp = *a;
	*a = *b;
	*b = tmp;
}

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

void constTabDyn(table_dynamique *table, int initialCapacity) {

	table->data = (uint128_t *) calloc(1, initialCapacity * sizeof(uint128_t));

	if (table->data == NULL) {
        	dprintf(STDERR_FILENO, "Erreur d'allocation mémoire\n");
        	exit(EXIT_FAILURE);
    	}

	table->size = 0;
	table->capacity = initialCapacity;
}

void addElement(table_dynamique *table, uint128_t element) {
	// Vérifier si une augmentation de la capacité est nécessaire
	if (table->size == table->capacity) {
        	// Doubler la capacité en utilisant realloc
        	table->capacity *= 2;
        	table->data = (uint128_t *) realloc(table->data, table->capacity * sizeof(uint128_t));

        	if (table->data == NULL) {
            		fprintf(stderr, "Erreur d'allocation mémoire\n");
            		exit(EXIT_FAILURE);
        	}
    	}

	// Réalloue la mémoire afin de faire de la place dans le tas
    	if (table->size == table->capacity) {
    		table->data = realloc(table->data, 2 * table->capacity * sizeof(uint128_t));
    		if (table->data == NULL) {
    			dprintf(STDERR_FILENO, "Erreur realloc addElement\n");
    			exit(EXIT_FAILURE);
    		}
    		memset(table->data + table->size, 0, table->capacity - table->size);
    		table->capacity *= 2;
    	}

    	// Ajouter l'élément au tableau
    	table->data[table->size++] = element;
}

void supprElement(table_dynamique *table, uint128_t element) {
	bool tmp = false;

	for(int i = 0; i < table->size - 1; i++) {
		if(eg(table->data[i], element) || tmp) {
			tmp = true;
			swapAB(&table->data[i], &table->data[i + 1]);
		}
	}
	if(tmp || eg(table->data[table->size - 1], element)){
		table->size--;
	}

	// Réalloue la mémoire afin d'en libéré les case qu'on utilise plus
	// si le nombre de case occupé est inferieur a 1/4 de la capacité
	if (table->size <= table->capacity * MIN_ALLOC) {
		table->data = realloc(table->data, 2 * table->size * sizeof(uint128_t));
		if (table->data == NULL) {
			dprintf(STDERR_FILENO, "Erreur realloc supprElement\n");
			exit(EXIT_FAILURE);
		}
		table->capacity = 2 * table->size;
	}
}

void supprElementInd(table_dynamique *table, int indice) {
	for(; indice < table->size ; indice++) {
		swapAB(&table->data[indice], &table->data[indice + 1]);
	}
	table->size--;

	// Réalloue la mémoire afin d'en libéré les case qu'on utilise plus
	// si le nombre de case occupé est inferieur a 1/4 de la capacité
	if (table->size <= table->capacity * MIN_ALLOC) {
		table->data = realloc(table->data, 2 * table->size * sizeof(uint128_t));
		if (table->data == NULL) {
			dprintf(STDERR_FILENO, "Erreur realloc supprElement\n");
			exit(EXIT_FAILURE);
		}
		table->capacity = 2 * table->size;
	}
}

void freeTable(table_dynamique *table) {
    free(table->data);
    table->size = 0;
    table->capacity = 0;
}

void printTable(table_dynamique *table) {
	printf("Tableau :\n| Donnée : [");
	for(int i = 0; i < table->size; i++) {
		printKey(table->data[i]);
		if (i == (table->size - 1))
			printf("]\n");
		else
			printf(";");
	}

	printf("| Taille : %d\n| Capacité : %d\n\n",table->size,table->capacity);
}

/* -------------------------------------------------------------------------- */
