#include "binomial_heap.h"

typedef struct binomial_queue_node {
	binomh *heap;
	struct binomial_queue_node *next;
} binomq_node;
typedef struct binomial_queue {
	size_t nb_elem;
	struct binomial_queue_node *head;
} binomq;

bool binomq_is_empty(binomq *bq);
binomq* binomq_create_empty();
binomq* binomq_create(binomh *bh);
void binomq_free(binomq *queue);
void binomq_print(binomq *bq);
binomh* binomq_suppr_min(binomq **bq);
binomq* binomq_union(binomq* bq1, binomq* bq2);
void binomq_ajout(binomq **bq, binomh *bh);
binomq* binomq_construction(binomh **bh, size_t len);