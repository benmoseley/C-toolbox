/*
 ============================================================================
 Name        : pq.h
 Author      : Ben Moseley | Adapted from Htps://rosettacode.org/wiki/Priority_queue#C
 Version     : 1.0
 Description : Implements a priority queue using binary min heap representation
 	 	 	   Supports pop, delete & insert operations, all with O(log n) pop, delete & insert time complexity

 A good simple description of priority queues is here:
 Htp://pages.cs.wisc.edu/~vernon/cs367/notes/11.PRIORITY-Q.Hml

Each node is stored in heap memory in an array by this routine.

 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct { // this struct is user defined
	int i; // add any data types you like here
	int j; // e.g. could be pointers to externally created data
} data_t;

typedef struct {
	double priority;
	data_t data;
} node_t;

// Each node is stored in heap memory in an array by this routine
typedef struct {
	node_t *nodes;
	long int len;
	long int size;
} heap_t;


void heapify(heap_t *h, long int i){
	/*
	 * Fix (heapify) the heap at index i
	 */

	double priority = h->nodes[i].priority;
	data_t data = h->nodes[i].data;

	long int j = i / 2; // index of parent (FLOOR division)

	if (i == 1 || h->nodes[j].priority < h->nodes[i].priority){// if i is root or parent smaller than i
		// filter down (move the node down the tree)

		long int k;
		while (1) {// while children are smaller, swap with smallest child
			k = i;
			j = 2 * i; // index of (1st of 2) child
			if (j <= h->len && h->nodes[j].priority < priority) {
				k = j;
			}
			if (j + 1 <= h->len && h->nodes[j + 1].priority < h->nodes[k].priority) {
				k = j + 1;// index of (2nd of 2) child; either swap with child 1 or child 2
			}
			if (k == i) {
				break;
			}
			h->nodes[i] = h->nodes[k]; // carry out the swap

			i = k;
		}
	}
	else {
		// filter up (move the node up the tree)

		while (i > 1 && h->nodes[j].priority > priority) { // while parent priority is greater than new node priority, swap nodes
			h->nodes[i] = h->nodes[j];

			i = j;
			j = j / 2;// index of next parent  (FLOOR division) (i.e. walk up the heap)
		}
	}

	h->nodes[i].priority = priority;
	h->nodes[i].data = data;

}

void push (heap_t *h, double priority, data_t data) {
	/*
	 * Insert a node into the heap.
	 */

	// Allocate more memory for heap if needed
	// Note initially h->len, h->size and h->nodes are zero (from calloc)
	if (h->len + 1 >= h->size) { // double the size of the nodes array if array is full
		h->size = h->size ? h->size * 2 : 4;
		h->nodes = (node_t *)realloc(h->nodes, h->size * sizeof (node_t));
		if (h->nodes == NULL){
			perror("Error allocating memory on heap for heap");
		}
	}

	// add new node to end of heap (note index of first element == 1  !)
	long int i = h->len + 1;
	h->nodes[i].priority = priority;
	h->nodes[i].data = data;
	h->len++;

	// fix the heap
	heapify(h, i);
}

node_t delete(heap_t *h, long int i) {
	/*
	 * Delete the node at index i from the heap.
	 * Returns node.
	 */

	if (!h->len) {
		printf("%li, %li", i, h->len);
		perror("Error deleting, Length of heap is 0\n");
		exit(-1);
	}

	if (i < 1 || i > h->len){
		printf("%li %li\n",i, h->len);
		perror("Error, i is not in nodes list");
		exit(-1);
	}

	// get data of the deleted element
	node_t node = h->nodes[i];

	h->len--;

	if (i!=h->len + 1){// if deleted node is not the end node (note this also covers the case where there is only one node in h)

		// replace the deleted node with the node at end of heap
		h->nodes[i] = h->nodes[h->len + 1];

		// fix the heap
		heapify(h, i);
	}

	return node;
}

node_t pop(heap_t *h){
	/*
	 * Pop the minimum (root) node at the top of the tree from the heap.
	 * Returns node.
	 */
	return delete(h, 1);
}
