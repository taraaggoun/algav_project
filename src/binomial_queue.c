// /* -------------------------------- INCLUDES -------------------------------- */

// #include "../include/uint128.h"

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <stdbool.h>
// #include <math.h>

// #include "../include/binomial_queue.h"

// /* ---------------------------- PRIVATE FUNCTION ---------------------------- */

// /* Fonction utilitaire */
// int powAK(int a , int k){
// 	int tmp = 1;
// 	for(int i = 0 ; i < k ; i++){
// 		tmp *=a;
// 	}

// 	return tmp;
// }

// /**
//  * Renvoie une copy de bh
//  * alloue un fils de plus si b == true
// */
// static binomh* copyHeap(binomh *bh, bool add_child) {
//     binomh *res = binomh_create_empty();

//     // Copy key
//     res->key = malloc(sizeof(uint128_t));
//     if (res->key == NULL) {
//         dprintf(STDERR_FILENO, "Erreur malloc copy key\n");
//         exit(EXIT_FAILURE);
//     }
//     *(res->key) = *(bh->key);

//     // Allocate memory for children, considering the possibility of adding one more child
//     res->childs = calloc(bh->degre + (add_child ? 1 : 0), sizeof(binomh));

//     if (res->childs == NULL) {
//         dprintf(STDERR_FILENO, "Erreur calloc copy childs\n");
//         exit(EXIT_FAILURE);
//     }

//     // Copy degree
//     res->degre = bh->degre;

//     // Copy child nodes
//     for (size_t i = 0; i < bh->degre; i++) {
// 	binomh *tmp = res->childs + i;
// 	tmp = copyHeap(&(bh->childs[i]), false);
//     }

//     return res;
// }



// /**
//  * Renvoie une copy de bq
// */
// static binomq* copyQueue(binomq *bq) {
// 	binomq *tmp = binomq_create_empty();

// 	tmp->nb_bh= bq->nb_bh;
// 	tmp->nb_elem= bq->nb_elem;
// 	memcpy(tmp->bh, bq->bh, bq->nb_bh * sizeof(binomh));

// 	return tmp;
// }

// static binomq * uFret(binomq * A,binomq * B, binomh * heap){
// 	if(binomh_is_empty(heap) == true){
// 		// printf("*********************binomh_is_empty(heap) == true*****************************\n\n");
// 		if(binomq_is_empty(A) == true){
// 			// printf("*********************binomq_is_empty(A) == true*****************************\n\n");
// 			return copyQueue(B);
// 		}
// 		if(binomq_is_empty(B) == true){
// 			// printf("*********************binomq_is_empty(B) == true*****************************\n\n");
// 			return copyQueue(A);
// 		}

// 		binomh * T1 = minDeg(A);
// 		binomh * T2 = minDeg(B);

// 		if(T1->degre < T2->degre){
// 			// printf("*********************T1->degre < T2->degre*****************************\n\n");
// 			return ajoutMin(unionQueue(reste(A),B),T1);
// 		}else if(T1->degre > T2->degre){
// 			// printf("*********************T1->degre > T2->degre*****************************\n\n");
// 			return ajoutMin(unionQueue(reste(B),A),T2);
// 		}else{
// 			// printf("*********************T1->degre = T2->degre*****************************\n\n");
// 			return uFret(reste(A),reste(B),binomh_union(T1,T2));
// 		}
// 	}else{
// 		// printf("*********************else*****************************\n\n");
// 		if(binomq_is_empty(A) == true){
// 			// printf("*********************binomq_is_empty(A) == true*****************************\n\n");
// 			return unionQueue(binomq_create(heap,1),B);
// 		}
// 		if(binomq_is_empty(B) == true){
// 			// printf("*********************binomq_is_empty(B) == true*****************************\n\n");
// 			return unionQueue(binomq_create(heap,1),A);;
// 		}

// 		binomh * T1 = minDeg(A);
// 		binomh * T2 = minDeg(B);

// 		if((heap->degre < T1->degre) && ( heap->degre < T2->degre)){
// 			// printf("*********************(heap->degre < T1->degre) && ( heap->degre < T2->degre)*****************************\n\n");
// 			return ajoutMin(unionQueue(A,B),heap);
// 		}else if((heap->degre == T1->degre) && ( heap->degre == T2->degre)){
// 			// printf("*********************(heap->degre == T1->degre) && ( heap->degre == T2->degre)*****************************\n\n");
// 			return ajoutMin(uFret(reste(A),reste(B),binomh_union(T1,T2)),heap);
// 		}else if((heap->degre == T1->degre) && ( heap->degre < T2->degre)){
// 			// printf("*********************(heap->degre == T1->degre) && ( heap->degre < T2->degre)*****************************\n\n");
// 			return uFret(reste(A),B,binomh_union(T1,heap));
// 		}else{
// 			// printf("*********************(heap->degre < T1->degre) && ( heap->degre == T2->degre)*****************************\n\n");
// 			return uFret(reste(B),A,binomh_union(T2,heap));
// 		}
// 	}
// }
// /* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

// binomq* binomq_create_empty() {
// 	binomq *bq = calloc(1, sizeof(binomh));
// 	if (bq == NULL) {
// 		dprintf(STDERR_FILENO, "Erreur calloc create bh empty");
// 		exit(EXIT_FAILURE);
// 	}
// 	return bq;
// }

// binomq* binomq_create(binomh * heaps, int len) {
// 	binomq *bq = binomq_create_empty();
// 	bq->bh = heaps;

// 	size_t somme = 0;


// 	for(int i = 0 ; i < len ; i ++){
// 		somme+= powAK(2,heaps[i].degre);
// 	}

// 	bq->nb_bh = len;
// 	bq->nb_elem = somme;

// 	return bq;
// }

// void binomq_free(binomq *bq) {
// 	if (!(bq == NULL)){
// 		binomh_free(bq->bh);
// 		free(bq);
// 	}
// }

// bool binomq_is_empty(binomq *bq) {
// 	return bq == NULL || bq->bh== NULL;
// }

// void binomq_print(binomq *bq) {
// 	if(!binomq_is_empty(bq)){
// 		printf("File Binomial :\n|Nombre d'éléments : %ld (FB_%ld)\n|Listes des éléments : < ",bq->nb_elem,bq->nb_elem);
// 		for(size_t j = 0 ; j < bq->nb_bh ; j++){
// 			printf("TB_%ld",bq->bh[j].degre);
// 			if(j == bq->nb_bh -1){
// 				printf(" >\n\n<\n\n");
// 			}else{
// 				printf(" ; ");
// 			}
// 		}
// 		for(size_t i = 0 ; i < bq->nb_bh ; i++){
// 			binomh_print(&bq->bh[i]);
// 			if(i == bq->nb_bh -1){
// 				printf("\n>\n");
// 			}else{
// 				printf("\n\t;\n\n");
// 			}
// 		}
// 	}else{
// 		printf("File Binomial : vide\n");
// 	}
// }

// binomh * minDeg(binomq * bq){
// 	/*int indice = 0;
// 	int minDegre = bq->bh[0].degre;

// 	for(int j = 1 ; j < bq->nb_bh ; j++){
// 		if(minDegre >=  bq->bh[j].degre){
// 			indice = j ;
// 		}
// 	}

// 	return copy(bq->bh[j],false);*/

// 	return copyHeap(&bq->bh[bq->nb_bh - 1],false);
// }

// binomq * reste(binomq * bq){
// 	binomh * tmp = (binomh*) malloc ((bq -> nb_bh - 1)*sizeof(binomh));

// 	for(size_t i = 0 ; i < bq->nb_bh - 1; i++){
// 		tmp[i]=bq->bh[i];
// 	}

// 	return binomq_create(tmp,bq -> nb_bh - 1);
// }

// /*binomq * supprMin(){

// }*/

// binomq * ajoutMin(binomq * bq,binomh *heap){
// 	binomh * tmpH = (binomh*) malloc((bq->nb_bh + 1) * sizeof(binomh));
// 	binomq * newBq;

// 	if(minDeg(bq)->degre > heap->degre){
// 		for(size_t i = 0 ;  i < bq->nb_bh + 1 ; i++){
// 			if(i == bq->nb_bh){
// 				tmpH[i]=*heap;
// 			}else{
// 				tmpH[i]=bq->bh[i];
// 			}
// 		}
// 		newBq = binomq_create(tmpH,bq->nb_bh + 1);
// 	}else{
// 		newBq = binomq_create_empty();
// 	}

// 	return newBq;
// }



// binomq * unionQueue(binomq *A,binomq *B){
// 	return uFret(A,B,binomh_create_empty());
// }

// //,Construction

// /* -------------------------------------------------------------------------- */

int main ()
{
	return 0;
}