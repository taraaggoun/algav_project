// /* -------------------------------- INCLUDE --------------------------------- */

// #include "../include/binomial_heap.h"
// #include "../include/binomial_queue.h"

// #include "test_utils.h"

// #include <string.h>
// #include <ctype.h>
// #include <stdlib.h>
// #include <unistd.h>


// /* -------------------------------- DEFINES --------------------------------- */

// #define DEGRE 2
// #define NOMBRECLES 14

// int powAF(int a , int k){
// 	int tmp = 1;
// 	for(int i = 0 ; i < k ; i++){
// 		tmp *=a;
// 	}

// 	return tmp;
// }

// // Affiche une clé à la sortie
// void print_cles(uint128_t cle) {
// 	char cle_tmp[BUF_UINT128_LEN_B10] = { 0 };
// 	uint128_to_str(cle, cle_tmp, BUF_UINT128_LEN_B10);
// 	printf(" %s ", cle_tmp);
// }

// /* ---------------------------------- MAIN ---------------------------------- */

// int main(int argc, char *argv[]) {
// 	argument_manager(argc, argv);

// 	FILE *file = fopen(pathname, "r");
// 	if (file == NULL) {
// 		dprintf(STDERR_FILENO, "Erreur fopen\n");
// 		exit(EXIT_FAILURE);
// 	}

// 	uint128_t * listeCles = (uint128_t*)malloc(NOMBRECLES*sizeof(uint128_t));
// 	uint128_t * tmp = (uint128_t*)malloc(DEGRE*powAF(2, DEGRE)*sizeof(uint128_t));
// 	uint128_t * tmp2 = (uint128_t*)malloc(DEGRE*powAF(2, DEGRE)*sizeof(uint128_t));
// 	binomh * listeh= (binomh*)malloc((DEGRE+1)*sizeof(binomh));
// 	binomh * listeh2= (binomh*)malloc((DEGRE+1)*sizeof(binomh));

// 	int i = 0;

// 	uint128_t cle = { 0 };
// 	char cle_str[BUF_UINT128_LEN_B16] = { 0 };

// 	while(i < NOMBRECLES) {
// 		if (read_uint128(file, &cle, cle_str) == 0)
// 			break;
// 		listeCles[i] = cle;
// 		i++;
// 	}

// 	int k = i/2;


// 	/*for(int l = 0 ; l <= DEGRE ; l++){
// 		k+=powAF(2,l);
// 	}*/

// 	int n = 0;

// 	for(int j = DEGRE ; j >=0 ; j--){
// 		for(int m = 0; m < powAF(2,j);m++){
// 			tmp[m]=listeCles[k];
// 			tmp2[m]=listeCles[i];
// 			k--;
// 			i--;
// 		}

// 		listeh[n]=*binomh_createK(tmp, j);
// 		listeh2[n++]=*binomh_createK(tmp2, j);
// 	}

// 	printf("*****************************************Création d'une File binomial BQ*****************************************\n\n");
// 	binomq *bq = binomq_create_empty();
// 	binomq_print(bq);

// 	printf("\n*****************************************Création d'une File binomial BQ_TEST*****************************************\n\n");
// 	binomq *bq_test=binomq_create(listeh,DEGRE+1);
// 	binomq_print(bq_test);

// 	printf("\n*****************************************Création d'une File binomial BQ_TEST*****************************************\n\n");
// 	binomq *bq_test2=binomq_create(listeh2,DEGRE+1);
// 	binomq_print(bq_test2);

// 	printf("\n*****************************************Union de deux files binomials BQ_TEST et BQ_TEST2*****************************************\n\n");
// 	printf("BQ_TEST : \n\n");
// 	binomq_print(bq_test);
// 	printf("BQ_TEST2 : \n\n");
// 	binomq_print(bq_test2);

// 	binomq * bq_union = unionQueue(bq_test,bq_test2);
// 	printf("BQ_UNION: \n\n");
// 	binomq_print(bq_union);

// 	//binomq_free(bq); erreur
// 	//binomq_free(bq_test); erreur

// 	fclose(file);

// 	return 0;
// }

// /* -------------------------------------------------------------------------- */
int main( ) {
	return 0;
}