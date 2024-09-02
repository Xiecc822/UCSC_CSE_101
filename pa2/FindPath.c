/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA2
* FindPath.c
* Main function for Graph.c
****************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int main(int argc, char **argv) { 

	FILE* in = fopen(argv[1], "r");
	
    if (in == NULL) {
    
        printf("Unable to open input file %s\n", argv[1]);
        exit(EXIT_FAILURE);
        
    }
    
    FILE* out = fopen(argv[2], "w");
    
    if (out == NULL) {
    
        printf("Unable to open output file %s\n", argv[2]);
        exit(EXIT_FAILURE);
        
    }

    int n, u, v;
    fscanf(in, "%d", &n);
    Graph G = newGraph(n);

    while (fscanf(in, "%d %d", &u, &v) == 2) {
    
        if (u == 0 && v == 0) {
        
            break;
            
        }
        
        addEdge(G, u, v);
        
    }

    printGraph(out, G);

    while (fscanf(in, "%d %d", &u, &v) == 2) {
    
        if (u == 0 && v == 0) {
        
            break;
            
        }
        
        BFS(G, u);
        
        if (getDist(G, v) == INF) {
        
            fprintf(out, "\n");
            fprintf(out, "The distance from %d to %d is infinity\n", u, v);
            fprintf(out, "No %d-%d path exists", u, v);
            
        } 
        else {
        
            fprintf(out, "\n");
            fprintf(out, "The distance from %d to %d is %d\n", u, v, getDist(G, v));
            List L = newList();
            getPath(L, G, v);
            fprintf(out, "A shortest %d-%d path is: ", u, v);
            printList(out, L);
            
            freeList(&L);
            
        }
        
        fprintf(out, "\n");
        
    }

    freeGraph(&G);
    fclose(in);
    fclose(out);

    return 0;

}


