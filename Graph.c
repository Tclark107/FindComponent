//===============================================================================
// Graph.c
// Implementation file for Graph ADT. Since I will not be using BFS for
// this project I commented out some of the unused variables and
// functions.
//
// Tristan Clark
//===============================================================================

#include<stdio.h>
#include<stdlib.h>

#include"List.h"
#include"Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

/*** struct ***/

// private GraphObj struct
typedef struct GraphObj{
   int order;
   int size;

   List *adj;
   int *color;
   int *parent;

   // for BFS
   //int *distance;
   //int source;
   
   // for DFS
   int *discover;
   int *finish;

}GraphObj;

/*** Contructors-Destructors ***/

// Graph newGraph()
// Graph constructor
Graph newGraph(int n) {
   Graph G = malloc(sizeof(struct GraphObj));
   
   G->adj = malloc((n+1)*sizeof(List));
   G->color = malloc((n+1)*sizeof(int));
   G->parent = malloc((n+1)*sizeof(int));
   
   // BFS variables
   //G->distance = malloc((n+1)*sizeof(int));
   
   // DFS variables   
   G->discover = malloc((n+1)*sizeof(int));
   G->finish = malloc((n+1)*sizeof(int));

   G->order = n; //n vertices
   G->size = 0;  //no edges
   //G->source = NIL;

   for(int i=1;i<=n; i++){
      G->adj[i] = newList();
      G->parent[i] = NIL;
      //G->distance[i] = INF;
      G->color[i] = WHITE;
   }
   return G;
}

// freeGraph()
// Graph Destructor
void freeGraph(Graph* pG) {
   Graph tmp = *pG;
   for(int i=1; i<(tmp->order+1); i++){
      freeList(&(tmp->adj[i]));
   }
   free(tmp->adj);
   free(tmp->parent);
   //free(tmp->distance);
   free(tmp->discover);
   free(tmp->finish);
   free(tmp->color);
   free(*pG);
   *pG = NULL;
}

/*** Access functions ***/

// getOrder()
// Returns value of order
int getOrder(Graph G) {return G->order;}

// getSize()
// Returns value of size
int getSize(Graph G) {return G->size;}

// getSource()
// Returns value of source
//int getSource(Graph G) {return G->source;}

// getParent()
// Returns the parent of vertex u
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
   if(u < 1 || u > getOrder(G)) {
      printf("getParent() called on a vertex out of bounds\n");
      exit(1);
   }
   return G->parent[u];
}

// getDiscover()
// Returns the Discovery time of vertex u
// Pre: 1<=u<=n=GetOrder(G)
int getDiscover(Graph G, int u) {
   if(u < 1 || u > getOrder(G)) {
      printf("getParent() called on a vertex out of bounds\n");
      exit(1);
   }
   return G->discover[u];
}


// getFinish()
// Returns the Finish time of vertex u
// Pre: 1<=u<=n=GetOrder(G)
int getFinish(Graph G, int u) {
   if(u < 1 || u > getOrder(G)) {
      printf("getParent() called on a vertex out of bounds\n");
      exit(1);
   }
   return G->finish[u];
}

/*
// getDist()
// Returns the distance from the most recent BFS source to vertex u
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
   if(u < 1 || u > getOrder(G)) {
      printf("getDist() called on a vertex out of bounds\n");
      exit(1);
   }
   return G->distance[u];
}
*/

/*
// getPath()
// Appends the vertices of the shortest path from source to u to the List L
// or NIL if it doesnt exist.
// Pre: getSource(G)!=NIL, 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u) {
   if(u < 1 || u > getOrder(G)) {
      printf("getPath() called on a vertex out of bounds\n");
      exit(1);
   }
   if(getSource(G)==NIL) {
      printf("getPath() was called before BFS() was called\n");
      exit(1);
   }
   //clear(L);
   List I = newList(); 
   prepend(I,u);
   while(getParent(G,u) != NIL) {
      prepend(I, getParent(G,u));
      u = getParent(G,u);
   }
   if(u == G->source) {
      moveFront(I);
      while(index(I) >= 0) {
         append(L,get(I));
         moveNext(I);
      }
   } else {
      append(L,NIL);
   }
   
   freeList(&I);
}
*/

/*
// makeNull()
// Deletes all edges of G.
void makeNull(Graph G) { 
   for(int i=1;i<=G->order;++i) {
      clear(G->adj[i]);
   }
}
*/

// addNeighbors()
// Does the insert action for addEdge() and addArc()
void addNeighbors(Graph G, int x, int y) {
   if(length(G->adj[x])>0) { //I may need to check whether element exists
      if(back(G->adj[x]) < y) {
         append(G->adj[x],y);
      } else {
         moveFront(G->adj[x]);
         while(index(G->adj[x])>=0) {
            if(get(G->adj[x]) > y) {
               insertBefore(G->adj[x],y);
               break;
            }
            moveNext(G->adj[x]);
         }
      }
   } else {
      append(G->adj[x],y);
   }
}

// void addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency
// List of v and vice versa. Note: make sure these are sorted
// Pre: 1 <= u <= getOrder(G)
void addEdge(Graph G, int u, int v) {
   if(u < 1 || u > getOrder(G)) {
      printf("addEdge() called on a vertex out of bounds\n");
      exit(1);
   }
   addNeighbors(G,u,v);
   addNeighbors(G,v,u);
   G->size++;
}

// void addArc()
// Inserts a new edge joining u to v, i.e. v is added to the adjacency
// List of u.
// Pre: 1 <= u <= getOrder(G)
void addArc(Graph G, int u, int v) {
   if(u < 1 || u > getOrder(G)) {
      printf("addArc() called on a vertex out of bounds\n");
      exit(1);
   }
   addNeighbors(G,u,v); 
   G->size++;
}

/*
// void BFS()
// BFS algorithm.
void BFS(Graph G, int s) {
   int x,y;
   G->source = s;
   //for(x=1;x<=G->order;++x) {
   //   G->color[x] = WHITE;
   //   G->distance[x] = INF;
   //   G->parent[x] = NIL;
   //}
   G->color[s] = GRAY;
   G->distance[s] = 0;
   G->parent[s] = NIL;
   
   List BFSQ = newList();
   append(BFSQ,s);

   while(length(BFSQ) > 0) {
      moveFront(BFSQ);
      x = get(BFSQ);
      delete(BFSQ);
      moveFront(G->adj[x]);
      while(index(G->adj[x])>=0){
         y = get(G->adj[x]);
         if(G->color[y] == WHITE) {
            G->color[y] = GRAY;
            G->distance[y] = G->distance[x]+1;
            G->parent[y] = x;
            append(BFSQ,y);
         }
         moveNext(G->adj[x]);
      }
      G->color[x] = BLACK;
   }
   freeList(&BFSQ);
}
*/

// Visit()
// Recursively processes visited vertices.
int Visit(Graph G, List S, int x, int time) {
   int y;
   G->discover[x] = ++time;
   //printf("The discover time of vertex %d is %d\n",x,G->discover[x]);
   G->color[x] = GRAY;
   if(length(G->adj[x])>0) {
      moveFront(G->adj[x]);
      while(index(G->adj[x])!=-1) {
         y = get(G->adj[x]);
         if(G->color[y] == WHITE) {
            G->parent[y] = x;
            time = Visit(G,S,y,time);
         }
         moveNext(G->adj[x]);
      }
   }
   G->color[x] = BLACK;
   G->finish[x] = ++time;
   //printf("The finish time 2 of vertex %d is %d\n",x,G->finish[x]);
   moveFront(S);
   while(index(S)!=-1) {
      if(get(S)==x) {
         delete(S);
         break;
      }
      moveNext(S);
   }
   prepend(S,x);
   return time;
}

// void DFS()
// DFS algorithm.
void DFS(Graph G, List S) {
   int x,time = 0;
   moveFront(S);
   while(index(S)!=-1) {
      x = get(S);
      if(G->color[x]==WHITE) {
         time = Visit(G,S,x,time);
      }
      moveNext(S);
   }
}

/*** Other operations ***/

// Graph transpose()
// Returns a graph representing the transpose of G.
Graph transpose(Graph G) {
   Graph T = newGraph(G->order);

   T->size = G->size;

   for(int i=1;i<=G->order;++i) {
      T->color[i] = WHITE;
      T->parent[i] = NIL;
      moveFront(G->adj[i]);
      while(index(G->adj[i])!=-1) {
         addArc(T,get(G->adj[i]),i);
         moveNext(G->adj[i]); 
      }
   }
   return T;
}

// Graph copyGraph()
// Returns a reference to a new Graph that is a copy of G.
Graph copyGraph(Graph G) {
   Graph C = newGraph(G->order);

   C->size = G->size;

   for(int i=1;i<=G->order;++i) {
      C->adj[i] = G->adj[i];
      C->parent[i] = G->parent[i];
      C->color[i] = G->color[i];
   }

   return C;
}

// void printGraph()
// Prints the adjacency list representation of G to the file pointed to
// by out.
void printGraph(FILE* out, Graph G) {
   for(int i=1;i<=G->order; i++){
      fprintf(out,"%d: ", i);
      printList(out,G->adj[i]);
      fprintf(out,"\n");
   } 
}
