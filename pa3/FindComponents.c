/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA3
* FindComponents.c
* Main function for Graph.c
****************************************/


#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "List.h"


int main(int argc, char **argv) { 

	FILE *infile, *outfile;
	int n, u, v, x = 0;
	int compCount = 0;
	Graph G, GT;
	List S = newList(), *scc;
	
	
	// Check command line for correct number of arguments
	if (argc != 3) { 
	
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	
	}
	
	// Open input file
	if ((infile = fopen(argv[1], "r")) == NULL) { 
	
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(EXIT_FAILURE);
	
	}
	
	// Open output file
	if ((outfile = fopen(argv[2], "w")) == NULL) { 
	
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(EXIT_FAILURE);
	
	}
	
	// Read the number of vertices
	fscanf(infile, " %d", &n);
	
	// Create a new graph with n vertices
	G = newGraph(n);
	
	
	// Read in edges and add them to the graph
	while (fscanf(infile, " %d %d", &u, &v) == 2 && u != 0 && v != 0) { 
	
		addArc(G, u, v);
	
	}
	
	
	// Print adjacency list representation of G
	fprintf(outfile, "Adjacency list representation of G:\n");
	printGraph(outfile, G);
	fprintf(outfile, "\n");
	
	
	// Get transpose of G
	GT = transpose(G);
	
	
	// Add vertices to the stack
	for (int i = 1; i <= n; i++) { 
	
		append(S, i);
	
	}
	
	
	// DFS ont G and GT
	DFS(G, S);
	DFS(GT, S);
	
	
	// Count the number of strongly connected components
	for (int i = 1; i <= n; i++) { 
	
		if (getParent(GT, i) == NIL) { 
		
			x++;
		
		}
	
	}
	
	// Create an array of lists of strongly connected components
	scc = calloc(x, sizeof(List));
	
	for (int i = 0; i < x; i++) { 
	
		scc[i] = newList();
	
	}
	
	
	// Move vertices to their respective component lists
	moveBack(S);
	
	while (index(S) != -1) { 
	
		int y = get(S);
		prepend(scc[compCount], y);
		
		if (getParent(GT, y) == NIL) { 
		
			compCount++;
		
		}
		
		movePrev(S);
	
	}
	
	
	// Print strongly connected components
	fprintf(outfile, "G contains %d strongly connected components:\n", x);
	
	for (int i = 0; i < x; i++) { 
	
		fprintf(outfile, "Component %d: ", i + 1);
		printList(outfile, scc[i]);
		fprintf(outfile, "\n");
		freeList(&scc[i]);
	
	}
	
	
	// Free all things
	free(scc);
	freeGraph(&G);
	freeGraph(&GT);
	freeList(&S);
	
	fclose(infile);
	fclose(outfile);
	
	return 0;

}


