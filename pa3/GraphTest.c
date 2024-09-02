/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA3
* GraphTest.c
* Graph Test for the Graph ADT
****************************************/


#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Graph.h"


int main(int argc, char **argv) { 

	int n = 10;
	
	List S = newList();
	Graph G = newGraph(n);
	Graph GT = NULL;
	Graph GC = NULL;
	
	printf("---------- Test Begin ----------\n");
    printf("\n");
	
	for (int i = 1; i <= n; i++) { 
	
		append(S, i);
	
	}
	
	addEdge(G, 1, 2);
	addEdge(G, 1, 5);
	addEdge(G, 2, 5);
	addEdge(G, 2, 6);
	addEdge(G, 3, 2);
	addEdge(G, 3, 4);
	addEdge(G, 3, 6);
	addEdge(G, 3, 7);
	addEdge(G, 3, 8);
	addEdge(G, 6, 5);
	addEdge(G, 6, 7);
	addEdge(G, 8, 4);
	addEdge(G, 8, 7);
	
	printf("The original graph:\n");
	printGraph(stdout, G);
	
	DFS(G, S);
	printf("\n");
	
	fprintf(stdout, "Vertex:  Discovery  Finish  Parent\n");
	
	for (int i = 1; i <= n; i++) { 
	
		fprintf(stdout, "%6d: %9d %7d %7d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
	
	}
	
	printf("\n");
	printf("List of vertices in order of decreasing finish times:\n");
	printList(stdout, S);
	
	GT = transpose(G);
	GC = copyGraph(G);
	
	printf("\n");
	printf("\n");
	printf("Transpose of graph:\n");
	printGraph(stdout, GT);
	
	printf("\n");
	printf("\n");
	printf("Copy of graph:\n");
	printGraph(stdout, GC);
	
	DFS(GT, S);
	printf("\n");
	fprintf(stdout, "Vertex:  Discovery  Finish  Parent\n");
	
	for (int i = 1; i <= n; i++) { 
	
		fprintf(stdout, "%6d: %9d %7d %7d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
	
	}
	
	freeList(&S);
	freeGraph(&G);
	freeGraph(&GT);
	freeGraph(&GC);
	
	printf("\n");
	printf("\n");
	
	printf("---------- Test End ----------\n");
	
	return 0;

}


/****************************************
Output of this Test:
---------- Test Begin ----------

The original graph:
1: 2 5
2: 1 3 5 6
3: 2 4 6 7 8
4: 3 8
5: 1 2 6
6: 2 3 5 7
7: 3 6 8
8: 3 4 7
9: 
10: 

Vertex:  Discovery  Finish  Parent
     1:         1      16       0
     2:         2      15       1
     3:         3      14       2
     4:         4      13       3
     5:         8       9       6
     6:         7      10       7
     7:         6      11       8
     8:         5      12       4
     9:        17      18       0
    10:        19      20       0

List of vertices in order of decreasing finish times:
10 9 1 2 3 4 8 7 6 5 

Transpose of graph:
1: 2 5
2: 1 3 5 6
3: 2 4 6 7 8
4: 3 8
5: 1 2 6
6: 2 3 5 7
7: 3 6 8
8: 3 4 7
9: 
10: 


Copy of graph:
1: 2 5
2: 1 3 5 6
3: 2 4 6 7 8
4: 3 8
5: 1 2 6
6: 2 3 5 7
7: 3 6 8
8: 3 4 7
9: 
10: 

Vertex:  Discovery  Finish  Parent
     1:         1      16       0
     2:         2      15       1
     3:         3      14       2
     4:         4      13       3
     5:         8       9       6
     6:         7      10       7
     7:         6      11       8
     8:         5      12       4
     9:        17      18       0
    10:        19      20       0


---------- Test End ----------
****************************************/

