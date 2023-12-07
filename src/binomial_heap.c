/* -------------------------------- INCLUDES -------------------------------- */

#include "../include/uint128.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "../include/binomial_heap.h"

/* ---------------------------- PRIVATE FUNCTION ---------------------------- */

/**
 * Renvoie une copy de bh
 * alloue un fils de plus si b == true
*/
static binomh* copy(binomh *bh, bool b) {
	binomh *res = binomh_create(*(bh->key));
	res->childs = (binomh*)malloc(sizeof(binomh) * (bh->degre + (b == true)));
	if (res == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc copy childs\n");
		exit(EXIT_FAILURE);
	}
	*(res->key) = *(bh->key);
	res->degre = bh->degre;
	memcpy(res->childs, bh->childs, bh->degre * sizeof(binomh));

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
			printf("i = %ld",i);
    		pretty_rec(&(bh->childs[i]), depth + 1, 2 * addr + i);
	}
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
		binomh_free(bh->childs);
	free(bh->key);
	free(bh);
}

bool binomh_is_empty(binomh *bh) {
	return bh == NULL || bh->key == NULL;
}

binomh* binomh_union(binomh *bh1, binomh *bh2) {
	if (binomh_is_empty(bh1))
		return copy(bh2, false);
	if (binomh_is_empty(bh2))
		return copy(bh1, false);

	binomh *res;
	if (inf(*(bh1->key), *(bh1->key)) == true) {
		res = copy(bh1, true);
		res->childs[res->degre] = *bh2;
	}
	else {
		res = copy(bh2, true);
		res->childs[res->degre] = *bh1;
	}
	res->degre++;
	return res;
}

binomh* binomK_create(uint128_t* arrayCles, int k){
	int nb = 0 ;
	int i = 0;
	binomh *uni;

	binomh * tmpArray = (binomh*)malloc(16*sizeof(binomh) );
	binomh *bh = binomh_create_empty();

	if (tmpArray == NULL) {
		dprintf(STDERR_FILENO, "Erreur calloc copy childs\n");
		exit(EXIT_FAILURE);
	}


	 while (i < 8) {
		 binomh* tmp = binomh_create(arrayCles[i]);
		 printf("TMP : ");
		 binomh_print(tmp);
		 printf("\nUNI : ");
	     uni = binomh_union(bh, tmp);
	     binomh_print(uni);
	     printf("\nUNI 2 : ");
	     if (nb > 0 ){
	    	 printf("if nb > 0\n");
	    	 if (tmpArray[nb - 1].degre == uni->degre) {
	    		 printf("degre = degre\n");
		    	 uni = binomh_union(&tmpArray[nb - 1], tmp);
		    	 binomh_print(uni);
		    	 printf("1\n ");
		    	 tmpArray[nb - 1] = *uni;
	    	 }else{
	    		 tmpArray[nb++] = *uni;
	    		 binomh_print(uni);
	    		 printf("2\n ");
	    	 }
	     } else {
	         tmpArray[nb++] = *uni;
	         binomh_print(uni);
	         printf("3\n ");
	     }
	     i++;
	 }

	return uni;
}

void binomh_print(binomh *bh) {
    pretty_rec(bh, 0, 0);
}

/* -------------------------------------------------------------------------- */
