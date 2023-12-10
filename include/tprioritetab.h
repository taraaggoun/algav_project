#pragma once

/* -------------------------------- INCLUDE --------------------------------- */

#include "uint128.h"
#include "tab_dynamique.h"

/* -------------------------------- FUNCTIONS ------------------------------- */

bool estUnTas(table_dynamique *tas);

// Supprime le plus petit element du tas
void supprMin(table_dynamique *tas);

// Ajoute au tas avec l'élément
void ajout(uint128_t element, table_dynamique *tas);

// Rajoute au tas les elemennt de la liste
void ajoutIteratif(uint128_t* listeElement,int len,table_dynamique *tas);

void constructionTas(table_dynamique *listeElement);

table_dynamique unionAB(table_dynamique * A,table_dynamique * B);
/* -------------------------------------------------------------------------- */
