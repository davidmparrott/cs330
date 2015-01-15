#include <stdlib.h>
#include <stdio.h>
#include "LUdecomp.h"

int main(){
  /*
    Create N
    Create matrix to hold the original set of x,y coordinates (xy_source)
    Create matrix to hold the transformed set of x,y coordinates (xy_target)
   */
  int N = 0;

  //get N from first line of text file
  scanf("%d", &N);
  double xy_source[N][2];
  double xy_target[N][2];

  //get the x and y values from input file
  for(int i = 0; i < N; i++){
    scanf("%lf %lf", &xy_source[i][0], &xy_source[i][1]);
  }
  for(int i = 0; i < N; i++){
    scanf("%lf %lf", &xy_target[i][0], &xy_target[i][1]);
  }
  
  //Create matrix to hold A
  double** A = (double**)malloc(2*N*sizeof(double*));
  //make room on the heap for A
  for(int i = 0; i < 2*N; i++)
    A[i] = (double*)malloc(8*sizeof(double));

  /*
    begin filling Matrix A
   */
  int count = 0;
  //column 1
  for(int j = 0; j < 2*N; j ++)
    if(j % 2 == 0)
      A[j][0] = xy_source[count++][0];
    else
      A[j][0] = 0;

  count = 0;
  //column 2
  for(int j = 0; j < 2*N; j++)
    if(j % 2 == 0)
      A[j][1] = xy_source[count++][1];
    else
      A[j][1] = 0;

  count = 0;
  //column 3
  for(int j = 0; j < 2*N; j++)
    if(j % 2 == 0)
      A[j][2] = 1;
    else
      A[j][2] = 0;

  count = 0;
  //column 4
  for(int j = 0; j < 2*N; j++)
    if(j % 2 == 0)
      A[j][3] = 0;
    else
      A[j][3] = xy_source[count++][0];

  count = 0;
  //column 5
  for(int j = 0; j < 2*N; j++)
    if(j % 2 ==0)
      A[j][4] = 0;
    else
      A[j][4] = xy_source[count++][1];

  count = 0;
  //column 6
  for(int j = 0; j < 2*N; j++)
    if(j % 2 == 0)
      A[j][5] = 0;
    else
      A[j][5] = 1;

  count = 0;
  //column 7
  for(int j = 0; j < 2*N; j++){
    if(j % 2 == 0){
      A[j][6] = (-1)*(xy_source[count][0])*(xy_target[count][0]);
    }else{
      A[j][6] = (-1)*(xy_source[count][0])*(xy_target[count][1]);
      count++;
    }
  }

  count = 0;
  //column 8
  for(int j = 0; j < 2*N; j++){
    if(j % 2 == 0){
      A[j][7] = (-1)*(xy_source[count][1])*(xy_target[count][0]);
    }else{
      A[j][7] = (-1)*(xy_source[count][1])*(xy_target[count][1]);
      count++;
    }
  }

  //Create and make room on heap for matrix b
  double* b = (double*)malloc(2*N*sizeof(double));
  //populate matrix b from xy_target
  count = 0;
  for(int j = 0; j < 2*N; j += 2){
    b[j] = xy_target[count][0];
    b[j+1] = xy_target[count++][1];
  }

  //Create and make room on heap for matrix x 
  double* x = (double*)malloc(8*sizeof(double));
  for(int j = 0; j < 8; j++)
    x[j] = 0.0;
  
  /*
    Create matrix to hold A transpose A
  */
  double** A_T_A = (double**)malloc(8*sizeof(double*));
  for(int i = 0; i < 8; i++){
    A_T_A[i] = (double*)malloc(8*sizeof(double));
  }
  //Create matrix to hold A transpose b  
  double* A_T_b = (double*)malloc(8*sizeof(double));
  
  /*
    If N > 4 we have an overdetermined system and must use the method of least-squares 
  */
  if(N > 4){
    double sum = 0.0;
    for(int i = 0; i < 8; i++){
      for(int j = i; j < 8; j++){
	sum = 0.0;
	for(int k = 0; k < 2*N; k++){
	  sum += A[k][i]*A[k][j];
	}
	A_T_A[i][j] = sum;
      }
    }
    for(int i = 0; i < 8; i++)
      for(int j = 0; j < i; j++)
	A_T_A[i][j] = A_T_A[j][i];

    sum = 0.0;    
    for(int i = 0; i < 8; i++){
      sum = 0.0;
      for(int j = 0; j < 2*N; j++)
	sum += A[j][i] * b[j];
      A_T_b[i] = sum;
    }
  }

  if(N == 4){
    LUdecomp* A_decompose = LUdecompose(2*N, (const double**)A);  
    LUsolve(A_decompose, b, x);
  }else{
    LUdecomp* A_T_decompose = LUdecompose(8, (const double**)A_T_A);
    LUsolve(A_T_decompose, A_T_b, x);
  }
    

  /*
    Print out the homography in row major order
  */
  for(int i = 0; i < 3; i++)
    printf("%lf ", x[i]);
  printf("\n");
  for(int i = 3; i < 6; i++)
    printf("%lf ", x[i]);
  printf("\n");
  for(int i = 6; i < 8; i++)
    printf("%lf ", x[i]);
  double one = 1.0;
  printf("%lf ", one);  
  return 0;
}
