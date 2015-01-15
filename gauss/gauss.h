#ifndef GAUSS_H
#define GAUSS_H

int solve(int N, double **A, double b[], double x[]);
double ** createMatrix(int N);
void destroyMatrix(int N, double **A);

#endif //GAUSS_H
