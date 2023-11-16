/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/uint128.h"
#include "../include/tprioritetab.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* -------------------------------- DEFINE --------------------------------- */

#define NB 10
#define BUF_UINT128_LEN_B10 38

/* ---------------------------- GLOBAL VARIABLE ----------------------------- */

char pathname[2048] = { 0 };

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

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

/* ---------------------------- PRIVATE FUNCTIONS --------------------------- */

int main(int argc, char *argv[]) {
	argument_manager(argc, argv);

	FILE *file = fopen(pathname, "r");
	if (file == NULL) {
		dprintf(STDERR_FILENO, "Erreur fopen\n");
		exit(EXIT_FAILURE);
	}
	// printf("-- Création d'une liste de clés %s --\n\n", pathname);

	int i = 0;

	uint128_t cle = { 0 };

	uint128_t *listesCle = calloc(1, NB * sizeof(uint128_t));

	while(i < NB) {
		if (read_uint128(file, &cle) == 0)
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