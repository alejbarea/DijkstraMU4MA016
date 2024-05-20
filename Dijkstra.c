#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "minHeap.h"
#include "DijkstraAlgo.h"

// Here we read the file containing the data of the graph
void read_Graph(Graph* G, const char* f)
{
  
  FILE *pFile;
  
  int k = INT_MAX;
  
  char text[1000];
  
  pFile = fopen(f,"r");
  // We protect the input
  if (pFile == NULL) { 
  	
  		printf("The file does not exist\n");
  		exit(0);
  
  };

  while ((strstr(fgets(text,k,pFile),"Vertices") == NULL)) {
    //printf(text);
   }
  //printf(text);

  int lv = 0;
  fscanf(pFile,"%d",&lv);
  G->nv = lv; // number of nodes
  // printf("%d\n",m->nv);
while ((strstr(fgets(text,k,pFile),"Matrix") == NULL)) {
    //printf(text);
   }
  //printf(text);
  int i,j;
  G->adj_matrix = malloc(lv * sizeof(double*));
  for(i = 0; i < lv; i++) {
    G->adj_matrix[i] = malloc(lv*sizeof(double));
    
  }

  int count_edges = 0;
  double auxiliar; 
  for (i = 0; i < lv ; i++) {
    
    for (j = 0; j < lv; j++){
      fscanf(pFile,"%lf",&auxiliar);
      G->adj_matrix[i][j] = auxiliar;
      
      
    }
     }

  for (int i = 0; i < lv; i++) {
    for (int j = i+1; j < lv; j++){
      if(G->adj_matrix[i][j] != 0) count_edges++;
    }
  }
  
  G->ne = count_edges;
  
  fclose(pFile);
  
}

    



int main(int argc, char* arg_list[]) {
  if(argc != 2) {
  //if(argc != 4) {
    // the compilation works this way: 
    // ./Dijkstra file origin destiny
    printf("Error: correct procedure: \n");
    printf("./Dijkstra file origin destiny\n");
    return 0;
  }
  Graph G;
  
  // We call the read_graph function on our file
  read_Graph(&G,arg_list[1]);
  printf("Let's go:\n");
  int* path;
  
  int i;
  double distance;
  int origin = atoi(arg_list[2]); // we have to convert it to integer
  int destiny = atoi(arg_list[3]); // idem
  int path_length;
  
  // We protect the input again
  if(origin >= G.nv || origin < 0 || destiny >= G.nv || destiny < 0) {
  	printf("The node values are not valid!, valid node values from 0 to %d\n",G.nv-1);
  	return 1;
  }
  float tt;
  clock_t time = clock();
  path = Dijkstra(origin, destiny, G,&distance,&path_length);
  time = clock() - time;
  tt = ((float)time)/CLOCKS_PER_SEC;
  printf("Temps d'execution: %f sec\n",tt);
  printf("The total distance between %d and %d is: %lf\n",origin,destiny,distance);
  printf("The path is: \n");
  for(i = path_length -1; i >=0; i--) {
    // path is stocked upside down due to the definition of previous
    printf("%d ",path[i]);
  }
  printf("\n");
  return 0;
}
