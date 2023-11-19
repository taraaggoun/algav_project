/* -------------------------------- INCLUDES -------------------------------- */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/tprioritetab.h"
#include "../include/test_utils.h"

/* -------------------------------- DEFINE --------------------------------- */

#define NB 10

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

// Affiche une clé à la sortie
void print_cle(uint128_t cle) {
	char cle_tmp[BUF_UINT128_LEN_B10] = { 0 };
	uint128_to_str(cle, cle_tmp, BUF_UINT128_LEN_B10);
	printf(" %s ", cle_tmp);
}

// Affiche un tableaux de clé à la sortie
void print_tas(uint128_t *tas, int taille) {
	printf("[");
	for(int i = 0 ; i < taille; i++) {
		print_cle(tas[i]);
		if(i == (taille - 2)) {
		} else {
			printf(";");
		}
	}
	printf("]\n");
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
	// printf("-- Création d'une liste de clés %s --\n\n", pathname);

	int i = 0;

	uint128_t cle = { 0 };
	char cle_str[BUF_UINT128_LEN_B16] = { 0 };
	uint128_t *listesCle = calloc(1, NB * sizeof(uint128_t));

	while(i < NB) {
		if (read_uint128(file, &cle, cle_str) == 0)
			break;
		listesCle[i] = cle;
		i++;
	}
	print_tas(listesCle, NB);
	// printf("\n");

	// printf("-- Création d'un tas à partir des clés %s --\n\n", pathname);

	uint128_t *tasCle = calloc(1, NB * sizeof(uint128_t));


	ajoutIteratif(listesCle, NB, tasCle);

	free(listesCle);

	printf("Tas:");
	print_tas(tasCle,i);
	printf("\n");

	// printf("-- Suppression de la plus petite clé du tas créer à partir des clés %s --\n\n", pathname);

	// supprMin(tasCle);

	// printf("Tas:");
	// print_tas(tasCle,i);
	// printf("\n");

	free(tasCle);
	
	// printf("\n-- Fin du tas créer avec les valeurs du fichier %s --\n", pathname);

	fclose(file);

	return 0;
}

/* -------------------------------------------------------------------------- */