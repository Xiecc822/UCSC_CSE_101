/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA2
* GraphTest.c
* Graph Test for the Graph ADT
****************************************/

#include<stdio.h>
#include<stdlib.h>

#include"Graph.h"

int main(int argc, char **argv){

    int n = 20;
    List L = newList();
    Graph G = newGraph(n);
    
    printf("---------- Test Begin ----------\n");
    printf("\n");
    
    printf("Test Graph G, List L\n");

    // Add edges to the graph
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 4);
    addEdge(G, 2, 5);
    addEdge(G, 3, 6);
    addEdge(G, 3, 7);
    addArc(G, 4, 8);
    addArc(G, 4, 9);
    addEdge(G, 5, 10);
    addEdge(G, 5, 11);
    addArc(G, 6, 12);
    addArc(G, 6, 13);
    addEdge(G, 7, 14);
    addEdge(G, 7, 15);
    addArc(G, 8, 16);
    addArc(G, 8, 17);
    addEdge(G, 9, 18);
    addEdge(G, 9, 19);
    addArc(G, 10, 20);
    addArc(G, 10, 1);
    addEdge(G, 11, 2);
    addEdge(G, 12, 3);
    addArc(G, 13, 4);
    addArc(G, 14, 5);
    addEdge(G, 15, 6);
    addEdge(G, 16, 7);
    addArc(G, 17, 8);
    addArc(G, 18, 9);
    addEdge(G, 19, 10);
    addEdge(G, 20, 11);

    // Print the adjacency list representation of the graph
    printGraph(stdout, G);

    // Perform BFS starting at vertex 1
    BFS(G, 1);

    // Print the size of the graph
    printf("Size of the graph: %d\n", getSize(G));

    // Print the order of the graph
    printf("Order of the graph: %d\n", getOrder(G));

    // Print the source vertex of the BFS
    printf("Source vertex of BFS: %d\n", getSource(G));

    // Print the parent of each vertex
    printf("Parent of vertex 1: %d\n", getParent(G, 1));
    printf("Parent of vertex 2: %d\n", getParent(G, 2));
    printf("Parent of vertex 3: %d\n", getParent(G, 3));
    printf("Parent of vertex 4: %d\n", getParent(G, 4));
    printf("Parent of vertex 5: %d\n", getParent(G, 5));
    printf("Parent of vertex 6: %d\n", getParent(G, 6));
    printf("Parent of vertex 7: %d\n", getParent(G, 7));
    printf("Parent of vertex 8: %d\n", getParent(G, 8));
    printf("Parent of vertex 9: %d\n", getParent(G, 9));
    printf("Parent of vertex 10: %d\n", getParent(G, 10));

    // Append the distance from vertex 1 to each vertex in the graph to the list
    for (int i = 1; i <= n; i++) {
    
        append(L, getDist(G, i));
        
    }

    // Print the list
    printList(stdout, L);
    printf("\n");

    // Test part 2
    printf("Test Graph M, List T\n");
    
    n = 5;
    List T = newList();
    Graph M = newGraph(n);
    addEdge(M, 1, 2);
    addEdge(M, 2, 3);
    addEdge(M, 3, 4);
    addEdge(M, 4, 5);
    
    printGraph(stdout, M);
    
     // print the size of the graph
    printf("Size of the graph M before calling makeNull: %d\n", getSize(M));  
     
    makeNull(M);
    
    // print the size of the graph
    printf("Size of the graph M after calling makeNull: %d\n", getSize(M));
    printf("\n");
    
    printf("---------- Test End ----------\n");
    
    freeList(&T);
    freeGraph(&M);
    freeList(&L);
    freeGraph(&G);

    return 0;
}

/****************************************
Output of this Test:
---------- Test Begin ----------

Test Graph G, List L
1: 2 3
2: 1 4 5 11
3: 1 6 7 12
4: 2 8 9
5: 2 10 11
6: 3 12 13 15
7: 3 14 15 16
8: 16 17
9: 18 19
10: 1 5 19 20
11: 2 5 20
12: 3
13: 4
14: 5 7
15: 6 7
16: 7
17: 8
18: 9 9
19: 9 10
20: 11
Size of the graph: 30
Order of the graph: 20
Source vertex of BFS: 1
Parent of vertex 1: -9
Parent of vertex 2: 1
Parent of vertex 3: 1
Parent of vertex 4: 2
Parent of vertex 5: 2
Parent of vertex 6: 3
Parent of vertex 7: 3
Parent of vertex 8: 4
Parent of vertex 9: 4
Parent of vertex 10: 5
0 1 1 2 2 2 2 3 3 3 2 2 3 3 3 3 4 4 4 3 
Test Graph M, List T
1: 2
2: 1 3
3: 2 4
4: 3 5
5: 4
Size of the graph M before calling makeNull: 4
Size of the graph M after calling makeNull: 0

---------- Test End ----------
****************************************/


