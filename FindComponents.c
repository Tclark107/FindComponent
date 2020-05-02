/*********************************************************************************
*  FindPath.c
*  This program will read an input file in the specified format
*  and then print the output for the adjacency list of the graph
*  and the shortest path from a source to a destination.
*
*  Tristan Clark
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char * argv[]){

   FILE *in, *out;
   int start, end, order;
   Graph G;
   int i;
   List L = newList();

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   
   // get the order of the graph;
   fscanf(in, "%d", &order);
   G = newGraph(order);
   for(i=1; i<=order; i++) append(L, i);

   /* read in a line of input and add an edge or Arc */
   while( fscanf(in, "%d %d", &start, &end) != EOF ) {
      if(start == 0) break;
      addArc(G,start,end);
   }
   
   // prints out adjacency list of G
   fprintf(out,"Adjacency list representation of G:\n");
   printGraph(out,G);
   fprintf(out, "\n");
   
   // runs DFS
   DFS(G, L);

   // compute the transpose of G and initialize an array to hold the forest
   Graph T = transpose(G);
   List forest[order];
   for(i=0;i<order;++i) forest[i]= newList(); 

   // run DFS on Transpose and place the SCC's in the forest array
   DFS(T, L);
   int listCounter = 0;

   moveBack(L);
   while(index(L)!=-1) {
      while(getParent(T,get(L))!=NIL) {
         prepend(forest[listCounter],get(L));
         movePrev(L);
      }
      prepend(forest[listCounter],get(L));
      movePrev(L);
      listCounter++;
   }

   fprintf(out,"G contains %d strongly connected components:\n",listCounter);
   for(i=0;i<listCounter;++i) {
      fprintf(out,"Component %d: ",i+1);
      printList(out,forest[i]);
      fprintf(out,"\n");
   }

   /* close files */
   fclose(in);
   fclose(out);
   
   // free used allocated memory
   for(i=0;i<order;++i)freeList(&forest[i]);
   freeList(&L);
   freeGraph(&G);
   freeGraph(&T);

   return(0);
}
