#pragma once

/* -------------------------------- INCLUDE --------------------------------- */

#include "uint128.h"

/* -------------------------------- FUNCTIONS ------------------------------- */

bool estUnTas(uint128_t *tas,int len);



// Supprime le plus petit element du tas
void supprMin(uint128_t *tas);

// Ajoute au tas avec l'élément
void ajout(uint128_t element, uint128_t *tas);

// Rajoute au tas les elemennt de la liste
void ajoutIteratif(uint128_t* listeElement, int len, uint128_t *tas);

void constructionTas(uint128_t *listeElement,int len);

uint128_t* unionAB(uint128_t * A,uint128_t * B,int lenA,int lenB);
/* -------------------------------------------------------------------------- */
