/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA3
* Graph.h
* Graph header file for Graph ADT
****************************************/

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include <stdio.h>
#include <stdbool.h>

#include "List.h"


#define INF -1
#define NIL 0
#define UNDEF -2

#define WHITE 0
#define GRAY 1
#define BLACK 2


typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);    /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u);    /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u);    /* Pre: 1<=u<=n=getOrder(G) */

/*** Manipulation procedures ***/
void addArc(Graph G, int u, int v);    /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v);    /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S);    /* Pre: length(S)==getOrder(G) */
void visit(Graph G, int u, int* time, List S);

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);


#endif

