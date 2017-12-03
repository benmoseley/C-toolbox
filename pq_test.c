/*
 ============================================================================
 Name        : pq_test.h
 Author      : Ben Moseley | Adapted from Htps://rosettacode.org/wiki/Priority_queue#C
 Version     : 1.0
 Description : Tests priority queue in pq.h

 A good simple description of priority queues is here:
 Htp://pages.cs.wisc.edu/~vernon/cs367/notes/11.PRIORITY-Q.Hml

 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

void print_heap(heap_t *h){
	/*
	 * print the contents of the heap for testing
	 *
	 */
	// get depth of tree
	int s = 1;
	int d = 0;
	while (s <= h->len){
		s *=2;
		d++;
	}

	int j = 1;
    for (int i = 1; i < h->len + 1; i++) {
		if (i == j){
			if (i!=1){
				printf("\n");
				s /= 2;}
			j *= 2;
			for (int t = 0; t < (s/2) - 1; t++){
				printf("\t");
			}
		}
		else {
			for (int t = 0; t < s; t++){
				printf("\t");
			}
		}
		printf("%.2f", h->nodes[i].priority);
    }
    printf("\n\n\n\n");
}


int main () {
    heap_t *h = (heap_t *)calloc(1, sizeof (heap_t)); // note calloc sets the value of the memory to 0
    push(h, 1.2, (data_t){.i = 1, .j = 2});
    push(h, -1.6, (data_t){.i = 3, .j = 5});
    push(h, -100.0, (data_t){.i = 4, .j = 5});
    push(h, 1.3, (data_t){.i = 2, .j = 3});
    push(h, 1.1, (data_t){.i = 5, .j = 4});
    push(h, 1.5, (data_t){.i = 3, .j = 2});
    print_heap(h);
    node_t node = delete(h, 6);
    print_heap(h);
    for (int i = 0; i < 5; i++) {
    		node_t node = pop(h);
        printf("%i, %i\n", node.data.i, node.data.j);
        print_heap(h);
    }
    return 1;
}
