/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/uint128.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

#include "../include/binomial_heap.h"

/* ---------------------------- PRIVATE FUNCTION ---------------------------- */

/**
 * Renvoie une copy de bh
 * alloue un fils de plus si b == true
*/
static binomh* copy(binomh *bh, bool b) {
	binomh *res = binomh_create(*(bh->key));
	res->childs = calloc(1,sizeof(binomh) * (bh->degre + (b == true)));
	if (res == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc copy childs\n");
		exit(EXIT_FAILURE);
	}
	*(res->key) = *(bh->key);
	res->degre = bh->degre;
	for (size_t i = 0; i < bh->degre; i++) {
        	res->childs[i] = *copy(&(bh->childs[i]), false);
    	}

	return res;
}

/**
 * Fonctions d'affichage
*/
static void print_head(int depth, int addr) {
	if (depth > 1) {
		int pre = addr / 2;
		print_head(depth - 1, pre);
		printf("%s", (pre % 2) != (addr % 2) ? "|    " : "     ");
		return;
    	}
    	if (depth == 1)
		printf ("     ");
}

#define BUF_UINT128_LEN_B10 38

static void pretty_rec(binomh *bh, int depth, int addr) {
	if (binomh_is_empty(bh)) {
		print_head(depth, addr);
		printf("|----N\n");
		return;
    	}

	for (size_t i = 0; i < bh->degre/2; i++) {
    	pretty_rec(&(bh->childs[i]), depth + 1, 2 * addr + i);
	}

	print_head(depth, addr);
    char c = (depth == 0) ? '-' : '|';
    char buf[BUF_UINT128_LEN_B10] = { 0 };
    uint128_to_str(*(bh->key), buf, BUF_UINT128_LEN_B10);
    printf("%c----%s\n", c, buf);
	for (size_t i = bh->degre/2; i < bh->degre; i++) {
    		pretty_rec(&(bh->childs[i]), depth + 1, 2 * addr + i);
	}
}

int powAB(int a , int k){
	int tmp = 1;
	for(int i = 0 ; i < k ; i++){
		tmp *=a;
	}

	return tmp;
}

// Affiche une clé à la sortie
void print_cle(uint128_t cle) {
	char cle_tmp[BUF_UINT128_LEN_B10] = { 0 };
	uint128_to_str(cle, cle_tmp, BUF_UINT128_LEN_B10);
	printf(" %s ", cle_tmp);
}

bool is_nodeHeap(binomh * node){
	printf("\nNode : \n");
	binomh_print(node);
	printf("\nFor(int i = 0 ; i < node->degre -1 ( %ld ) ; i ++ )\n",node->degre - 1);
	if(node->degre > 0){
		for(int i = 0; i < node->degre -1 ;i++){
				binomh * child_1 = &node->childs[i];
				binomh * child_2 = &node->childs[i+1];
				printf("\nChild_1 : \n");
				binomh_print(child_1);
				printf("\nChild_2 : \n");
				binomh_print(child_2);
				printf("\nIf (node->childs[%d].degre > node->childs[%d].degre) : %b\n",i,i+1,(node->childs[i].degre) > (node->childs[i+1].degre));
				if((child_1->degre) > (child_2->degre)){
					printf("\nFalse\n");
					return false;
				}
				printf("\nNode->key : \n");
				print_cle(*(node->key));
				printf("\nChild_1->key : \n");
				print_cle(*(child_1->key));
				printf("\nChild_2->key : \n");
				print_cle(*(child_2->key));
				printf("\nIf (!inf(*(node->childs[%d].key),*(node->childs[%d].key))) : %b\n",i,i+1,inf(*(child_1->key),*(node->key)) && inf(*(child_2->key),*(node->key)));
				if(inf(*(child_1->key),*(node->key)) && inf(*(child_2->key),*(node->key))){
					printf("\nFalse\n");
					return false;
				}
			}
	}

	return true;
}

bool is_binomT(binomh * tree){
	printf("\nIf tree == Null %b\n",tree == NULL);
	if (tree == NULL) {
	        return true; // Un arbre vide est également considéré comme un tournoi binomial
	}

	printf("\nFor(int i = 0 ; i < tree->degre ( %ld ) ; i ++ )\n",tree->degre);
	for(int i = 0 ; i < tree->degre ; i++){
		printf("\nIf (is_nodeHeap(&tree->childs[%d]))\n",i);
		if(is_nodeHeap(&tree->childs[i])){
			printf("\nReturn is_binomT(&tree->childs[%d]\n",i);
			is_binomT(&tree->childs[i]);
		}else{
			printf("\nFalse\n");
			return false;
		}
	}

	return true;
}

/* ---------------------------- PUBLIC FUNCTIONS ---------------------------- */

binomh* binomh_create_empty() {
	binomh *bh = calloc(1, sizeof(binomh));
	if (bh == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc create bh empty");
		exit(EXIT_FAILURE);
	}
	return bh;
}

binomh* binomh_create(uint128_t k) {
	binomh *bh = binomh_create_empty();
	bh->key = calloc(1, sizeof(uint128_t));
	if (bh->key == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc create bh empty");
		exit(EXIT_FAILURE);
	}
	*(bh->key) = k;
	bh->degre = 0;
	return bh;
}

void binomh_free(binomh *bh) {
	if (bh == NULL)
		return;
	for (size_t i = 0; i < bh->degre; i++)
		binomh_free(&(bh->childs[i]));
	free(bh->key);
	free(bh);
}

bool binomh_is_empty(binomh *bh) {
	return bh == NULL || bh->key == NULL;
}

binomh* binomh_union(binomh *bh1, binomh *bh2) {
	if (binomh_is_empty(bh1)){
		return copy(bh2, false);
	}
	if (binomh_is_empty(bh2)){
		return copy(bh1, false);
	}

	binomh *res;
	if (inf(*(bh1->key), *(bh2->key)) == true) {
		res = copy(bh1, true);
		res->childs[res->degre] = *copy(bh2, false);
	}
	else {
		res = copy(bh2, true);

		res->childs[res->degre] = *bh1;
	}
	res->degre++;

	/*for(int i = 0 ; i< res->degre ; i++){
		printf("Binomh_union -- Childs :\n");
		binomh_print(&res->childs[i]);
		printf("\n");
	}

	printf("Binomh_union -- res :\n");
	binomh_print(res);
	printf("\n");*/

	return res;
}

binomh* binomK_create(uint128_t* arrayCles, int k){
	int nb = 0 ;
	int i = 0;

	bool booltmp=false;

	binomh *uni;


	binomh * tmpArray = (binomh*)malloc(2*powAB(2,k)*sizeof(binomh) );
	binomh *bh = binomh_create_empty();

	if (tmpArray == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc copy childs\n");
		exit(EXIT_FAILURE);
	}


	 while (i < powAB(2,k)) {
		 binomh* tmp = binomh_create(arrayCles[i]);
	     bh = binomh_union(bh, tmp);
	     uni=bh;
	     if (nb > 0 ){
	    	 booltmp=false;
	    	 //uni=bh;
	    	 for(int k = nb-1 ; k >= 0 ; k--){
	    		if (tmpArray[k].degre == uni->degre) {
	    		 	uni = binomh_union(&tmpArray[k], uni);
	    		 	booltmp=true;
	    		 	if(k==0){
	    		 		tmpArray[k] = *uni;
	    		 		nb = 1;
	    		 	}else if(tmpArray[k-1].degre > uni->degre){
	    		 		tmpArray[k] = *uni;
	    		 		nb = k+1;
	    		 	}
	    		}else{
	    			if(bh->degre >0 && !booltmp){
	    				tmpArray[nb++] = *uni;
	    				bh=binomh_create_empty();
	    			}else if(booltmp){
	    				bh=binomh_create_empty();
	    			}
	    			break;
	    		}
	    	}
	     }
	     if(bh->degre >0 && !booltmp){
	    	 tmpArray[nb++] = *bh;
	     	 bh=binomh_create_empty();
	     }else if(booltmp){
			bh=binomh_create_empty();
	     }
	     i++;
	 }

	return uni;
}


bool isBinomialHeap(binomh *heap) {
    if(heap != NULL) {
        if (!is_binomT(heap)) {
            return false; // Si l'un des arbres n'est pas un tournoi binomial, retourne faux
        }

    }

    return true; // Tous les arbres sont des tournois binomiaux
}

void binomh_print(binomh *bh) {
    pretty_rec(bh, 0, 0);
}

/* -------------------------------------------------------------------------- */
