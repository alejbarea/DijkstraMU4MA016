#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>


typedef struct minHeapNode {
  int vertex; // number of node 
  double distance; // distance to the origin 
} minHeapNode;

typedef struct minHeap {
  int size; // memory needed 
  int tail; // position of the last node
  int* pos; // pos[i] = position of the i-th node in the heap
  minHeapNode* nodes; // table of minHeapNodes
} minHeap;

// with this function, we calculate the height 
int number_of_rows(const minHeap minheap) {

// We calculate the number of rows by consequently dividing by two, which works because our tree is binary and complete.
	int rowNum = 0;
	while(((double)minheap.size) / pow(2,rowNum) >= 1) {
    // pow(2,rowNum) = number of nodes in row "rowNum"
    // once we arrive the true number_of_rows, it'll happend:
    // pow(2,rowNum+1) > size => we stop
		rowNum++;
}
	return rowNum;
}

void DisplayH(const minHeap minheap) {
  int i;
	int j;

  // we start counting rows in 0
	for(i = 0; i < number_of_rows(minheap);i++) {
    // int each row we have pow(2,i) nodes
    // we start counting nodes in 0
		for(j = 0; j < pow(2,i); j++) {
      int height = (int)pow(2,i);
			int k = height + j - 1;
		    if(k > minheap.tail) {
			    break;
        }
			printf("(%d, %lf)",minheap.nodes[(int)pow(2,i) + j  - 1].vertex,minheap.nodes[(int)pow(2,i) + j  - 1].distance);
    }
	printf("\n");

  }
  printf("Posiciones:\n");
  for(i = 0; i <= 3; i++) {
    printf("%d\n",minheap.pos[i]);
  }
}

void initialize_minheap(minHeap* minheap) {
  minheap->nodes = NULL;
  minheap->pos = NULL;
  minheap->tail = -1; // in order to tail being the position of the last node
  minheap->size = 0;
}

// This method allows us to get the parent of a node.
int parent(int e) {
  assert(e > 0);
  return (e-1)/2;
}

// This function changes nodes e and p in the heap
void change(int e, int p, minHeap* minheap) {
  // At first, we have to make sure these two ints are allowed values :)

  assert(e <= minheap->tail);
  assert(p <= minheap->tail);

  // We create a temporary node to swap between the one at index e and the one at index p
  // it is important to change all the information stored in the structure minHeapNode

  minHeapNode tmpnode;
  tmpnode.distance = minheap->nodes[e].distance;
  tmpnode.vertex = minheap->nodes[e].vertex;
  minheap->nodes[e].distance = minheap->nodes[p].distance;
  minheap->nodes[e].vertex = minheap->nodes[p].vertex;
  minheap->nodes[p].distance = tmpnode.distance;
  minheap->nodes[p].vertex = tmpnode.vertex;

  // We must not forget that the position of our nodes have changed too!!

  int tmppos;
  tmppos = minheap->pos[minheap->nodes[e].vertex];
  minheap->pos[minheap->nodes[e].vertex] = minheap->pos[minheap->nodes[p].vertex];
  minheap->pos[minheap->nodes[p].vertex] = tmppos;

} 

// nodes[e].distance < nodes[p].distance ? True : False
// this is an auxiliary function that will help us maintain the carachteristic of minHeap 
int compareNodes(int e, int p,minHeap* minheap) {
  if(minheap->nodes[e].distance < minheap->nodes[p].distance) {
    return 1;
  }
  return 0;
}

void minHeapPush(minHeapNode node,minHeap* minheap) {

  // We update the minheap with the new value, just appending it.

  minheap->tail++;
  minheap->size += sizeof(minHeapNode);
  minheap->nodes[minheap->tail] = node;
  minheap->pos[node.vertex] = minheap->tail;
  
  // Now, we must move this node to its correct position to maintain the minHeap property

  int currentPosition = minheap->tail;
  if(currentPosition > 0){
    // currentPosition is a child position
    int parentPosition = parent(currentPosition);
  
  // While our currentPosition is not the root and the value of the distance of our currentnode is less than the one of the parent node, we iterate :)
    while(currentPosition != 0 && (compareNodes(currentPosition,parentPosition,minheap) == 1)) {
      change(currentPosition,parentPosition,minheap);
      if(parentPosition > 0) {
        // we still are childs
        currentPosition = parentPosition;
        parentPosition = parent(currentPosition);
      }
    }
  }
}

// L_child gives us the position of the left child
int L_child(int p, int tail)
{
  if (2*p+1 <= tail ) return 2*p+1;
  else return -1;
}

// R_child gives us the position of the right child
int R_child(int p, int tail)
{
  if(2*p+2 <= tail) return 2*p+2;
  else return -1;
}

// low_child gives us the position (e or p) of the vertex whose distance is the lowest
int low_child(int e, int p, minHeap* minheap) {
  if(e == -1) {
    return p;
  }
  if(p == -1) {
    return e;
  }
  if(compareNodes(e,p,minheap)) {
    return e;
  }
  return p;
}

// Because of what we want to do (Dijkstra), the distances will only be lowered so we only have to check the upper nodes for it to be a minheap.
void actualize(double new_distance, int position, minHeap* minheap) {
  int currentPosition = minheap->pos[position];
  if((minheap->nodes[currentPosition].distance > new_distance) && currentPosition <= minheap->tail) {
    minheap->nodes[currentPosition].distance = new_distance;
    if(currentPosition > 0){
      int parentPosition = parent(currentPosition);
      // now we hace to check the minHeap property again
  
  // we repeat the process we've used in minHeapPush:
  // While our currentPos is not the root and the value of the distance of our currentnode is less than the one of the parent node, we iterate :)
      while(currentPosition != 0 && (compareNodes(currentPosition,parentPosition,minheap) == 1)) {
        change(currentPosition,parentPosition,minheap);
        if(parentPosition > 0) {
          currentPosition = parentPosition;
          parentPosition = parent(currentPosition);
        }
      }
    }
  }
}

minHeapNode minHeapPop(minHeap* minheap) {
  // First, we change the positions of the first node and the one in the tail, we store our node first to then return it at the end.
  minHeapNode tmpnode = minheap->nodes[0];
  change(0,minheap->tail,minheap);

  // Now its turn to erase it (devilish face)
  minheap->tail--;

  // We proceed the same way as before but in the other direction.

  int currentNode = 0;
  int Lchild = L_child(currentNode,minheap->tail);
  int Rchild = R_child(currentNode,minheap->tail);
  int Bchild = low_child(Lchild,Rchild,minheap); // the one with the lowest distance

  // Bchild == -1 <==> Lchild == Rchild == -1 <==> they both are leaves
  while((currentNode != minheap->tail) && (Bchild != -1) && ((compareNodes(Bchild,currentNode,minheap)))) {
      // Bchild.distance < currentNode.distance
      change(Bchild,currentNode,minheap);
      currentNode = Bchild;
      Lchild = L_child(currentNode,minheap->tail);
      Rchild = R_child(currentNode,minheap->tail);
      Bchild = low_child(Lchild,Rchild,minheap);
  }

  return tmpnode;


}