
typedef struct Graph {
  double** adj_matrix; // adjacency matrix
  int nv; // nombre de noeuds
  int ne; // nombre de aretes
} Graph;



void initial_minheap(int, const Graph, minHeap*);
int* Dijkstra(int, const int, const Graph,double*,int*);
