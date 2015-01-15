/**
Brett Carter
brett.carter@wsu.edu
CS330 - Numerical Computing
Homography Assignment
 **/

#include <stdio.h>
#include <stdlib.h>
#include "LUdecomp.h"

/**function to fill the A array **/
void Afill(double** A, double** source, double** target, int N);
/** function to fill the B array **/
void Bfill(double* B, double** target, int N);

int main(){
  int N;  //number of source and target points.
  double x;
  double y;

  //grab the first values from the file which is the size.
  scanf("%i", &N);
  printf("N = %i\n", N);

  //2d array to hold the x,y pairs for the source points.
  double** Spoints = (double**)malloc(N*sizeof(double*));
  for(int i = 0; i < N; i++){
    Spoints[i] = (double*)malloc(2*sizeof(double));
  }
  
  //2d array to hold the x,y pairs for the target points.
  double** Tpoints = (double**)malloc(N*sizeof(double*));
  for(int i = 0; i < N; i++){
    Tpoints[i] = (double*)malloc(2*sizeof(double));
  }

  //fill both arrays with the given points.
  for(int i = 0; i < N; i++){
    scanf("%lf %lf", &x, &y);
    Spoints[i][0] = x;
    Spoints[i][1] = y;
  }
  printf("start point values:\n");
  for(int j = 0; j < N; j++){
    printf("(x,y) = (%lf,%lf)\n", Spoints[j][0], Spoints[j][1]);
  }

  for(int i = 0; i < N; i++){
    scanf("%lf %lf", &x, &y);
    Tpoints[i][0] = x;
    Tpoints[i][1] = y;
  }
  printf("target point values:\n");
  for(int j = 0; j < N; j++){
    printf("(x,y) = (%lf,%lf)\n", Tpoints[j][0], Tpoints[j][1]);
  }

  //create the full A matrix.
  double** A = (double**)malloc(2*N*sizeof(double*));
  for(int i = 0; i < 2*N; i++){
    A[i] = (double*)malloc(8*sizeof(double));
  }
  //fill in the proper values from the source and target values.
  Afill(A, Spoints, Tpoints, N);

  //create the B matrix.
  double* B = (double*)malloc(2*N*sizeof(double));
  Bfill(B, Tpoints, N);
  
  //create the empty X matrix.
  double* X = (double*)malloc(8*sizeof(double));
  for(int i = 0; i < 8; i++){
    X[i] =0.0;
  }

  LUdecomp* Adecomp = LUdecompose(N, (const double**)A);
  LUsolve(Adecomp, B, X); 
 
  for(int k = 0; k < 8; k++){
    printf("X%i : %f\n", k, X[k]);
  }
  return 0;
}

/** 
helper function to fill the array A with the input values.
 **/
void Afill(double** A, double** source, double** target, int N){
  int count = 0;
  //column 1.
  for(int j = 0; j < 2*N; j++){
    if(j%2 == 0){
      A[j][0] = source[count][0];
      count++;
    }else{
      A[j][0] = 0;
    }
  } 
  printf("column 1\n");
  //column 2.
  count = 0;
  for(int j = 0; j < 2*N; j++){
    if(j%2 == 0){
      A[j][1] = target[count][1];
      count++;
    }else{
      A[j][1] = 0;
    }
  }
  printf("column 2\n");
  //column 3.
  for(int j = 0; j < 2*N; j++){
    if(j%2 == 0){
      A[j][2] = 1;
    }else{
      A[j][2] = 0;
    }
  }
  printf("column 3\n");
  //column 4.
  count = 0;
  for(int j = 1; j < 2*N; j++){
    if(j%2 == 0){
      A[j][3] = 0;
    }else{
      A[j][3] = source[count][0];
      count++;
    }
  }
  printf("column 4\n");
  //column 5.
  count = 0;
  for(int j = 0; j < 2*N; j++){
    if(j%2 == 0){
      A[j][4] = 0;
    }else{
      A[j][4] = source[count][1];
      count++;
    }
  }
  printf("column 5\n");
  //column 6.
  for(int j = 0; j < 2*N; j++){
    if(j%2 == 0){
      A[j][5] = 0;
    }else{
      A[j][5] = 1;
    }
  }
  printf("column 6\n");
  //column 7.
  count = 0;
  for(int j = 0; j < 2*N; j++){
    if(j%2 == 0){
      A[j][6] = (-1)*(source[count][0])*(target[count][0]);
    }else{
      A[j][6] = (-1)*(source[count][0])*(target[count][1]);
      count++;
    }
  }
  printf("column 7\n");
  //column 8.
  count = 0;
  for(int j = 0; j < 2*N; j++){
    if(j%2 == 0){
      A[j][7] = (-1)*(source[count][1])*(target[count][0]);
    }else{
      A[j][7] = (-1)*(source[count][1])*(target[count][1]);
    }
  }
  printf("column 8\n");
}
/** helper function to fill array B. **/  
void Bfill(double* B, double** Tpoints, int N){
  int count = 0;
  for(int i = 0; i < 2*N; i += 2){
    B[i] = Tpoints[count][0];
    B[i+1] = Tpoints[count][1];
    count++;
  }
}




