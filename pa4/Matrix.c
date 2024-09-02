/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA4
* Matrix.c
* Matrix for Matrix ADT
****************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "List.h"


typedef struct EntryObj { 

	int col;
	double val;

} EntryObj;


typedef struct MatrixObj { 

	int size;
	int NNZ;
	List* rows;

} MatrixObj;


typedef struct EntryObj *Entry;


Entry newEntry(int col, double val) { 

	Entry E = malloc(sizeof(EntryObj));
	E -> col = col;
	E -> val = val;
	
	return E;

}


void freeEntry(Entry* pE) { 

	if (pE != NULL && *pE != NULL) { 
	
		free(*pE);
		*pE = NULL;
	
	}

}

// Matrix constructor
Matrix newMatrix(int n) { 

	Matrix M = malloc(sizeof(MatrixObj));
	M -> size = n;
	M -> NNZ = 0;
	M -> rows = calloc(n + 1, sizeof(List));
	
	for (int i = 1; i <= n; i++) { 
	
		M -> rows[i] = newList();
	
	}
	
	return M;

}

// Matrix destructor
void freeMatrix(Matrix* pM) { 

	if (pM != NULL && *pM != NULL) { 
	
		makeZero(*pM);
		
		for (int i = 1; i <= (*pM) -> size; i++) { 
		
			freeList(&((*pM) -> rows[i]));
		
		}
		
		free((*pM) -> rows);
		free(*pM);
		*pM = NULL;
	
	}

}

// Access functions ------------------------------
// Return the size of square Matrix M
int size(Matrix M) { 

	return M -> size;

}

// Return the number of non-zero elements in M
int NNZ(Matrix M) { 

	return M -> NNZ;

}

// Return true (1) if matrices A and B are equal, false (0) otherwise
int equals(Matrix A, Matrix B) { 

	if (A == NULL || B == NULL) { 
	
		fprintf(stderr, "Matrix | equals() | Calling equals() on one or more NULL Matrices.");
		exit(EXIT_FAILURE);
	
	}
	
	if (size(A) != size(B)) { 
	
		return 0;
	
	}
	
	for (int i = 1; i <= size(A); i++) { 
	
		if (length(A -> rows[i]) != length(B -> rows[i])) { 
		
			return 0;
		
		}
		
		moveFront(A -> rows[i]);
		moveFront(B -> rows[i]);
		
		while (index(A -> rows[i]) > 0) { 
		
			if (((Entry)get(A -> rows[i])) -> col != ((Entry)get(B -> rows[i])) -> col) { 
			
				return 0;
			
			}
			
			if (((Entry)get(A -> rows[i])) -> val != ((Entry)get(B -> rows[i])) -> val) { 
			
				return 0;
			
			}
			
			moveNext(A -> rows[i]);
			moveNext(B -> rows[i]);
		
		}
	
	}
	
	return 1;

}


// Manipulation procedures ------------------------------
// Re-sets M to the zero Matrix state
void makeZero(Matrix M) { 

	for (int i = 1; i <= size(M); i++) { 
	
		List row = M -> rows[i];
		
		if (row != NULL) { 
		
			clear(row);
		
		}
	
	}
	
	M -> NNZ = 0;

}

// Changes the i th row, j th culumn of M to the value x
// Pre: 1 <= i <= size(M), 1 <= j <= size(M)
void changeEntry(Matrix M, int i, int j, double x) { 

	if (M == NULL) { 
	
		fprintf(stderr, "Matrix | changeEntry() | Calling changeEntry() on a NULL Matrix.\n");
		exit(EXIT_FAILURE);
	
	}
	
	if (i < 1 || i > M -> size || j < 1 || j > M -> size) { 
	
		fprintf(stderr, "Matrix Error: changeEntry() called with out-of-bounds index.\n");
		exit(EXIT_FAILURE);
	
	}
	
	List L = M -> rows[i];
	moveFront(L);
	
	while (index(L) >= 0) { 
	
		Entry E = (Entry)get(L);
		
		if (E -> col == j) { 
		
			if (x == 0.0) { 
			
				delete(L);
				M -> NNZ--;
				freeEntry(&E);
				return;
			
			} else { 
			
				E -> val = x;
				return;
			
			}
		
		} else if (E -> col > j) { 
		
			if (x != 0.0) { 
			
				insertBefore(L, newEntry(j, x));
				M -> NNZ--;
				return;
			
			} else { 
			
				return;
			
			}
		
		}
		
		moveNext(L);
	
	}
	
	if (x != 0.0) { 
	
		append(L, newEntry(j, x));
		M -> NNZ++;
	
	}

}


// Matrix Arithmetic operations ------------------------------
// Returns a reference to a new Matrix object having the same entries as A
Matrix copy(Matrix A) { 

	Matrix B = newMatrix(A -> size);
	
	for (int i = 1; i <= A -> size; i++) { 
	
		List row = A -> rows[i];
		moveFront(row);
		
		while (index(row) != -1) { 
		
		
			Entry entry = (Entry)get(row);
			changeEntry(B, i, entry -> col, entry -> val);
			moveNext(row);
		
		}
	
	}
	
	return B;

}

// Returns a reference to a new Matrix object representing the transpose of A
Matrix transpose(Matrix A) { 

	Matrix B = newMatrix(A -> size);
	
	for (int i = 1; i <= A -> size; i++) { 
	
		List row = A -> rows[i];
		moveFront(row);
		
		while (index(row) != -1) { 
		
			Entry entry = (Entry)get(row);
			changeEntry(B, entry -> col, i, entry -> val);
			moveNext(row);
		
		}
	
	}
	
	return B;

}

// Returns a reference to a new Matrix object representing x A
Matrix scalarMult(double x, Matrix A) { 

	Matrix B = newMatrix(A -> size);
	
	for (int i = 1; i <= A -> size; i++) { 
	
		List row = A -> rows[i];
		moveFront(row);
		
		while (index(row) != -1) { 
		
			Entry entry = (Entry)get(row);
			changeEntry(B, i, entry -> col, x * entry -> val);
			moveNext(row);
		
		}
	
	}
	
	return B;

}


// Returns a reference to a new Matrix object representing A + B
// pre: size(A) == size(B)
Matrix sum(Matrix A, Matrix B) { 

	if (A == NULL || B == NULL) { 
	
		fprintf(stderr, "Calling sum() on a NULL Matrix.\n");
		exit(EXIT_FAILURE);
	
	}
	
	if (size(A) != size(B)) { 
	
		fprintf(stderr, "Calling sum() on different sized Matricies.\n");
		exit(EXIT_FAILURE);
	
	}
	
	if (A == B) { 
	
		return scalarMult(2, A);
	
	}
	
	Matrix C = newMatrix(A -> size);
	List sL;
	
	for (int i = 1; i <= C -> size; i++) { 
	
		sL = C -> rows[i];
		
		moveFront(A -> rows[i]);
		moveFront(B -> rows[i]);
		
		while (index(A -> rows[i]) >= 0 && index(B -> rows[i]) >= 0) { 
		
			Entry aE = (Entry)get(A -> rows[i]);
			Entry bE = (Entry)get(B -> rows[i]);
			
			if (aE -> col < bE -> col) { 
			
				append(sL, newEntry(aE -> col, aE -> val));
				C -> NNZ++;
				moveNext(A -> rows[i]);
			
			}
			
			else if (aE -> col > bE -> col) { 
			
				append(sL, newEntry(bE -> col, bE -> val));
				C -> NNZ--;
				moveNext(B -> rows[i]);
			
			}
			
			else { 
			
				if (aE -> val + bE -> val != 0) { 
				
					append(sL, newEntry(aE -> col, aE -> val+ bE -> val));
					C -> NNZ++;
				
				}
				
				moveNext(A -> rows[i]);
				moveNext(B -> rows[i]);
			
			}
		
		}
		
		while (index(A -> rows[i]) >= 0) { 
		
			Entry aE = (Entry)get(A -> rows[i]);
			append(sL, newEntry(aE -> col, aE -> val));
			C -> NNZ++;
			moveNext(A -> rows[i]);
		
		}
		
		while (index(B -> rows[i]) >= 0) { 
		
			Entry bE = (Entry)get(B -> rows[i]);
			append(sL, newEntry(bE -> col, bE -> val));
			C -> NNZ++;
			moveNext(B -> rows[i]);
		
		}
	
	}
	
	return C;

}

// Returns a reference to a new Matrix object representing A - B
// pre: size(A) == size(B)
Matrix diff(Matrix A, Matrix B) { 

	if (A -> size != B -> size) { 
	
		fprintf(stderr, "Error: matrices must have the same size.\n");
		exit(EXIT_FAILURE);
	
	}
	
	return sum(A, scalarMult(-1.0, B));

}

double vectorDot(List P, List Q) { 

	double dot = 0.0;
	
	moveFront(P);
	moveFront(Q);
	
	while (index(P) >= 0 && index(Q) >= 0) { 
	
		Entry eP = (Entry)get(P);
		Entry eQ = (Entry)get(Q);
		
		if (eP -> col == eQ -> col) { 
		
			dot += (eP -> val) * (eQ -> val);
			
			moveNext(P);
			moveNext(Q);
		
		}
		
		else if (eP -> col < eQ -> col) { 
		
			moveNext(P);
		
		}
		
		else if (eP -> col > eQ -> col) { 
		
			moveNext(Q);
		
		}
	
	}
	
	return dot;

}

// Returns a reference to a new Matrix object representing A B
// pre: size(A) == size(B)
Matrix product(Matrix A, Matrix B) { 

	if (A == NULL || B == NULL) { 
	
		fprintf(stderr, "Matrix | product() | Calling product() on one or more NULL Matrices.");
		exit(EXIT_FAILURE);
	
	}
	
	if (A -> size != B -> size) { 
	
		fprintf(stderr, "Matrix | product() | Calling product() on Matrices with different sizes.");
		exit(EXIT_FAILURE);
	
	}
	
	Matrix P = newMatrix(A -> size);
	
	if (A -> NNZ == 0 || B -> NNZ == 0) { 
	
		return P;
	
	}
	
	Matrix BT = transpose(B);
	
	for (int i = 1; i <= A -> size; i++) { 
	
		List Prow = A -> rows[i];
		
		if (length(Prow) > 0) {
		
			for (int j = 1; j <= BT -> size; j++) { 
			
				List Qrow = BT -> rows[j];
				
				if (length(Qrow) > 0) { 
				
					double dp = vectorDot(Prow, Qrow);
					
					if (dp != 0) { 
					
						Entry e = newEntry(j, dp);
						append(P -> rows[i], e);
						P -> NNZ++;
					
					}
				
				}
			
			}
		
		}
	
	}
	
	freeMatrix(&BT);
	return P;

}

// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point
void printMatrix(FILE* out, Matrix M) { 

	if (out == NULL || M == NULL) { 
	
		printf("Error: printMatrix() called with NULL parameters\n");
		exit(EXIT_FAILURE);
	
	}
	
	for (int i = 1; i <= size(M); i++) { 
	
		if (length(M -> rows[i]) > 0) { 
		
			fprintf(out, "%d: ", i);
			
			for (moveFront(M ->rows[i]); index(M -> rows[i]) >= 0; moveNext(M -> rows[i])) { 
			
				Entry e = get(M -> rows[i]);
				fprintf(out, "(%d, %.1f) ", e -> col, e -> val);
			
			}
			
			fprintf(out, "\n");
		
		}
	
	}

}


