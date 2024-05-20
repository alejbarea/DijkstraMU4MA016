
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>
    
void store_rand_Graph(const char* f)
{
  srand (time(NULL)); // we set a seed
  FILE *pFile;
  
  // we open the file in mode "write"
  pFile = fopen(f,"w");
  printf("1\n");
  int dim = 1400;
  fprintf(pFile,"Vertices\n");
  fprintf(pFile,"%d\n",dim);
  fprintf(pFile,"Matrix\n");
  printf("2\n");
  int T[dim][dim];
  for(int i = 0; i < dim; i++){
    for(int j = 0; j < dim; j++){
      T[i][j] = 0;
    }
  }

  printf("3\n");
  for(int i = 0; i < dim; i++){
    for(int j = i+1; j < dim; j++){
      int r = rand() % 10; 
      if(r > 3) r = 0;  
      T[i][j] = r;
      T[j][i] = r;
    }
  }
  printf("4\n");
  for(int i = 0; i < dim; i++){
    for(int j = 0; j < dim; j++){
      fprintf(pFile,"%d ",T[i][j]);
    }
    fprintf(pFile,"\n");
  }
  
  fclose(pFile);
}

/*
int main() {
  store_rand_Graph("prueba7.txt");
  return 0;
}
*/

/*
int main()
{
  int k = 7;
  char NN[7][20] = {"prueba.txt","prueba2txt","prueba3.txt","prueba4.txt","prueba5.txt","prueba6.txt","prueba7.txt"};
  float tt[k];
  for(int i = 0; i < k; i++){
    char chaine[200];
    strcpy(chaine,"./Dijkstra ");
    strcat(chaine,NN[i]);
    clock_t time = clock();
    // printf("%s\n",chaine);
    system(chaine);
    time = clock() - time;
    tt[i] = ((float)time)/CLOCKS_PER_SEC;
    printf("Temps d'execution: %f sec\n\n",tt[i]);
  }

  // données de la courbe du temps ConstructEdges
  FILE *pFile;
  pFile = fopen("temps.txt","w");
  for (int i = 0; i < k; i++) {
    fprintf(pFile,"%d\t%f\n",i,tt[i]);
  }
  FILE *pFile2;
  pFile2 = fopen("NlogN.txt","w");
  for (int i = 1; i < k+1; i++) {
    double j = i*10000;
    fprintf(pFile2,"%d\t%lf\n",i-1,j*log(j));
  }

  return 0;
  }
*/