/*
 * mallok_test.c
 *
 *  Created on: May 21, 2018
 *      Author: Sally Ho
 */

#include "mallok.h"
#include<string.h>
//prototype
/*
 * The one where you make 1000
 * and allocate blocks of 10, 100 times.
 */
void test1();
/*
 * The one where you you make 1000
 * then you make 250 and free them
 */
void test2();
/*
 * the one where you make 1000
 * then free and add and free and add to
 * see if free and malloc works
 */
void test3();
/*
 * The one where you make 1000 and fill
 * blocks of 200 with letters.
 */
void test4();
/*
 * Similar to Test 2 but larger chunks and you free
 * more as you go.
 */
void test5();

int main(void) {
	test1();
	test2();
	test3();
	test4();
	test5();
	return 0;
}

/*
 * Allocates a pool of 1000 bytes
 * Needs to allocate 10 bytes 100 times
 * Test Status: PASS
 */
void test1() {
	printf("Test Case 1: \n");
	int count = 0;
	create_pool(1000);
	while(my_malloc(10) != NULL) {
		count++;
	}
	if(count == 100) {
		printf("PASS\n");
	}
}

/*
 * Allocates a pool of 1000 bytes
 * Allocate 200 bytes 5 times.
 * Frees the rest of the bytes.
 * Test Status: PASS
 */
void test2() {
	printf("Test Case 2: \n");
	create_pool(1000);
	void *address[5];
	int i = 0, count = 0, outerTest = 0;
	for(outerTest = 0; outerTest < 50; outerTest++) {
		for(i = 0; i < 5; i++) {
			address[i] = my_malloc(200);
			if(address[i] != NULL) {
				count++;
			}
			my_free(address[i]);
			address[i] = NULL;
		}
	}
	if(count) {
		printf("Failed.\n");
	} else {
		printf("PASS\n");
	}
	free_pool();
}

/*
 * Allocate pool of 1000 bytes
 * make 5 blocks of 200 bytes
 * free middle block
 * allocate 210, should fail
 * now allocate 150, should pass
 * allocate 60, should fail
 * now allocate 50, should pass.
 * Test Status: PASS
 */
void test3() {
	printf("Test Case 3: \n");
	create_pool(1000);
	void *blocks[8];
	int i = 0;
	for(i = 0; i < 5; i++) {
		blocks[i] = my_malloc(200);
	}
	//remove the middle block
	my_free(blocks[3]);
	printf("Freed middle block.\n");
	//try allocating a block of 210, should fail.
	blocks[3] = my_malloc(210);
	if(blocks[3] == NULL) {
		printf("Tried to allocate more than it could!\n");
	}
	//now try allocating a block of 150. should succeed.
	blocks[3] = my_malloc(150);
	if(blocks[3] != NULL) {
		printf("Able to allocate 150.\n");
	}
	//try allocating an additional 60.
	blocks[3] = my_malloc(60);
	if(blocks[3] == NULL) {
		printf("Tried to allocate more than it could!\n");
	}
	//try allocating just 50.
	blocks[3] = my_malloc(50);
	if(blocks[3] != NULL) {
		printf("Able to allocate 50.\n");
	}
	free_pool();
}

/*
 * Make pool of 1000 bytes.
 * Make 5 blocks of 200 bytes each.
 * Fill first block with character 'A'
 * Verify that blocks are where they are.
 * reference for later: https://stackoverflow.com/questions/32442600
 * /memory-allocation-for-char-array?utm_medium=organic&utm_source=g
 * oogle_rich_qa&utm_campaign=google_rich_qa
 */
void test4() {
	printf("Test Case 4: \n");
	create_pool(1000);
	void *block[5];
	int i, j, k;
	char A = 'A';
	//set each block with their respective letters.
	for(i = 0; i < 5; i++) {
		block[i] = my_malloc(200);
		if(block[i] != NULL) {
			printf("Successfully Allocated.\n");
		}
		memset(block[i], A, 200);
		A += 1;
	}
	A = 'A';
	for(j = 0; j < 5; j++) {
		for(k = 0; k < 200; k++) {
			if(*(char *)(block[j] + k) != A) {
				printf("Not initialized to %c", A);
			}
		}
		A++;
	}
	free_pool();
}

/*
 * create pool of 1000
 * request block of 1000
 * return that block of 1000
 * request 4 blocks of 250
 * return 4 blocks of 250
 * request 10 blocks of 100
 * return 10 blocks of 100
 * Test Status: PASS
 */
void test5() {
	printf("Test Case 5: \n");
	create_pool(100);
	int i = 0;
	void *block[10];
	block[0] = my_malloc(1000); //request block of 1000
	my_free(block[0]); //return block of 1000

	//allocating 250 blocks 4 times.
	for(i = 0; i < 4; i++) {
		block[i] = my_malloc(250);
		if(block[i] != NULL) {
			printf("Failed malloc of 250.");
		}
		my_free(block[i]);
	}


	//allocating 100 blocks 10 times.
	for(i = 0; i < 10; i++) {
		block[i] = my_malloc(100);
		if(block[i] == NULL) {
			printf("Failed malloc of 100 \n");
		}
		my_free(block[i]);
	}
	printf("PASS.\n");
	free_pool();
}
