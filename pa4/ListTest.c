/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA4
* ListTest.c
* Test client for List ADT
****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "List.h"

int main(int argc, char **argv) {
   
	List A = newList();
	List B = newList();
	List C = newList();
   
	printf("---------- Test Begin ----------\n");
	printf("\n");
	
	int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int u = -1, v = -2, w = -3;
	bool equal = false;
	
	
	// Initialize List A and List B
	for (int i = 1; i <= 20; i++) { 
   
		append(A, &X[i]);
		prepend(B, &X[i]);
   
	}
   
   
	// Print List A and List B
	for (moveFront(A); index(A) >= 0; moveNext(A)) { 
   
		printf("%d ", *(int*)get(A));
   
	}
	printf("\n");
   
	for (moveFront(B); index(B) >= 0; moveNext(B)) { 
   
		printf("%d ", *(int*)get(B));
   
	}
	printf("\n");
   
   
	for (moveBack(A); index(A) >= 0; movePrev(A)) { 
   
		printf("%d ", *(int*)get(A));
   
	}
	printf("\n");
   
	for (moveBack(B); index(B) >= 0; movePrev(B)) { 
   
		printf("%d ", *(int*)get(B));
   
	}
	printf("\n");
   
   
	moveFront(A);
   
	while (index(A) >= 0) { 
   
		append(C, get(A));
		moveNext(A);
   
	}
   
   
	for (moveFront(C); index(C) >= 0; moveNext(C)) { 
   
		printf("%d ", *(int*)get(C));
   
	}
	printf("\n");
	printf("\n");
	
	
	// Test List A and List C by comparing pointers
	equal = (length(A) == length(C));
	moveFront(A);
	moveFront(C);
	
	while (index(A) >= 0 && equal) { 
	
		equal = (get(A) == get(C));
		moveNext(A);
		moveNext(C);
	
	}   
	printf("A equals C is %s\n", (equal ? "ture" : "false"));
	printf("\n");
	
	
	moveFront(A);
	
	for (int i = 0; i < 5; i++) { 
	
		moveNext(A);
	
	}
	
	printf("index(A) = %d\n", index(A));
	
	insertBefore(A, &u);
	
	printf("index(A) = %d\n", index(A));
	
	for (int i = 0; i < 9; i++) { 
	
		moveNext(A);
	
	}
	
	printf("index(A) = %d\n", index(A));
	
	insertAfter(A, &v);
	
	printf("index(A) = %d\n", index(A));
	
	for (int i = 0; i < 5; i++) { 
	
		movePrev(A);
	
	}
	
	printf("index(A) = %d\n", index(A));
	
	delete(A);
	
	printf("index(A) = %d\n", index(A));
	
	moveBack(A);
	
	printf("index(A) = %d\n", index(A));
	
	for (int i = 0; i < 10; i++) { 
	
		movePrev(A);
	
	}
	
	printf("index(A) = %d\n", index(A));
	printf("\n");
	
	set(A, &w);
	
	
	for (moveFront(A); index(A) >= 0; moveNext(A)) { 
	
		printf("%d ", *(int*)get(A));
	
	}
	printf("\n");
	
	for (moveBack(A); index(A) >= 0; movePrev(A)) { 
	
		printf("%d ", *(int*)get(A));
	
	}
	printf("\n");
	
	
	// Test length of A, and after clear(A)
	printf("%d\n", length(A));
	clear(A);
	printf("%d\n", length(A));
	printf("\n");
	
	
	List D = newList();
	int x = 1, y = 2, z = 3, a = 5, b = 6;
	
	append(D, &x);
	moveFront(D);
	set(D, &y);
	moveBack(D);
	set(D, &z);
	append(D, &y);
	prepend(D, &z);
	insertBefore(D, &a);
	insertAfter(D, &b);
	printList(stdout, D);
	freeList(&D);
	
	
	// Test Index
	List E = newList();
	
	for (int i = 0; i < 10; i++) { 
	
		append(E, &i);
	
	}
	
	moveFront(E);
	
	for (int i = 0; i < 10; i++) { 
	
		if (index(E) != i) { 
		
			printf("Test Index: Failed\n");
			break;
		
		}
		
		moveNext(E);
	
	}
	
	freeList(&E);
	
	printf("Test Index: Passed\n");
	
	
	// Test set and get
	List F = newList();
	
	for (int i = 0; i < 10; i++) { 
	
		append(F, &i);
	
	}
	
	moveFront(F);
	
	for (int i = 0; i < 10; i++) { 
	
		set(F, &i);
		
		if (*((int *)get(F)) != i) { 
		
			printf("Test Set and Get: Failed\n");
			break;
		
		}
		
		moveNext(F);
	
	}
	
	freeList(&F);
	printf("Test Set and Get: Passed\n");
	
	
	printf("\n");
	printf("---------- Test End ----------\n");
	
	
	// Free all Lists
	freeList(&A);
	freeList(&B);
	freeList(&C);
	
	return 0;

}

/****************************************
Output of this Test:
---------- Test Begin ----------

1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 

A equals C is ture

index(A) = 5
index(A) = 6
index(A) = 15
index(A) = 15
index(A) = 10
index(A) = -1
index(A) = 20
index(A) = 10

1 2 3 4 5 -1 6 7 8 9 -3 12 13 14 15 -2 16 17 18 19 20 
20 19 18 17 16 -2 15 14 13 12 -3 9 8 7 6 -1 5 4 3 2 1 
21
0

3 5 3 6 2 
Test Index: Passed
Test Set and Get: Passed

---------- Test End ----------
****************************************/

