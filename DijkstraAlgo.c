#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "minHeap.h"

typedef struct Graph {
  double** adj_matrix; // adjacency matrix
  int nv; // nombre de noeuds
  int ne; // nombre de aretes
} Graph;


// this function defines the initial minheap, whose top is the origin, with distance 0
void initial_minheap(int origin, const Graph G, minHeap* h) {
  int i;
  minHeapNode bigNode;
  minHeapNode originNode;
  originNode.distance = 0;
  originNode.vertex = origin;
  // for the rest of nodes, we stablish their distance to the origin as "INF", cause the algorithm will reduce in it each step
  bigNode.distance = DBL_MAX;
  for(i = 0; i < G.nv; i++) {
    if(i == origin) {
      minHeapPush(originNode,h);
    } else {
      bigNode.vertex = i;
      minHeapPush(bigNode,h);
    }
  }
}



int* Dijkstra(int origin, const int destiny, const Graph G, double* distance_returned, int* path_length) {
  // We first initialize the heap
  minHeap h;
  initialize_minheap(&h);
  // We reserve the capacity we need 
  h.nodes = malloc(G.nv*sizeof(minHeapNode));
  h.pos = malloc(G.nv*sizeof(int));
  // We add the initial information
  initial_minheap(origin, G, &h);
  
  int currentNode = origin;
  int* path_vertices = malloc(G.ne*sizeof(int)); // container of the visited nodes
  int* previous = malloc(G.nv*sizeof(int)); // for each node, we are going to stocke the previous node we've visited
  double* total_costs = malloc(G.ne*sizeof(double));
  total_costs[origin] = 0;
  int i = 0;
  minHeapNode currentNode_data;
  int j;
  int count = 0; // counts the nodes in the final path

  // the initial costs are INF, after they will be adjusted
  for(j = 1; j < G.nv; j++) {
    total_costs[j] = DBL_MAX;
  }

  // we start the algorithm
  while(currentNode != destiny) {
    i++;
    // we get the node with the minimum distance
    currentNode_data = minHeapPop(&h);
    currentNode = currentNode_data.vertex;

    // We update its stocked distance 
    total_costs[currentNode] = currentNode_data.distance;
    
    // now currentNode has changed
    if(currentNode != destiny) {
      int initial_head = h.nodes[0].vertex;
      double initial_weight = h.nodes[0].distance;
       
      for(j = 0; j < G.nv; j++) {
        // w = currentNode-j edge's value  
        double w = G.adj_matrix[currentNode][j];
          
        if(w > 0){
          // there exists the edge currentNode-j
          if(w + currentNode_data.distance < h.nodes[h.pos[j]].distance){
            // we are sure that we are minimizing the travelled distance if we continue this way
            // otherwise we should go back and restart
            previous[j] = currentNode;
          }
          // we update the distance
          actualize(w + currentNode_data.distance,j,&h);
        }
      }

    }
  }
  
  distance_returned[0] = total_costs[destiny]; // this is the final distance (sum of the weights of the edges by which we've travelled in the final path)
  int* path = malloc(G.nv*sizeof(int));
  path[0] = destiny;
  i = 1;
  while(path[i-1] != origin) {
    path[i] = previous[path[i-1]];
    i++;
  }
  path_length[0] = i;
  return path;
}





