#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//
//   X(t+h) = X(t) + h*F(t,X) 
//
void Euler(int N, double t, double h, const double X[],
	 void (*F)(double t, const double X[], double R[]),
	 double R[]) {
  double T[N];
  F(t,X,T);
  for (int i = 0; i < N; i++)
    R[i] = X[i]+ h*T[i];
}

void RK4(int N, double t, double h, const double X[],
	 void (*F)(double t, const double X[], double R[]),
	 double R[]) {
  double K1[N];
  F(t,X,K1);

  double T[N], K2[N];
  for (int i = 0; i < N; i++)
    T[i] = X[i] + h/2*K1[i];
  F(t+h/2,T,K2);

  double K3[N];
  for (int i = 0; i < N; i++)
    T[i] = X[i] + h/2*K2[i];
  F(t+h/2,T,K3);

  double K4[N];
  for (int i = 0; i < N; i++)
    T[i] = X[i] + h*K3[i];
  F(t+h,T,K4);

  for (int i = 0; i < N; i++)
    R[i] = X[i] + h/6*(K1[i] + 2*(K2[i] + K3[i]) + K4[i]);
}

const double G = 32;

void Farrow(double t, const double X[], double R[]) {
  R[0] = X[1];  // velocity
  R[1] = -(1/25.0)*X[1] - G;    // acceleration
}

void Fbaseball(double t, const double X[], double R[]) {
  const double k = 0.25;
  const double g = 32.0;
  R[0] = X[1];
  R[1] = -k*X[1];
  R[2] = X[3];
  R[3] = -k*X[3] - g;
}

#ifdef ARROW_XXX

int main() {
  double t = 0.0;
  double h = 0.1;
  double X[2] = {0, 300.0};
  for (int i = 0; i < 300; i++, t += h) {
    printf("%0.10f %0.10f\n", t, X[0]);
    RK4(2, t, h, X, Farrow, X);
  }
  return 0;
}

#endif

int main() {
  double t = 0.0;
  double h = 0.1;
  double v = 207.0;
  double theta = 40*M_PI/180;
  double X[4];
  X[0] = 0.0; X[1] = v*cos(theta);
  X[2] = 3.0; X[3] = v*sin(theta);
  for (t = 0.0; t <= 7.0; t += h) {
    printf("%0.10f %0.10f\n", X[0], X[2]);
    // XXX Euler(4, t, h, X, Fbaseball, X);
    RK4(4, t, h, X, Fbaseball, X);
  }
  return 0;
}
