/* -------------------------------- INCLUDE --------------------------------- */

#include "test_utils.h"

#include <string.h>

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

/**
 * Verifie si la comparaison est reussie et stock le resultat dans str
**/
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
**/
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

/* ---------------------------------- MAIN ---------------------------------- */

int main(int argc, char *argv[]) {
	char pathname[PATHMAX] = { 0 };
	argument_manager(argc, argv, pathname);

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

	printf("\n-- Fin comparaison des valeurs du fichier %s --\n\n", pathname);
	fclose(file);

	return 0;
}

/* -------------------------------------------------------------------------- */