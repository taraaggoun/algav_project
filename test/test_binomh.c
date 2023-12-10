/* -------------------------------- INCLUDE --------------------------------- */

#include "../include/binomial_heap.h"

#include "test_utils.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


/* -------------------------------- DEFINES --------------------------------- */

#define NB_UINT128 6

/* ---------------------------------- MAIN ---------------------------------- */

int main(int argc, char *argv[]) {
	char pathname[PATHMAX] = { "cles_alea/jeu_1_nb_cles_1000.txt" };
	//argument_manager(argc, argv);

	printf("%s\n",pathname);

	FILE *file = fopen(pathname, "r");
	if (file == NULL) {
		dprintf(STDERR_FILENO, "Erreur fopen\n");
		exit(EXIT_FAILURE);
	}

	//uint128_t cle = { 0 };
	//char cle_str[BUF_UINT128_LEN_B16] = { 0 };

	/*binomh *bh = binomh_create_empty();
	printf("Tournois Binomiale vide \n");
	binomh_print(bh);
	printf("\n");*/


	//size_t i = pow(2, NB_UINT128);

	uint128_t * tmp = (uint128_t*)malloc(pow(2, NB_UINT128)*sizeof(uint128_t));

	int i = 0;

	uint128_t cle = { 0 };
	char cle_str[BUF_UINT128_LEN_B16] = { 0 };

	while(i < pow(2, NB_UINT128)) {
		if (read_uint128(file, &cle, cle_str) == 0)
			break;
		tmp[i] = cle;
		i++;
	}
	/*while( --i >= 0 && read_uint128(file, &cle, cle_str)) {
		printf("b\n");
		tmp[i]=cle;
		//binomh *tmp = binomh_create(cle);
		//binomh *uni = binomh_union(bh, tmp);
		//binomh_free(tmp);
		//binomh_free(bh);
		//bh = NULL;
		//bh = uni;
	}*/

	binomh *uni = binomK_create(tmp,NB_UINT128);

	binomh_print(uni);

	if(isBinomialHeap(uni)){
		printf("\nest un tournoi\n");
	}else{
		printf("\nn'est pas un tournoi\n");
	}

	//binomh_print(tmp);


	// print_bst(bst);
	// printf("L'arbre est un abr ? %d\n", is_bst(bst));
	
	// bool exist = search_bst(bst, cle) != NULL;
	// printf("Es ce que %s appartient a l'arbre? %d \n", cle_str, exist);

	// printf("\nSuppression de %s\n", cle_str);
	// bst = supp_bst(bst, cle);
	// print_bst(bst);
	// printf("L'arbre est un abr ? %d\n", is_bst(bst));

	// exist = search_bst(bst, cle) != NULL;
	// printf("Es ce que %s appartient a l'arbre? %d \n", cle_str, exist);

	// binomh_free(bh);
	fclose(file);

	return 0;
}

/* -------------------------------------------------------------------------- */
