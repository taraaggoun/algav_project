/* -------------------------------- INCLUDES -------------------------------- */

#include "test_utils.h"

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

/**
 * Renvoie la taille de la chaine de caractere
**/
static int len(char *str) {
	int cmp = 0;
	while (isalnum(*str)) {
		cmp++;
		str++;
	}
	return cmp;
}

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

/** Renvoie une erreur si trop d'argument
 *  Sinon le nom du fichier et l'argument
 *  Sinon un fichier par default
**/
void argument_manager(int argc, char *argv[], char *pathname) {
	if (argc == 1)
		strcpy(pathname, "cles_alea/jeu_1_nb_cles_1000.txt");
	if (argc == 2)
		strcpy(pathname, argv[1]);
	if (argc > 2) {
		dprintf(STDERR_FILENO, "Erreur mauvais nombre d'argument\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * Lis dans un fichier le prochain nombre
**/
int read_uint128(FILE *file, uint128_t *cle, char *buf) {
	memset(buf, 0, strlen(buf));

	char *str = fgets(buf, BUF_UINT128_LEN_B16, file);
	if (str == NULL && strcmp(buf, "\0") != 0) {
		dprintf(STDERR_FILENO, "Erreur fgets\n");
		exit(EXIT_FAILURE);
	}
	if (str == NULL)
		return 0;

	buf[len(str)] = '\0';
	str_to_uint128(buf, cle);

	return 1;
}

/* -------------------------------------------------------------------------- */
