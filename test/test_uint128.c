/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/uint128.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* -------------------------------- DEFINE --------------------------------- */



/* ---------------------------- GLOBAL VARIABLE ----------------------------- */

char pathname[2048] = { 0 };

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

/** Affiche si
 * cle1 > cle 2
 * cle1 = cle2
 * cle1 < cle2
*/
void affiche_comparaison(uint128_t cle1, uint128_t cle2) {
	// Convertion des int en str
	char cle1_str[45] = { 0 };
	uint128_to_str(cle1, cle1_str);
	char cle2_str[45] = { 0 };
	uint128_to_str(cle2, cle2_str);

	if (inf(cle1, cle2)) {
		printf("%s < %s\n", cle1_str, cle2_str);
		return;
	}

	if (eg(cle1, cle2)) {
		printf("%s = %s\n", cle1_str, cle2_str);
		return;
	}

	// Si cle1 > cle2
	printf("%s > %s\n", cle1_str, cle2_str);
}

/** Renvoie une erreur si trop d'argument
 *  Sinon le nom du fichier et l'argument
 *  Sinon un fichier par default
*/
void argument_manager(int argc, char *argv[]) {
	if (argc > 2) {
		dprintf(STDERR_FILENO, "Erreur mauvais nombre d'argument\n");
		exit(EXIT_FAILURE);
	}

	if (argc == 2)
		strcpy(pathname, argv[1]);

	if (argc == 1)
		strcpy(pathname, "test/cles_alea/jeu_1_nb_cles_1000.txt");
}

// Renvoie la taille de la chaine de caractere
int len(char *str) {
	int cmp = 0;
	while (isalnum(*str)) {
		cmp++;
		str++;
	}
	return cmp;
}

// Lis dans un fichier le prochain nombre
int read_uint128(FILE *file, uint128_t *cle) {
	char buf[36] = { 0 };

	char *str = fgets(buf, 36, file);
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

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

int main(int argc, char *argv[]) {
	argument_manager(argc, argv);

	FILE *file = fopen(pathname, "r");
	if (file == NULL) {
		dprintf(STDERR_FILENO, "Erreur fopen\n");
		exit(EXIT_FAILURE);
	}
	printf("-- Comparaison des valeurs du fichier %s --\n\n", pathname);

	uint128_t cle1 = { 0 };
	uint128_t cle2 = { 0 };

	while(read_uint128(file, &cle1)) {
		if (read_uint128(file, &cle2) == 0)
			break;

		affiche_comparaison(cle1, cle2);
	}

	printf("\n-- Fin comparaison des valeurs du fichier %s --\n", pathname);
	fclose(file);

	return 0;
}

/* -------------------------------------------------------------------------- */
