/**
Brett Carter
CS330 - num. comp.
LU decomposition
11/4/13
 **/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "LUdecomp.h"


void LUsolve(LUdecomp *decomp, const double *b, double *x){
  double y[decomp->N];
  y[0] = b[decomp->mutate[0]];
  for(int i = 0; i < decomp->N; i++){
    double sum = 0;
    for(int j = 0; j < i; j++){   //sum the lower triangle.
      sum += decomp->LU[i][j]*y[j];
    }
    y[i] = b[decomp->mutate[i]] - sum;
  }
  x[(decomp->N)-1] = (y[(decomp->N)-1])/(decomp->LU[(decomp->N)-1][(decomp->N)-1]);
  for(int i = (decomp->N)-2; i >= 0; i--){
    double sum = 0;
    for(int j = i+1; j < decomp->N; j++){
      sum += decomp->LU[i][j]*x[j];
    }
    x[i] = (1/decomp->LU[i][i])*(y[i] - sum);
  }
  return;
}

/** creates a new LUdecomp struct **/
LUdecomp* LUcreate(int n, const double** A){
  LUdecomp* B = (LUdecomp*)malloc(sizeof(LUdecomp));
  B->N = n;
  B->LU = (double**)malloc(n*sizeof(double*)); //allocate first level of matrix.
  for(int j = 0; j < n; j++){
    B->LU[j] = (double*)malloc(n*sizeof(double)); //second level of matrix.
  }
  for(int r = 0; r < n; r++){
    for(int c = 0; c < n; c++){
      B->LU[r][c] = A[r][c]; //put the values of a into the LU matrix.
    }
  }
  B->mutate = (short*)malloc(n*sizeof(short));
  for(int i = 0; i < n; i++){
    B->mutate[i] = (short)i;
  }
  return B;
}

LUdecomp* LUdecompose(int N, const double **a){
  LUdecomp* LUD = LUcreate(N,a);               //create a new LU struct
  LUD->d = 1;                                 //row swap parity value
  double P;                                   //pivot value
  int n;                                      //pivot row.
  for(int j = 0; j < N; j++){              // j is column
    for(int i = 0; i <= j; i++){             //i is row
      double sum = 0;
      for(int k = 0; k < i; k++){
	sum += (LUD->LU[i][k]*LUD->LU[k][j]);
      }
      LUD->LU[i][j] = LUD->LU[i][j] - sum;
      P = fabs(LUD->LU[j][j]);
      n = j;
    }
    for(int i = j+1; i < N; i++){
      double sum = 0;
      for(int k = 0; k < j; k++){
	sum += (LUD->LU[i][k]*LUD->LU[k][j]);
      }
      LUD->LU[i][j] = LUD->LU[i][j] - sum;
      if(fabs(LUD->LU[i][j]) > P){
	P = fabs(LUD->LU[i][j]);
	n = i;
      }
    }
    if(P == 0){  //singular matrix.
      printf("singular matrix");
      exit(1);
    }
    if(n != j){
      double* tempr = LUD->LU[n];
      //swap n and j rows in the matrix.
      LUD->LU[n] = LUD->LU[j];  
      LUD->LU[j] = tempr;
      //swap n and j rows in the mutable matrix.
      short tempm = LUD->mutate[n];
      LUD->mutate[n] = LUD->mutate[j];
      LUD->mutate[j] = tempm;
      LUD->d = -1;
    }
    for(int i = j+1; i < N; i++){
      LUD->LU[i][j] = (LUD->LU[i][j])/(LUD->LU[j][j]);
    }
  }
  return LUD;
}


void LUdestroy(LUdecomp* a){
  free(a);
  return;
}

