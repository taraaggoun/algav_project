/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/min_heap_array.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./test_utils.h"
#include "../include/tab_dynamique.h"

/* -------------------------------- DEFINE --------------------------------- */

#define CAPACITY 10
#define SIZE 5

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

// Affiche une clé à la sortie
void printCles(uint128_t cle) {
	char cle_tmp[BUF_UINT128_LEN_B10] = { 0 };
	uint128_to_str(cle, cle_tmp, BUF_UINT128_LEN_B10);
	printf(" %s ", cle_tmp);
}

// Affiche un tableaux de clé à la sortie
void printTas(uint128_t *tas, int taille) {
	printf("[\n");
	for(int i = 0 ; i < taille; i++) {
		printCles(tas[i]);
		if(i != (taille - 1))
			printf(";\n");
	}
	printf("]\n\n");
}

/* ---------------------------------- MAIN ---------------------------------- */

int main(int argc, char *argv[]) {
	argument_manager(argc, argv);

	FILE *file = fopen(pathname, "r");
	if (file == NULL) {
		dprintf(STDERR_FILENO, "Erreur fopen\n");
		exit(EXIT_FAILURE);
	}

	char pathname_2[PATHMAX] = "test/cles_alea/jeu_2_nb_cles_1000.txt";

	FILE *file_2 = fopen(pathname_2, "r");
	if (file_2 == NULL) {
		dprintf(STDERR_FILENO, "Erreur fopen file_2\n");
		exit(EXIT_FAILURE);
	}

	uint128_t *listesCle_1 = calloc(1, SIZE * sizeof(uint128_t));
	uint128_t *listesCle_2 = calloc(1, SIZE * sizeof(uint128_t));

	printf("-- Création d'une liste de clés %s --\n\n", pathname);

	int i = 0;

	uint128_t cle = { 0 };
	char cle_str[BUF_UINT128_LEN_B16] = { 0 };

	while(i < SIZE) {
		if (read_uint128(file, &cle, cle_str) == 0)
			break;
		listesCle_1[i] = cle;
		i++;
	}


	printf("Liste clé 1 : \n");
	printTas(listesCle_1, i);
	printf("\n\n");

	printf("-- Création d'une liste de clés %s --\n\n", pathname_2);

	int j = 0;

	uint128_t cle_2 = { 0 };
	char cle_str_2[BUF_UINT128_LEN_B16] = { 0 };

	while(j < SIZE) {
		if (read_uint128(file_2, &cle_2, cle_str_2) == 0)
			break;
		listesCle_2[j] = cle_2;
		j++;
	}

	printf("Liste clé 2 : \n");
	printTas(listesCle_2, j);
	printf("\n\n");

	printf("-- Création d'un tas à partir des clés %s --\n\n", pathname);

	table_dynamique tas_1;
	constTabDyn(&tas_1, CAPACITY);

	mharray_ajout_iteratif(listesCle_1, i, &tas_1);

	printTable(&tas_1);

	if (is_heap(&tas_1)) printf("Tas 1 est un tas\n\n");
	else printf("Tas 1 n'est pas un tas\n\n");

	printf("-- Création d'un tas à partir des clés %s --\n\n", pathname_2);
	table_dynamique tas_2;
	constTabDyn(&tas_2, CAPACITY);

	for (int k = 0 ; k < j; k++)
		addElement(&tas_2,listesCle_2[k]);

	for (int k = tas_2.size; k < tas_2.capacity; k++) {
		if (read_uint128(file_2, &cle_2, cle_str_2) == 0)
			break;
		addElement(&tas_2, cle_2);
	}
	mharray_construction(&tas_2);
	printTable(&tas_2);

	if(is_heap(&tas_2)) printf("Tas 2 est un tas\n\n");
	else printf("Tas 2 n'est pas un tas\n\n");

	printf("-- Union des tas créer à partir des clés de %s & %s --\n\n", pathname, pathname_2);

	table_dynamique unionTas = mharray_union(&tas_1, &tas_2);

	printTable(&unionTas);

	if(is_heap(&unionTas))
		printf("Tas Union est un tas\n\n");
	else
		printf("Tas Union n'est pas un tas\n\n");

	printf("-- Suppression de la plus petite clé du tas créer à partir des clés %s --\n\n", pathname);

	mharray_suppr_min(&tas_1);

	printTable(&tas_1);

	if(is_heap(&tas_1))
		printf("Tas mharray_suppr_min est un tas\n\n");
	else
		printf("Tas mharray_suppr_min n'est pas un tas\n\n");

	freeTable(&unionTas);
	freeTable(&tas_2);
	freeTable(&tas_1);

	free(listesCle_2);
	free(listesCle_1);

	fclose(file_2);
	fclose(file);

	return 0;
}

/* -------------------------------------------------------------------------- */
