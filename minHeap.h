
typedef struct minHeapNode {
  int vertex;
  double distance;
} minHeapNode;

typedef struct minHeap {
  int size;
  int tail;
  int* pos;
  minHeapNode* nodes;
} minHeap;

int number_of_rows(const minHeap*);
int parent(int);
void initialize_minheap(minHeap*);
int L_child(int,int);
int R_child(int,int);
void actualize(double,int,minHeap*);
int low_child(int,int,minHeap*);
int compareNodes(int,int,minHeap*);
void change(int,int,minHeap*);
void minHeapPush(minHeapNode,minHeap*);
minHeapNode minHeapPop(minHeap*);
