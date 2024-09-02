/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA1
* ListTest.c
* Test client for List ADT
****************************************/

#include "List.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int main(int argc, char **argv) { 

	printf("----------Test Begin----------\n");
	printf("\n");
	
	List A = newList();
	List B = newList();
	List C = NULL;
	List D = newList();
	List E = newList();
	int i;
	
	int a[] = {1, 22, 333, 4444, 55555, 666666, 7777777};
	
	for (i = 0; i < sizeof(a)/sizeof(a[0]); i++) { 
	
		append(A, a[i]);
		prepend(B, a[i]);
	
	}
	
	
	int b[] = {123, 456, 789, 0, 987, 654, 321};
	
	for (i = 0; i < sizeof(b)/sizeof(b[0]); i++) { 
	
		append(D, b[i]);
		prepend(E, b[i]);
	
	}
	
	printList(stdout, A);
	printf("\n");
	printList(stdout, B);
	printf("\n");
	printList(stdout, D);
	printf("\n");
	printList(stdout, E);
	printf("\n");
	
	deleteFront(A);
	deleteFront(B);
	deleteBack(D);
	deleteBack(E);
	
	for(moveFront(A); index(A) >= 0; moveNext(A)) { 
	
		printf("%d", get(A));
		printf(" ");
	
	}
	printf("\n");
	
	for (moveBack(B); index(B) >= 0; movePrev(B)) { 
	
		printf("%d", get(B));
		printf(" ");
	
	}
	printf("\n");
	
	for (moveFront(D); index(D) >= 0; movePrev(D)) { 
	
		printf("%d", get(D));
		printf(" ");
	
	}
	printf("\n");
	
	for (moveBack(E); index(E) >= 0; movePrev(E)) { 
	
		printf("%d", get(E));
		printf(" ");
	
	}
	printf("\n");
	
	C = copyList(A);
	printf("%s\n", equals(A,B) ? "ture" : "false");
	printf("%s\n", equals(B,C) ? "ture" : "false");
	printf("%s\n", equals(C,A) ? "ture" : "false");
	
	moveFront(A);
	for (i = 0; i < 2; i++) { 
	
		moveNext(A);
	
	}
	
	insertBefore(A, -1);
	
	// Test cursors
	
	insertBefore(E, -5);
	printList(stdout, D);
	printf("\n");
	printList(stdout, E);
	printf("\n");
	
	printf("%d\n", length(D));
	printf("%d\n", length(E));
	
	for (i = 0; i < 2; i ++) { 
	
		moveNext(A);
	
	}
	
	insertAfter(A, -2);
	
	for (i = 0; i < 2; i++) { 
	
		movePrev(A);
	
	}
	
	delete(A);
	printList(stdout, A);
	printf("\n");
	printf("%d\n", length(A));
	clear(A);
	printf("%d\n", length(A));
	
	freeList(&A);
	freeList(&B);
	freeList(&C);
	freeList(&D);
	freeList(&E);
	
	printf("\n");
	printf("----------Test End----------\n");
	
	return 0;

}


/****************************************
Output of this program:
----------Test Begin----------

1 22 333 4444 55555 666666 7777777 
7777777 666666 55555 4444 333 22 1 
123 456 789 0 987 654 321 
321 654 987 0 789 456 123 
22 333 4444 55555 666666 7777777 
1 22 333 4444 55555 666666 
123 
456 789 0 987 654 321 
false
false
ture
123 456 789 0 987 654 
321 654 987 0 789 456 
6
6
22 333 -1 55555 666666 -2 7777777 
7
0

----------Test End----------
****************************************/


