#pragma once

/* -------------------------------- INCLUDE --------------------------------- */

#include "uint128.h"

/* -------------------------------- STRUCTURES ------------------------------ */


// Structure représentant le tableau dynamique
typedef struct table_dynamique{
    uint128_t * data;     // Pointeur vers les données du tableau
    int size;   // Taille actuelle du tableau
    int capacity; // Capacité totale du tableau
}table_dynamique;


/* -------------------------------- FUNCTIONS ------------------------------- */

// Fonction pour initialiser le tableau dynamique
void constTableDyn(table_dynamique *table, int initialCapacity);

// Fonction pour ajouter un élément au tableau dynamique
void addElement(table_dynamique *table, uint128_t element);

// Fonction pour ajouter un élément au tableau dynamique
void supprElement(table_dynamique *table, uint128_t element);

// Fonction pour ajouter un élément au tableau dynamique
void supprElementInd(table_dynamique *table, int indice);

// Fonction pour libérer la mémoire allouée par le tableau dynamique
void freeTable(table_dynamique *table);

// Fonction pour afficher le tableau dynamique
void printTable(table_dynamique *table);


