#include <stdio.h>
#include <stdlib.h>
//#include gauss.h
//#include <float.h>
#include <math.h>

double **createMatrix (int N) {
  double **A = (double **) malloc(N*sizeof(double *));
  for(int i = 0; i < N; i++)
    A[i] = (double *) malloc(N*sizeof(double));
  return A;
}

void destroyMatrix(int N, double **A){
  for(int i = N-1; i >= 0; i--)
    free(A[i]);
  free(A);
}

int solve( int N,  double **A, double b[], double x[]){
  for (int i = 0; i < N; i++) {

    int q = i;
    float pivot = fabs(A[i][i]);
    for(int j = i+1; j < N; j++){
      const double v = A[j][i];
      if(v > pivot){
	pivot = v;
	q = j;
      }
    }
    if (pivot == 0.0) return 0;
    if ( q != i){
      double *tmp = A[i]; //swap rows i and q of A
      A[i] = A[q];
      A[q] = tmp;
      double x = b[i]; //swap rows b[i] and b[q]
      b[i] = b[q];
      b[q] = x;
    }
    for ( int j = i + 1; j < N; j++){
      const double s = -A[j][i]/A[i][i];
      for( int k = 0; k < N; k++)
	A[j][k] += s*A[i][k];
      b[j] += s*b[i];     
    }
  }
  x[N-1] = b[N-1]/A[N-1][N-1];
  for (int i = N - 2; i >= 0; --i){
    double sum = 0.0;
    for (int j = i + 1; j < N; j++)
      sum += A[i][j]*x[j];
    x[i] = (b[i] - sum)/A[i][i];
  }
  return 1;
}

#ifdef TEST_GAUSS

int main(){
  double **A = createMatrix(3);
  A[0][0] = 2;  A[0][1] = 1; A[0][2] = 2;
  A[1][0] = -2; A[1][1] = 2; A[1][2] = -3;
  A[2][0] = 6;  A[2][1] = 9; A[2][2] = 9;
  double b[] = {1, 1, 17};
  double x[3];

  solve (3, A, b, x);

  printf("%0.10f %0.10f %0.10f\n", x[0], x[1], x[2]);
 
  destroyMatrix(3, A);
  return 0;
}

#endif
