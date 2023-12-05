/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/tab_dynamique.h"
#include "test_utils.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* -------------------------------- DEFINE --------------------------------- */

#define CAPACITY 100
#define SIZE 10

/* ---------------------------------- MAIN ---------------------------------- */

int main(int argc, char *argv[]) {
	char pathname[PATHMAX] = { 0 };
	argument_manager(argc, argv, pathname);

	FILE *file = fopen(pathname, "r");
	if (file == NULL) {
		dprintf(STDERR_FILENO, "Erreur fopen\n");
		exit(EXIT_FAILURE);
	}

	uint128_t *listeCle_1 = calloc(1, SIZE * sizeof(uint128_t));



	printf("-- Création d'une liste de clés %s --\n\n", pathname);

	int i = 0;

	uint128_t cle = { 0 };
	char cle_str[BUF_UINT128_LEN_B16] = { 0 };

	while(i < SIZE) {
		if (read_uint128(file, &cle, cle_str) == 0)
			break;
		listeCle_1[i] = cle;
		i++;
	}

	printf("-- Fin de création d'une liste de clés %s --\n\n", pathname);

	printf("-- Création d'un tableau dynamique à partir de cette liste de clés %s --\n\n", pathname);

	table_dynamique table;

	constTableDyn(&table,CAPACITY);

	for (int j = 0; j < i ; j++){
		addElement(&table,listeCle_1[j]);
	}

	printTable(&table);

	printf("-- Fin de création d'un tableau dynamique à partir de cette liste de clés %s --\n\n", pathname);

	printf("-- Suppression de l'élément [%d] du tableau dynamique --\n",4);

	supprElement(&table,table.data[4]);

	printTable(&table);

	printf("--Fin de suppression de l'élément [%d] du tableau dynamique --\n",4);

	freeTable(&table);

	return 0;
}
/* -------------------------------------------------------------------------- */
