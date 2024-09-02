/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA3
* Graph.c
* Graph ADT
****************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "List.h"


typedef struct GraphObj {

    List* adj;      // array of Lists containing adjacent vertices
    int* color;     // array of vertex colors
    int* parent;    // array of parents
    int* discover;  // array of discover times
    int* finish;    // array of finish times
    int order;      // number of vertices in the graph
    int size;      // number of edges in the graph
    
} GraphObj;


/*** Constructors-Destructors ***/

Graph newGraph(int n) {

    Graph G = malloc(sizeof(struct GraphObj));
    G -> adj = malloc((n + 1) * sizeof(List));
    G -> color = malloc((n + 1) * sizeof(int));
    G -> parent = malloc((n + 1) * sizeof(int));
    G -> discover = malloc((n + 1) * sizeof(int));
    G -> finish = malloc((n + 1) * sizeof(int));
    G -> order = n;
    G -> size = 0;
    
    for (int i = 1; i <= n; i++) {
    
        G -> adj[i] = newList();
        G -> color[i] = WHITE;
        G -> parent[i] = NIL;
        G -> discover[i] = UNDEF;
        G -> finish[i] = UNDEF;
        
    }
    
    return G;
    
}

void freeGraph(Graph* pG) {

    if (pG == NULL || *pG == NULL) {
    
        return;
        
    }
    
    for (int i = 1; i <= (*pG) -> order; i++) {
    
        freeList(&((*pG) -> adj[i]));
        
    }
    
    free((*pG) -> adj);
    free((*pG) -> color);
    free((*pG) -> parent);
    free((*pG) -> discover);
    free((*pG) -> finish);
    free(*pG);
    *pG = NULL;
    
}


/*** Access functions ***/

// Returns the order of the graph (number of vertices)
int getOrder(Graph G) {

    if (G == NULL) {
    
        fprintf(stderr, "Error: getOrder() called on NULL Graph reference\n");
        exit(EXIT_FAILURE);
        
    }
    
    return G -> order;
    
}

// Returns the size of the graph (number of edges)
int getSize(Graph G) {

    if (G == NULL) {
    
        fprintf(stderr, "Error: getSize() called on NULL Graph reference\n");
        exit(EXIT_FAILURE);
        
    }
    
    return G -> size;
    
}


int getParent(Graph G, int u) {

    if (G == NULL) {
    
        fprintf(stderr, "Error: getParent() called on NULL Graph reference\n");
        exit(EXIT_FAILURE);
        
    }
    
    if (u < 1 || u > getOrder(G)) {
    
        fprintf(stderr, "Error: getParent() called with vertex out of range\n");
        exit(EXIT_FAILURE);
        
    }
    
    return G -> parent[u];
    
}

int getDiscover(Graph G, int u) {    /* Pre: 1<=u<=n=getOrder(G) */

    if (u < 1 || u > getOrder(G)) { 
    
    	printf("calling getDiscover() with invalid vertex index\n");
    	exit(EXIT_FAILURE);
    
    }
    
    return G -> discover[u];
    
}


int getFinish(Graph G, int u) {     /* Pre: 1<=u<=n=getOrder(G) */

	if (u < 1 || u > getOrder(G)) { 
	
		fprintf(stderr, "getFinish() vertex %d is out of range\n", u);
		exit(EXIT_FAILURE);
	
	}
	
	return G -> finish[u];

}


/*** Manipulation procedures ***/

void addArc(Graph G, int u, int v) {

	if (v > getOrder(G) || u > getOrder(G) || v < 1 || u < 1) { 
	
		printf("addArc(): invalid vertex index\n");
		exit(1);
	
	}
	
	List L = G -> adj[u];
	
	if (length(L) == 0) { 
	
		append(L, v);
	
	}
	else { 
	
		for (moveFront(L); index(L) >= 0; moveNext(L)) { 
		
			if (v < get(L)) { 
			
				insertBefore(L, v);
				break;
			
			}
			else if (v == get(L)) { 
			
				return;
			
			}
		
		}
		
		if (index(L) < 0) { 
		
			append(L, v);
		
		}
	
	}
	
	G -> size++;
   
}

void addEdge(Graph G, int u, int v) {

   addArc(G, u, v);
   addArc(G, v, u);
   G -> size--;
   
}


void DFS(Graph G, List S) {

   for (int i = 0; i <= getOrder(G); i++) { 
   
   	   G -> color[i] = WHITE;
   	   G -> parent[i] = NIL;
   	   G -> discover[i] = UNDEF;
   	   G -> finish[i] = UNDEF;
   
   }
   
   int time = 0;
   List temp = copyList(S);
   clear(S);
   
   moveFront(temp);
   while (index(temp) >= 0) { 
   
       int vertex = get(temp);
       if (G -> color[vertex] == WHITE) { 
       
           visit(G, vertex, &time, S);
       
       }
       
       moveNext(temp);
   
   }
   
   freeList(&temp);
   
}


void visit(Graph G, int x, int* time, List S) { 

	G -> discover[x] = ++(* time);
	G -> color[x] = GRAY;
	List L = G -> adj[x];
	moveFront(L);
	
	while (index(L) >= 0) { 
	
		int y = get(L);
		
		if (G -> color[y] == WHITE) { 
		
			G -> parent[y] = x;
			visit(G, y, time, S);
		
		}
		
		moveNext(L);
	
	}
	
	G -> color[x] = BLACK;
	G -> finish[x] = ++(* time);
	prepend(S, x);

}

/*** Other operations ***/

Graph transpose(Graph G) { 

	int n = getOrder(G);
	Graph T = newGraph(n);
	
	for (int u = 1; u <= n; u++) { 
	
		List adj = G -> adj[u];
		moveFront(adj);
		
		while (index(adj) != -1) { 
		
			int v = get(adj);
			addArc(T, v, u);
			moveNext(adj);
		
		}
	
	}
	
	return T;

}


Graph copyGraph(Graph G) { 

	int n = getOrder(G);
	Graph C = newGraph(n);
	
	for (int u = 1; u <= n; u++) { 
	
		List adj = G -> adj[u];
		moveFront(adj);
		
		while (index(adj) != -1) { 
		
			int v = get(adj);
			addArc(C, u, v);
			moveNext(adj);
		
		}
	
	}
	
	return C;

}


void printGraph(FILE* out, Graph G) {

    if (out == NULL || G == NULL) {
    
        fprintf(stderr, "Graph Error: calling printGraph() on NULL reference(s)\n");
        exit(EXIT_FAILURE);
        
    }

    for (int i = 1; i <= getOrder(G); i++) {
    
        fprintf(out, "%d: ", i);

        if (length(G -> adj[i]) == 0) {
        
            fprintf(out, "\n");
            continue;
            
        }

        for (moveFront(G -> adj[i]); index(G -> adj[i]) != -1; moveNext(G -> adj[i])) {
        
            fprintf(out, "%d", get(G -> adj[i]));

            if (index(G -> adj[i]) != length(G -> adj[i]) - 1) {
            
                fprintf(out, " ");
                
            }
            
        }

        fprintf(out, "\n");
        
    }
}

