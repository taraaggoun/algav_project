#include "binomial_heap.h"

typedef struct binomial_queue {
	size_t nb_elem;
	size_t nb_bh;
	struct binomial_heap *bh;

} binomq;

binomq* binomq_create_empty();
binomq* binomq_create(binomh * heaps, int len);
void binomq_free(binomq *bq) ;
bool binomq_is_empty(binomq *bq);
void binomq_print(binomq *bq);
binomq * reste(binomq * bq);
binomq * ajoutMin(binomq * bq,binomh *heap);
binomq * unionQueue(binomq *A,binomq *B);
binomh * minDeg(binomq * bq);
