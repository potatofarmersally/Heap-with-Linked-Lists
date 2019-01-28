/*
 * mallok.c
 *
 *  Created on: May 21, 2018
 *      Author: Sally Ho
 */

#include "mallok.h"
#define NOT_FREE 0
#define FREE 1
// points to the beginning of the list
static Node *head = NULL;
//the actual heap.
static void *heap = NULL;

/*
 * This creates a pool of memory in a heap of
 * whatever the size declared is.
 */
void create_pool(int size) {
	//check if the head and heap are null
	if(head == NULL && heap == NULL) {
		//if there's nothing, allocate the size.
		heap = malloc(size);
		if(heap != NULL) { //if there is something inside the heap
			head = malloc(sizeof(Node)); //allocate the head,
			head->address = heap; //set the address to the heap.
			head->byteSize = size; // size the size.
			head->free = FREE; //the memory is free to use!
			head->next = NULL; //the next pointer is null.
		}
	}
}


/*
 * Allocate a certain size of memory,
 * returns a void pointer to the address of the malloc'd area.
 */
void *my_malloc(int size) {
	Node *scan = head, *newNode;
	void *returnResult = NULL;
	while(scan != NULL && (scan->byteSize < size ||
			scan->free == NOT_FREE)) { //while it's not available NOT_FREE?
		scan = scan->next; //keep scanning
	}
	if(scan!= NULL && scan->byteSize > size && scan->free == FREE) {
		newNode = malloc(sizeof(Node));
		newNode->address = scan->address + size;
		newNode->byteSize = scan->byteSize - size;
		newNode->free = FREE;
		newNode->next = scan->next;
		scan->byteSize = size;
		scan->free = NOT_FREE;
		scan->next = newNode;
		returnResult = scan->address;
	} else if(scan != NULL && scan->byteSize == size && scan->free == FREE) {
		scan->free = NOT_FREE;  //set availability to false,
		returnResult = scan->address;
	}
	return returnResult;
}
/**
 * Frees a specific block of memory and coalesce's the
 * neighboring blocks and stuff.
 */
void my_free(void *theBlock) {
	Node *current, *nextNode, *prev = NULL;
	current = head;
	while (current != NULL && current->address != theBlock) {
		prev = current;
		current = current->next;
	}
	if (current != NULL && current->address == theBlock &&
	    current->free == NOT_FREE) {
		current->free = FREE;
		nextNode = current->next;
		if (nextNode != NULL && nextNode->free == FREE) {
			current->byteSize += nextNode->byteSize;
			current->next = nextNode->next;
			free(nextNode);
		}
		if (prev != NULL && prev->free == FREE) {
			prev->byteSize += current->byteSize;
			prev->next = current->next;
			free(current);
		}
	}
}

/*
 * Frees the entire pool
 */
void free_pool() {
	Node *temp;
	while(head != NULL) {
		temp = head;
		head = head->next;
		temp->next = NULL;
		free(temp);
	}
	free(head);
	free(heap);
	heap = NULL;
}
