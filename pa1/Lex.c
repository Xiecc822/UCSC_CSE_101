/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA1
* Lex.c
* Lex for List ADT
****************************************/

#include "List.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENTH 300

int main(int argc, char **argv) { 

	int lc = 0;
	FILE *infile, *outfile;
	char line[MAX_LENTH];
	
	// check command line for correct number of arguments
	if (argc != 3) { 
	
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	
	}
	
	infile = fopen(argv[1], "r");
	if (infile == NULL) { 
	
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	
	}
	
	outfile = fopen(argv[2], "w");
	if (outfile == NULL) { 
	
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	
	}
	
	// read the input file
	int init_lc = 0;
	
	while (fgets(line, MAX_LENTH, infile) != NULL) { 
	
		init_lc++;
	
	}
	
	rewind(infile);
	
	char **str = (char**)malloc(init_lc * sizeof(char*));
	
	while (fgets(line, MAX_LENTH, infile) != NULL) { 
	
		str[lc] = (char*)malloc(MAX_LENTH * sizeof(char) * strlen(line));
		strcpy(str[lc], line);
		lc++;
	
	}
	
	List L = newList();
	append(L, 0);
	moveFront(L);
	
	for (int i = 1; i < lc; i++) { 
	
		while (index(L) >= 0) { 
		
			if (strcmp(str[i], str[get(L)]) > 0) { 
			
				moveNext(L);
			
			}
			
			else break;
		
		}
		
		if (index(L) >= 0) { 
		
			insertBefore(L, i);
		
		}
		
		else append(L, i);
		
		moveFront(L);
	
	}
	
	while (index(L) >= 0) { 
	
		fprintf(outfile, "%s", str[get(L)]);
		moveNext(L);
	
	}
	
	// close files
	fclose(infile);
	fclose(outfile);
	
	// memory-check
	for (int i = 0; i < lc; i++) { 
	
		free(str[i]);
	
	}
	
	// free all things
	freeList(&L);
	free(str);
	
	return 0;

}


