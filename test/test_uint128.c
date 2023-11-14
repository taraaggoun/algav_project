/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/uint128.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* -------------------------------- DEFINES --------------------------------- */

#define BUF_UINT128_LEN_B16 36

#define BUF_UINT128_LEN_B10 38

#define PATHMAX 2048

/* ---------------------------- GLOBAL VARIABLE ----------------------------- */

char pathname[PATHMAX] = { 0 };

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

// Verifie si la comparaison est reussie et stock le resultat dans str
static void comparaison_reussie(int str_cmp, int int_cmp, char *str) {
	str_cmp = (str_cmp > 0) ?  1 : str_cmp;
	str_cmp = (str_cmp < 0) ? -1 : str_cmp;
	memset(str, 0, strlen(str));
	if (str_cmp == int_cmp)
		sprintf(str, "OK");
	else
		sprintf(str, "Erreur");
}

/** Affiche si
 * cle1 > cle 2
 * cle1 = cle2
 * cle1 < cle2
*/
static void affiche_comparaison(uint128_t cle1, uint128_t cle2, int cmp) {
	// Convertion des int en str
	char cle1_str[BUF_UINT128_LEN_B10] = { 0 };
	uint128_to_str(cle1, cle1_str, BUF_UINT128_LEN_B10);
	char cle2_str[BUF_UINT128_LEN_B10] = { 0 };
	uint128_to_str(cle2, cle2_str, BUF_UINT128_LEN_B10);

	char str_comparaison[16] = { 0 }; // Taille max = ERREUR

	if (inf(cle1, cle2)) {
		comparaison_reussie(cmp, -1, str_comparaison);
		printf("%s < %s : %s\n", cle1_str, cle2_str, str_comparaison);
		return;
	}

	if (eg(cle1, cle2)) {
		comparaison_reussie(cmp, 1, str_comparaison);
		printf("%s = %s : %s\n", cle1_str, cle2_str, str_comparaison);
		return;
	}

	// Si cle1 > cle2
	comparaison_reussie(cmp, 1, str_comparaison);
	printf("%s > %s : %s\n", cle1_str, cle2_str, str_comparaison);
}

/** Renvoie une erreur si trop d'argument
 *  Sinon le nom du fichier et l'argument
 *  Sinon un fichier par default
*/
static void argument_manager(int argc, char *argv[]) {
	if (argc == 1)
		strcpy(pathname, "test/cles_alea/jeu_1_nb_cles_1000.txt");

	if (argc == 2)
		strcpy(pathname, argv[1]);
	if (argc > 2) {
		dprintf(STDERR_FILENO, "Erreur mauvais nombre d'argument\n");
		exit(EXIT_FAILURE);
	}
}

// Renvoie la taille de la chaine de caractere
static int len(char *str) {
	int cmp = 0;
	while (isalnum(*str)) {
		cmp++;
		str++;
	}
	return cmp;
}

// Lis dans un fichier le prochain nombre
static int read_uint128(FILE *file, uint128_t *cle, char *buf) {
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
	char cle1_str[BUF_UINT128_LEN_B16] = { 0 };
	uint128_t cle2 = { 0 };
	char cle2_str[BUF_UINT128_LEN_B16] = { 0 };

	while(read_uint128(file, &cle1, cle1_str)) {
		if (read_uint128(file, &cle2, cle2_str) == 0)
			break;
			
		affiche_comparaison(cle1, cle2, strcmp(cle1_str, cle2_str));
	}

	printf("\n-- Fin comparaison des valeurs du fichier %s --\n", pathname);
	fclose(file);

	return 0;
}

/* -------------------------------------------------------------------------- */
