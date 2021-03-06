/*
 David Parrott
 CS 330
 HW #4
 */
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

void Fbaseball(double t, const double X[], double R[]) {
  const double k = 0.002;
  const double g = 32.0;
  R[0] = X[1];
  R[1] = -k*(X[1])*sqrt(X[1]*X[1] + X[3]*X[3]);
  R[2] = X[3];
  R[3] = -k*(X[3])*sqrt(X[1]*X[1] + X[3]*X[3]) - g;
}

void Mercury(double t, const double X[], double R[]){
  const double sun = 1.9891e30;
  const double mer = 3.3022e23;
  const double G = 6.67384e-11;
  const double r = sqrt(X[0]*X[0] + X[2]*X[2]);
  const double F = (mer * sun * G)/(r*r);
  const double Fx = F*X[0]/r;
  const double Fy = F*X[2]/r;
  R[0] = X[1];
  R[1] = -Fx/mer;
  R[2] = X[3];
  R[3] = -Fy/mer;
}

int main() {
  double t = 0.0;
  double h = 0.1;
  
  double v = 208.0;
  double theta = 43*M_PI/180;
  double X[4];
  X[0] = 0.0; X[1] = v*cos(theta);
  X[2] = 3.0; X[3] = v*sin(theta);
  for (int n = 0; (t < 6.47859) && (n < 100); n++, t += h) {
    printf("%0.10f %0.10f\n", X[0], X[2]);
    // XXX Euler(4, t, h, X, Fbaseball, X);
    RK4(4, t, h, X, Fbaseball, X);
  }
  /*
  double t = 0.0;
  double h = 100;
  double X[4] = {46001200000.0, 0.0, 0.0, 58980.0};
  for(; t <= 7600521.6; t += h){
    printf("%0.10f %0.10f\n", X[0], X[2]);
    RK4(4, t, h, X, Mercury, X);
  }
  */
  return 0;
}
