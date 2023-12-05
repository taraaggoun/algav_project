/* -------------------------------- INCLUDES -------------------------------- */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/tprioritetab.h"
#include "test_utils.h"

/* -------------------------------- DEFINE --------------------------------- */

#define NB 5

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

// Affiche une clé à la sortie
void print_cle(uint128_t cle) {
	char cle_tmp[BUF_UINT128_LEN_B10] = { 0 };
	uint128_to_str(cle, cle_tmp, BUF_UINT128_LEN_B10);
	printf(" %s ", cle_tmp);
}

// Affiche un tableaux de clé à la sortie
void print_tas(uint128_t *tas, int taille) {
	printf("[\n");
	for(int i = 0 ; i < taille; i++) {
		print_cle(tas[i]);
		if(i == (taille - 1)) {
		} else {
			printf(";\n");
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

	char pathname_2[PATHMAX] = "cles_alea/jeu_3_nb_cles_5000.txt";

	FILE *file_2 = fopen(pathname_2, "r");
	if (file_2 == NULL) {
		dprintf(STDERR_FILENO, "Erreur fopen file_2\n");
		exit(EXIT_FAILURE);
	}

	uint128_t *listesCle_1 = calloc(1, NB * sizeof(uint128_t));
	uint128_t *listesCle_2 = calloc(1, NB * sizeof(uint128_t));


	printf("-- Création d'une liste de clés %s --\n\n", pathname);

	int i = 0;

	uint128_t cle = { 0 };
	char cle_str[BUF_UINT128_LEN_B16] = { 0 };

	while(i < NB) {
		if (read_uint128(file, &cle, cle_str) == 0)
			break;
		listesCle_1[i] = cle;
		listesCle_2[i] = cle;
		i++;
	}

	printf("Liste clé 1 : ");
	print_tas(listesCle_1, i);
	printf("\n");

	printf("-- Création d'un tas à partir des clés %s --\n\n", pathname);

	printf("-- Création d'une liste de clés %s --\n\n", pathname_2);

	int j = 0;

	uint128_t cle_2 = { 0 };
	char cle_str_2[BUF_UINT128_LEN_B16] = { 0 };

	while(j < NB) {
		if (read_uint128(file_2, &cle_2, cle_str_2) == 0)
			break;
		listesCle_2[i] = cle_2;
		j++;
	}

	printf("Liste clé 2 : ");
	print_tas(listesCle_2, j);
	printf("\n");

	printf("-- Création d'un tas à partir des clés %s --\n\n", pathname_2);

	uint128_t *tasCle = calloc(1, NB * sizeof(uint128_t));


	ajoutIteratif(listesCle_1, NB, tasCle);
	constructionTas(listesCle_2,i);

	free(listesCle_1);

	printf("Tas 1 : ");
	print_tas(tasCle,i);
	printf("\n");

	if(estUnTas(tasCle,i)){
		printf("Tas 1 est un tas\n");
	}else{
		printf("Tas 1 n'est pas un tas\n");
	}

	printf("Tas 2 : ");
	print_tas(listesCle_2,i);
	printf("\n");

	if(estUnTas(listesCle_2,i)){
		printf("Tas 2 est un tas\n");
	}else{
		printf("Tas 2 n'est pas un tas\n");
	}

	printf("-- Union des tas créer à partir des clés de %s & %s --\n\n", pathname,pathname_2);

	uint128_t *unionTas;

	unionTas = unionAB(listesCle_2,tasCle,j,i);

	printf("Tas Union:");
	print_tas(unionTas,i+j);
	printf("\n");

	if(estUnTas(unionTas,i+j)){
		printf("Tas Union est un tas\n");
	}else{
		printf("Tas Union n'est pas un tas\n");
	}

	printf("\n-- Fin du tas créer avec les tas des fichiers %s & %s --\n", pathname,pathname_2);

	printf("-- Suppression de la plus petite clé du tas créer à partir des clés %s --\n\n", pathname);

	supprMin(tasCle);

	printf("Tas:");
	print_tas(tasCle,i-1);
	printf("\n");

	if(estUnTas(tasCle,i-1)){
		printf("Tas supprMin est un tas\n");
	}else{
		printf("Tas supprMin n'est pas un tas\n");
	}

	free(listesCle_2);

	free(tasCle);

	printf("\n-- Fin du tas créer avec les valeurs du fichier %s --\n", pathname);

	fclose(file);

	return 0;
}

/* -------------------------------------------------------------------------- */
