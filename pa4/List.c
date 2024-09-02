/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA4
* List.c
* List for List ADT
****************************************/

#include "List.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct NodeObj *Node;

typedef struct NodeObj { 

	void* data;
	struct NodeObj* prev;
	struct NodeObj* next;

} NodeObj;

typedef struct ListObj { 

	Node front;
	Node back;
	Node cursor;
	int length;
	int index;

} ListObj;

bool isEmpty(List L) { 

	if (L == NULL) { 
	
		printf("List Error: calling isEmpty() on NULL List\n");
		exit(EXIT_FAILURE);
	
	}
	
	return(L -> length == 0);

}

// Constructors-Destructors --------------------

// newNode() 
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(void* data) { 

	Node N = malloc(sizeof(NodeObj));
	assert(N != NULL);
	N -> data = data;
	N -> next = NULL;
	return(N);

}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN) { 

	if(pN != NULL && *pN != NULL) { 
	
		free(*pN);
		*pN = NULL;
	
	}

}

// Creates and returns a new empty List.
List newList(void) { 

	List L = malloc(sizeof(ListObj));
	L -> front = NULL;
	L -> back = NULL;
	L -> cursor = NULL;
	L -> index = -1;
	L -> length = 0;
	return L;

}

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL) { 

	if (pL != NULL && *pL != NULL) { 
	
		while(!isEmpty(*pL)) { 
		
			deleteFront(*pL);
		
		}
		
		free(*pL);
		*pL = NULL;
	
	}

}


// Access functions --------------------

// Returns the number of elements in L.
int length(List L) { 

	if (L == NULL) { 
	
		printf("List Error: calling length() on NULL List\n");
		exit(EXIT_FAILURE);
	
	}
	
	return(L -> length);

}

// Returns index of cursor element if deefined, -1 otherwise.
int index(List L) { 

	if (L == NULL) { 
	
		return -1;
	
	}
	
	return(L -> index);

}

// Returns front element of L. Pre: length() > 0
void* front(List L) { 

	if (length(L) == 0) { 
	
		fprintf(stderr, "front() called on empty List\n");
		exit(EXIT_FAILURE);
	
	}
	
	return(L -> front -> data);

}

// Returns back element of L. Pre: length() > 0
void* back(List L) { 

	if (length(L) == 0) { 
	
		fprintf(stderr, "back() called on empty List\n");
		exit(EXIT_FAILURE);
	
	}
	
	return(L -> back -> data);

}

// Returns cursor element of L. Pre: length() > 0
void* get(List L) { 

	if (length(L) == 0) { 
	
		fprintf(stderr, "get() called on empty List\n");
		exit(EXIT_FAILURE);
	
	}
	
	if (index(L) < 0) { 
	
		fprintf(stderr, "get() called with undefined index\n");
		exit(EXIT_FAILURE);
	
	}
	
	return(L -> cursor -> data);

}


// Manipulation procedures --------------------

// Resets L to its original empty state.
void clear(List L) { 

	if (L == NULL) { 
	
		printf("List Error: calling clear() on NULL List\n");
		exit(EXIT_FAILURE);
	
	}
	
	while (L -> length > 0) { 
	
		deleteFront(L);
	
	}
	
	L -> front = NULL;
	L -> back = NULL;
	L -> cursor = NULL;
	L -> index = -1;
	L -> length = 0;

}

// Overwrites the cursor element's data with x.
// Pre: length() > 0, index() >= 0
void set(List L, void* x) { 

	if (L == NULL) { 
	
		printf("calling set() on NULL List reference\n");
		exit(EXIT_FAILURE);
	
	}
	
	if (length(L) == 0) { 
	
		printf("calling set() on an empty List\n");
		exit(EXIT_FAILURE);
	
	}
	
	if (index(L) < 0) { 
	
		printf("calling set() with undefined cursor\n");
		exit(EXIT_FAILURE);
	
	}
	
	L -> cursor -> data = x;

}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) { 

	if (L -> length != 0) { 
	
		L -> cursor = L -> front;
		L -> index = 0;
	
	}

}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L) { 

	if (L == NULL) { 
	
		printf("List Error: calling moveBack() on NULL List\n");
		exit(EXIT_FAILURE);
	
	}
	
	if (L -> length == 0) { 
	
		printf("List Error: calling moveBack() on empty List\n");
		exit(EXIT_FAILURE);
	
	}
	
	if (L -> length > 0) { 
	
		L -> cursor = L -> back;
		L -> index = L -> length - 1;
	
	}

}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) { 

	if (L == NULL) { 
	
		printf("List Error: calling movePrev() on NULL List\n");
		exit(EXIT_FAILURE);
	
	}
	
	if (L -> length == 0) { 
	
		printf("List Error: calling movePrev() on empty List\n");
		exit(EXIT_FAILURE);
	
	}
	
	if (L -> cursor != NULL) { 
	
		if (L -> cursor != L -> front) { 
		
			L -> cursor = L -> cursor -> prev;
			L -> index--;
		
		}
		else if (L -> cursor == L -> front) { 
		
			L -> cursor = NULL;
			L -> index = -1;
		
		}
	
	}

}

// If cursor is defined and not at back, move cursor one 
// step toward the back of L; if cursor is defined and at 
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) { 

	if (L == NULL) { 
	
		printf("List Error: calling moveNext() on NULL list\n");
		exit(EXIT_FAILURE);
	
	}
	
	if (L -> length == 0) { 
	
		printf("List Error: calling moveNext() on empty List\n");
		exit(EXIT_FAILURE);
	
	}
	
	if (L -> cursor != NULL && L -> cursor != L -> back) { 
	
		L -> cursor = L -> cursor -> next;
		L -> index++;
	
	}
	else if (L -> cursor != NULL && L -> cursor == L -> back) { 
	
		L -> cursor = NULL;
		L -> index = -1;
	
	}

}

// Insert new element into L. If L is non-empty,
//insertion takes place before front element.
void prepend(List L, void* x) { 

	if (L == NULL) { 
	
		printf("List Error: calling prepend() on NULL list\n");
		exit(EXIT_FAILURE);
	
	}
	
	Node N = newNode(x);
	
	if (length(L) == 0) { 
	
		L -> front = L -> back = L -> cursor = N;
		L -> index = 0;
	
	}
	else { 
	
		N -> next = L -> front;
		L -> front -> prev = N;
		L -> front = N;
		
		if (L -> cursor == L -> front) { 
		
			L -> index++;
		
		}
		else if (L -> index != -1) { 
		
			L -> index ++;
		
		}
	
	}
	
	L -> length++;

}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, void* x) { 

	if (L == NULL) { 
	
		printf("List Error: calling append() on NULL List\n");
		exit(EXIT_FAILURE);
	
	}
	
	Node N = newNode(x);
	
	if (L -> length == 0) { 
	
		L -> front = L -> back = N;
	
	} else { 
	
		N -> prev = L -> back;
		L -> back -> next = N;
		L -> back = N;
	
	}
	
	L -> length++;

}

// Insert new element before cursor.
// Pre: length() > 0, index() >= 0
void insertBefore(List L, void* x) {

	if (L == NULL) {
  
		printf("List Error: calling insertBefore() on NULL List\n");
		exit(EXIT_FAILURE);
    
	}
  
	if (length(L) <= 0 || index(L) < 0) {
  
		printf("List Error: calling insertBefore() on empty or NULL List\n");
		exit(EXIT_FAILURE);
    
	}
	
	Node N = newNode(x);
	
	if (index(L) == 0) { 
	
		L -> front -> prev = N;
		N -> next = L -> front;
		L -> front = N;
	
	} else { 
	
		N -> prev = L -> cursor -> prev;
		L -> cursor -> prev -> next = N;
		N -> next = L -> cursor;
		L -> cursor -> prev = N;
	
	}
	
	L -> index++;
	L -> length++;

}

// Insert new element after cursor.
// Pre: length() > 0, index() >= 0
void insertAfter(List L, void* x) {

	if (L -> cursor == NULL) {
	
		fprintf(stderr, "insertAfter() called on undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	
	Node N = newNode(x);
	
	if (L -> cursor == L -> back) { 
	
		L -> back -> next = N;
		N -> prev = L -> back;
		L -> back = N;
	
	} else { 
	
		N -> next = L -> cursor -> next;
		L -> cursor -> next -> prev = N;
		N -> prev = L -> cursor;
		L -> cursor -> next = N;
	
	}
	
	L -> length++;
  
}

// Delete the front element. Pre: length() > 0
void deleteFront(List L) {

	if (L == NULL) {
  
		printf("List Error: calling deleteFront() on NULL List\n");
		exit(EXIT_FAILURE);
    
	}
  
	if (L -> length == 0) {
  
		printf("List Error: calling deleteFront() on empty List\n");
		exit(EXIT_FAILURE);
    
	}
  
	if (L -> length <= 0) {
  
		printf("List Error: calling deleteFront() on out of range List\n");
		exit(EXIT_FAILURE);
    
	}

	if (L -> length > 0) {
  
		Node N = L -> front -> next;
		freeNode(&(L -> front));
		L -> front = N;
    
		if (L -> cursor == L -> front) {
    
			L -> back = NULL;
      
		}
    
		L -> length--;
		L -> index--;
    
	}
  
}

// Delete the back element. Pre: length() > 0
void deleteBack(List L) {

	if (L == NULL) {
	
		printf("List Error: calling deleteBack() on NULL List\n");
		exit(EXIT_FAILURE);
		
	}
	
	if (L -> length == 0) {
	
		printf("List Error: calling deleteBack() on empty List\n");
		exit(EXIT_FAILURE);
		
	}
	
	if (L -> length <= 0) {
	
		printf("List Error: calling deleteBack() on out of range List\n");
		exit(EXIT_FAILURE);
		
	}

	if (L -> cursor == L -> back) {
	
		L -> cursor = NULL;
		L -> index = -1;
		
	}
	
	Node N = L -> back;
	L -> back = L -> back -> prev;
	
	if (L -> back != NULL) {
	
		L -> back -> next = NULL;
		
	} 
	else {
	
		L -> front = NULL;
		
	}
	
	freeNode(&N);
	L -> length--;
  
}

// Delete cursor element, making cursor undefined
// Pre: length() > 0, index() >= 0
void delete(List L) {

	if(L -> cursor == L -> front) {
	
		deleteFront(L);
		
	} 
	else if (L -> cursor == L -> back) {
	
		deleteBack(L);
		
	} 
	else if (L -> index >= 0 && L -> length > 0) {
	
		L -> cursor -> next -> prev = L -> cursor -> prev;
		L -> cursor -> prev -> next = L -> cursor -> next;
		Node N = L -> cursor;
		L -> cursor = NULL;
		L -> index = -1;
		L -> length -= 1;
		freeNode(&N);
    
	}
  
}


// Other operations --------------------

// Prints to the file pointed to by out, a 
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE *out, List L) {

	if (L == NULL) {
	
		printf("List Error: calling printList() on NULL List\n");
		exit(EXIT_FAILURE);
		
	}
	
	for (moveFront(L); index(L) >= 0; moveNext(L)) {
	
		fprintf(out, "%d ", *((int*) get(L)));
		
	}
	
	fprintf(out, "\n");
	
}

