#pragma once

/* -------------------------------- INCLUDE --------------------------------- */

#include "uint128.h"

/* -------------------------------- STRUCTURES ------------------------------ */

/**
 * Structure représentant le tableau dynamique
*/
typedef struct table_dynamique {
	/** Pointeur vers les données du tableau */
	uint128_t *data;
	/** Taille actuelle du tableau */
	int size;
	/** Capacité totale du tableau */
	int capacity;
} table_dynamique;

/* -------------------------------- FUNCTIONS ------------------------------- */

/**
 * Fonction pour initialiser le tableau dynamique
*/
void constTabDyn(table_dynamique *table, int initialCapacity);

/**
 * Fonction pour ajouter un élément au tableau dynamique
*/
void addElement(table_dynamique *table, uint128_t element);

/**
 * Fonction pour ajouter un élément au tableau dynamique
 */
void supprElement(table_dynamique *table, uint128_t element);

/**
 * Fonction pour ajouter un élément au tableau dynamique
*/
void supprElementInd(table_dynamique *table, int indice);

/**
 * Fonction pour libérer la mémoire allouée par le tableau dynamique
*/
void freeTable(table_dynamique *table);

/**
 * Fonction pour afficher le tableau dynamique 
*/
void printTable(table_dynamique *table);

/* -------------------------------------------------------------------------- */
