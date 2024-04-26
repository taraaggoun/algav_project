/* -------------------------------- INCLUDES -------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/uint128.h"

/* -------------------------------- DEFINES --------------------------------- */

#define BUF_UINT128_LEN_B16 36

#define BUF_UINT128_LEN_B10 38

#define PATHMAX 2048

/* ---------------------------- GLOBAL VARIABLE ----------------------------- */

extern char pathname [PATHMAX];

/* -------------------------------- FUNCTIONS ------------------------------- */

/** Renvoie une erreur si trop d'argument
 *  Sinon le nom du fichier et l'argument
 *  Sinon un fichier par default
*/
void argument_manager(int argc, char *argv[]);

/**
 * Lis un uint128 dans le fichier et le met dans cle 
 * et dans buf sous forme de chaine de caracteres
**/
int read_uint128(FILE *file, uint128_t *cle, char *buf);

/* -------------------------------------------------------------------------- */