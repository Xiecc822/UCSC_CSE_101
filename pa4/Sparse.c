/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA3
* Sparse.c
* Main function for Matrix.c
****************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

int main(int argc, char **argv) { 

	if (argc != 3) { 
	
		fprintf(stderr, "Usage: Sparse <input file> <output file> \n");
		exit(EXIT_FAILURE);
	
	}
	
	FILE* input = fopen(argv[1], "r");
	
	if (input == NULL) { 
	
		fprintf(stderr, "Unable to open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	
	}
	
	FILE* output = fopen(argv[2], "w");
	
	if (output == NULL) { 
	
		fprintf(stderr, "Unable to open file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	
	}
	
	
	int n, a, b;
	fscanf(input, "%d %d %d", &n, &a, &b);
	Matrix A = newMatrix(n);
	Matrix B = newMatrix(n);
	
	for (int i = 0; i < a; i++) { 
	
		int row, col;
		double value;
		fscanf(input, "%d %d %lf", &row, &col, &value);
		changeEntry(A, row, col, value);
	
	}
	
	for (int i = 0; i < b; i++) {
        int row, col;
        double value;
        fscanf(input, "%d %d %lf", &row, &col, &value);
        changeEntry(B, row, col, value);
    }

    fprintf(output, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(output, A);

    fprintf(output, "\nB has %d non-zero entries:\n", NNZ(B));
    printMatrix(output, B);
    fprintf(output, "\n");

    //(1.5)*A
    fprintf(output, "(1.5)*A =\n");
    Matrix Z = scalarMult(1.5, A);
    printMatrix(output, Z);
    fprintf(output, "\n");
    freeMatrix(&Z);

    // A + B
    fprintf(output, "A+B =\n");
    Matrix C = sum(A, B);
    printMatrix(output, C);
    fprintf(output, "\n");
    freeMatrix(&C);

    // A+A 
    fprintf(output, "A+A =\n");
    Matrix D = sum(A, A);
    printMatrix(output, D);
    fprintf(output, "\n");
    freeMatrix(&D);

    // B-A
    fprintf(output, "B-A =\n");
    Matrix E = diff(B, A);
    printMatrix(output, E);
    fprintf(output, "\n");
    freeMatrix(&E);

    // A-A
    fprintf(output, "A-A =\n");
    Matrix F = diff(A, A);
    printMatrix(output, F);
    fprintf(output, "\n");
    freeMatrix(&F);

    // Transpose(A)
    fprintf(output, "Transpose(A) =\n");
    Matrix G = transpose(A);
    printMatrix(output, G);
    fprintf(output, "\n");
    freeMatrix(&G);

    // A*B
    fprintf(output, "A*B =\n");
    Matrix H = product(A, B);
    printMatrix(output, H);
    fprintf(output, "\n");
    freeMatrix(&H);

    // B*B
    fprintf(output, "B*B =\n");
    Matrix I = product(B, B);
    printMatrix(output, I);
    fprintf(output, "\n");
    freeMatrix(&I);

    freeMatrix(&A);
    freeMatrix(&B);
    
    fclose(input);
    fclose(output);
    
    return 0;

}






































