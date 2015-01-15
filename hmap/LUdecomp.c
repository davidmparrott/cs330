#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "./LUdecomp.h"


void LUdestroy(LUdecomp* A){
  for(int i = 0; i < A -> N; i ++){
    free(A -> LU[i]);
  }
  free(A->LU);
  free(A->mutate);
  free(A);  
  return;
}

LUdecomp *LUdecompose(int N, const double **A){
  /*
    Create a new matrix decomp to store the values from A. 
    Memory is allocated on the heap for all of the elements
    and values are copied into the LUdecomp struct. Mutate[]
    is filled with values 0-(N-1) andd is set to '1' 
    initially. 
   */

  LUdecomp* decomp = (LUdecomp*) malloc(sizeof(LUdecomp));
  decomp->N = N;
  decomp->LU = (double**)malloc(N*sizeof(double*));
  int counter = 0;
  for(int j = 0; j < N; j++)
    decomp->LU[j] = (double*)malloc(N*sizeof(double));
  for(int r = 0; r < N; r++){
    for(int c = 0; c < N; c++){
      decomp->LU[r][c] = A[r][c];
    }
  }
  decomp -> mutate = (short*)malloc(N*sizeof(short));
  for(int i = 0; i < N; i++){
    decomp->mutate[i] = (short)i;
  }
  
  
  decomp->d = 1; 
  
  double p;
  int n;
  for(int j = 0; j < N; j++){
    counter++;
    for(int i = 0; i <= j; i++){
      double sum = 0;
      for(int k = 0; k < i; k++){
	sum += (decomp->LU[i][k]*decomp->LU[k][j]);
      }
      decomp->LU[i][j] = decomp->LU[i][j] - sum;
      p = fabs(decomp->LU[j][j]);
      n = j;
    }
    for(int i = j+1; i < N; i++){
      double sum = 0;
      for(int k = 0; k < j; k++){
	sum += (decomp->LU[i][k]*decomp->LU[k][j]);
      }
      decomp->LU[i][j] = decomp->LU[i][j] - sum;
      if(fabs(decomp->LU[i][j] > p)){
	p = fabs(decomp->LU[i][j]);
	n = i;
      }
    }
    if(p == 0){
      printf("singular matrix found on iteration %i\n", counter);
      exit(1);
    }
    if(n != j){
      //SWAP n and j of A
      double* temp = decomp->LU[n];
      decomp->LU[n] = decomp->LU[j];
      decomp->LU[j] = temp;
      short t = decomp->mutate[n];
      decomp->mutate[n] = decomp->mutate[j];
      decomp->mutate[j] = t;
      decomp->d = -1;
    }
    for(int i = j+1; i < N; i++){
      decomp->LU[i][j] = (decomp->LU[i][j]) / (decomp->LU[j][j]);      
    }
  }
  
  return decomp;
}
 
void LUsolve(LUdecomp *decomp, const double *b, double *x){
  double y[decomp -> N];
  y[0] = b[decomp -> mutate[0]];

  double sum;
  for(int i = 0; i < decomp -> N; i++){
    sum = 0;
    for(int j = 0; j < i; j++){
      sum += decomp -> LU[i][j] * y[j];
    }
    y[i] = b[decomp -> mutate[i]] - sum;
  }
  x[(decomp->N)-1] = (y[(decomp->N)-1])/(decomp->LU[(decomp->N)-1][(decomp->N)-1]);
  for(int i = (decomp->N)-2; i >= 0; i--){
    sum = 0;
    for( int j = i + 1; j < decomp->N; j++){
      sum += decomp->LU[i][j] * x[j];
    }
    x[i] = (1 / decomp->LU[i][i]) * (y[i] - sum);
  }
  return;
}
