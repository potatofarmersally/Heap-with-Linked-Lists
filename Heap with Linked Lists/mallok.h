/*
 * mallok.h
 *
 *  Created on: May 21, 2018
 *      Author: Sally Ho
 */

#ifndef MALLOK_H
#define MALLOK_H
#include <stdlib.h>
#include <stdio.h>
//node struct for node related manipulation.
struct node {
	void *address; //the address of the pointer.
	unsigned int byteSize; //can't have negative bytes.
	int free; //determines if it's free or not
	struct node *next; //good ol' next.
};

typedef struct node Node, List;

/*
 * this creates a pool of the TOTAL byte size.
 */
void create_pool(int size);
/*
 * my_malloc should allocate memory for
 * a certain amount of bytes.
 */
void *my_malloc(int size);
/*
 * frees certain amount of memory.
 */
void my_free(void *block);
/*
 * Frees basically everything.
 */
void free_pool();

#endif /* MALLOK_H */
