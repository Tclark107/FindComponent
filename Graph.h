//===============================================================================
// Graph.h
// Header file for Graph ADT.
// I am adding to my previous ADT so I am commenting out, unneeded
// functions for DFS.
//
// Tristan Clark
//===============================================================================

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#include"List.h"

#define INF -1
#define NIL 0

/*** Exported type ***/

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

// newGraph()
// Returns a Graph with n vertices and no edges.
Graph newGraph(int n);

// freeGraph() 
// Graph Destructor.
void freeGraph(Graph* pG);

/*** Access functions ***/

// getOrder()
// Returns value of order.
int getOrder(Graph G);

// getSize()
// Returns value of size.
int getSize(Graph G);

// getSource()
// Returns value of source.
//int getSource(Graph G);

// getParent()
// Returns the parent of vertex u.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDiscover()
// Returns the Discovery time of vertex u
// Pre: 1<=u<=n=GetOrder(G)
int getDiscover(Graph G, int u);

// getFinish()
// Returns the Finish time of vertex u
// Pre: 1<=u<=n=GetOrder(G)
int getFinish(Graph G, int u);

// getDist()
// Returns the distance from the most recent BFS source to vertex u.
// Pre: 1 <= u <= getOrder(G)
//int getDist(Graph G, int u);

// getPath()
// Appends the vertices of the shortest path from source to u to the List L
// or NIL if it doesnt exist.
// Pre: getSource(G)!=NIL, 1 <= u <= getOrder(G)
//void getPath(List L, Graph G, int u);

// makeNull()
// Deletes all edges of G.
//void makeNull(Graph G);

// void addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency
// List of v and vice versa. Note: make sure these are sorted
// Pre: 1 <= u <= getOrder(G)
void addEdge(Graph G, int u, int v);

// void addArc()
// Inserts a new edge joining u to v, i.e. v is added to the adjacency
// List of u.
// Pre: 1 <= u <= getOrder(G)
void addArc(Graph G, int u, int v);

// void BFS()
// BFS algorithm.
//void BFS(Graph G, int s);

// void DFS()
// DFS algorithm.
void DFS(Graph G, List S);

/*** Other operations ***/

// Graph transpose()
// Returns a graph representing the transpose of G.
Graph transpose(Graph G);

// Graph copyGraph()
// Returns a reference to a new Graph that is a copy of G.
Graph copyGraph(Graph G);

// void printGraph()
// Prints the adjacency list representation of G to the file pointed to
// by out.
void printGraph(FILE* out, Graph G);

#endif
