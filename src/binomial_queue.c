#include "../graph/profiler.h"
#include "../include/binomial_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

bool binomq_is_empty(binomq *bq) {
    return bq == NULL || bq->head == NULL || binomh_is_empty(bq->head->heap);
}

binomq* binomq_create_empty() {
    binomq *queue = calloc(1, sizeof(binomq));
    if (queue == NULL) {
        fprintf(stderr, "Erreur calloc queue\n");
        exit(EXIT_FAILURE);
    }
    return queue;
}

binomq* binomq_create(binomh *bh) {
    binomq *queue = binomq_create_empty();
    queue->nb_elem = pow(2, bh->degree);

    queue->head = calloc(1, sizeof(binomq_node));
    if (queue->head == NULL) {
        fprintf(stderr, "Erreur calloc queue bh\n");
        exit(EXIT_FAILURE);
    }
    queue->head->heap = binomh_copy(bh, false);
    return queue;
}

static binomq* binomq_copy(binomq *bq) {
    if (binomq_is_empty(bq))
        return binomq_create_empty();

    binomq *copy = binomq_create_empty();
    copy->nb_elem = bq->nb_elem;

    binomq_node *source_current = bq->head;
    binomq_node *target_prev = NULL;

    while (source_current != NULL) {
        binomq_node *target_current = calloc(1, sizeof(binomq_node));
        if (target_current == NULL) {
            fprintf(stderr, "Erreur malloc copy binomq_node\n");
            exit(EXIT_FAILURE);
        }
        target_current->heap = binomh_copy(source_current->heap, false);
        if (target_prev == NULL)
            copy->head = target_current;
        else
            target_prev->next = target_current;
        target_prev = target_current;
        source_current = source_current->next;
    }
    return copy;
}

static size_t count_elem(size_t number) {
    int count = 0;
    while (number) {
        count += number & 1;
        number >>= 1;
    }
    return count;
}

void binomq_free(binomq *queue) {
    if (queue == NULL) {
        return;
    }
    binomq_node *current = queue->head;
    while (current != NULL) {
        binomq_node *next = current->next;

        if (current->heap != NULL)
            binomh_free(current->heap);

        free(current);
        current = next;
    }

    free(queue);
}

void binomq_print(binomq *bq) {
    printf("[ ");
    size_t size = bq->nb_elem;
    size_t position = 0;
    while (size != 0) {
        if (size & 1) {
            printf("B%ld ", position);
        }
        position++;
        size >>= 1;
    }
    printf("]\n");
}

binomh* binomq_suppr_min(binomq **bq) {
	clock_t cl = BEGIN_PROFILE_FUNCTION();
	if (binomq_is_empty(*bq))
        	return binomh_create_empty();

	binomh *min_heap = (*bq)->head->heap;
	binomq_node *temp = (*bq)->head;
	(*bq)->head = (*bq)->head->next;
	free(temp);

	(*bq)->nb_elem -= pow(2, min_heap->degree);

	END_PROFILE_FUNCTION((*bq)->nb_elem, cl);
    	return min_heap;
}

#include <stddef.h>

static size_t powAB(size_t a, size_t k) {
    size_t tmp = 1;
    for (size_t i = 0; i < k; i++)
        tmp *= a;
    return tmp;
}

binomq* ajout_min(binomh *bh, binomq *bq) {
    binomq_node *new_node = calloc(1, sizeof(binomq_node));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur allocation mémoire dans ajout_min\n");
        exit(EXIT_FAILURE);
    }

    new_node->heap = bh;
    new_node->next = NULL;

    if (binomq_is_empty(bq)) {
        bq = binomq_create_empty();
        bq->head = new_node;
    } else {
        binomq_node *current = bq->head;
        binomq_node *prev = NULL;
        while (current != NULL && current->heap->degree < bh->degree) {
            prev = current;
            current = current->next;
        }
        if (prev == NULL) {
            new_node->next = bq->head;
            bq->head = new_node;
        } else {
            new_node->next = current;
            prev->next = new_node;
        }
    }

    bq->nb_elem += pow(2, bh->degree);
    return bq;
}

binomq* reste(binomq *bq) {
    if (binomq_is_empty(bq)) {
        fprintf(stderr, "Erreur dans reste : la file est vide\n");
        exit(EXIT_FAILURE);
    }

    binomq_node *min_node = bq->head;
    binomq_node *prev = NULL;
    binomq_node *current = bq->head;

    while (current->next != NULL) {
        if (current->next->heap->degree < min_node->heap->degree) {
            min_node = current->next;
            prev = current;
        }
        current = current->next;
    }
    if (prev == NULL)
        bq->head = min_node->next;
    else
        prev->next = min_node->next;

    free(min_node);
    return bq;
}

binomq* u_fret(binomq *bq1, binomq *bq2, binomh *bh);

binomq* binomq_union(binomq* bq1, binomq* bq2) {
	clock_t cl = BEGIN_PROFILE_FUNCTION();
	// binomq *bq = u_fret(bq1, bq2, binomh_create_empty());
	END_PROFILE_FUNCTION(bq1->nb_elem + bq2->nb_elem, cl);
	return NULL;
}

binomq* u_fret(binomq *bq1, binomq *bq2, binomh *bh) {
    if (binomh_is_empty(bh)) {
        if (binomq_is_empty(bq1))
            return binomq_copy(bq2);
        if (binomq_is_empty(bq2))
            return binomq_copy(bq1);

        binomh *bh1 = bq1->head->heap;
        binomh *bh2 = bq2->head->heap;

        if (bh1->degree < bh2->degree)
            return ajout_min(bh1, u_fret(reste(bq1), bq2, NULL));
        else if (bh2->degree < bh1->degree)
            return ajout_min(bh2, u_fret(reste(bq2), bq1, NULL));
        else if (bh1->degree == bh2->degree) {
            binomq* rest_union = binomq_union(reste(bq1), reste(bq2));
            return ajout_min(bh1, ajout_min(bh2, rest_union));
        }
    } else {
        if (binomq_is_empty(bq1))
            return binomq_union(binomq_create_empty(), bq2);
        if (binomq_is_empty(bq2))
            return binomq_union(binomq_create_empty(), bq1);

        binomh *bh1 = bq1->head->heap;
        binomh *bh2 = bq2->head->heap;

        if (bh->degree < bh1->degree && bh->degree < bh2->degree)
            return ajout_min(bh, binomq_union(bq1, bq2));
        else if (bh->degree == bh1->degree && bh->degree == bh2->degree) {
            binomq* rest_union = binomq_union(reste(bq1), reste(bq2));
            return ajout_min(bh, rest_union);
        }
        else if (bh->degree == bh1->degree && bh->degree < bh2->degree)
        {
            binomq* rest_union = binomq_union(reste(bq1), bq2);
            return ajout_min(bh, rest_union);
        }
        else if (bh->degree == bh2->degree && bh->degree < bh1->degree)
        {
            binomq* rest_union = binomq_union(reste(bq2), bq1);
            return ajout_min(bh, rest_union);
        }
    }
}

void binomq_ajout(binomq **bq, binomh *bh) {
	clock_t cl = BEGIN_PROFILE_FUNCTION();

    if (binomq_is_empty(*bq)) {
        *bq = binomq_create(bh);
        return;
    }
    binomq *bq1 = binomq_create(bh);
//     *bq = binomq_union(*bq, bq1);
	END_PROFILE_FUNCTION((*bq)->nb_elem, cl);
}

binomq* binomq_construction(binomh **bh, size_t len) {
	clock_t cl = BEGIN_PROFILE_FUNCTION();
	size_t cmp = 0;
	binomq *bq = binomq_create_empty();
	for (size_t i = 0; i < len; i++) {
		cmp += pow(2, bh[i]->degree);
		binomq_ajout(&bq, bh[i]);
	}
	END_PROFILE_FUNCTION(len, cl);
}


// int main() {
//     uint128_t u = { 0 };
//     u.low = 6;
//     uint128_t u2 = { 0 };
//     u2.low = 7;
//     binomh *bh = binomh_create(u);
//     binomq *bq = binomq_create(bh);
//     binomq_print(bq);
//     binomq *bq2 = binomq_copy(bq);
//     binomq_print(bq2);
//     binomh_print(bq2->head->heap);
//     binomh *sup = binomq_suppr_min(&bq2);
//     binomh_print(sup);
//     binomq_print(bq2);
//     binomh *bh2 = binomh_create(u2);
//     binomq_ajout(&bq2, bh2);
//     binomq_print(bq2);
//     binomh_print(bq2->head->heap);

//     binomh_free(sup);
//     binomq_free(bq2);
//     binomh_free(bh);
//     binomq_free(bq);
//     return 0;
// }
