#include "include/binomial_heap.h"

typedef struct binomial_queue {
	size_t nb_elem;
	struct binomial_heap *bh;

} binomq;