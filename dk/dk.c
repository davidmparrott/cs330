#include <math.h>
#include <stdio.h>
#include <complex.h>
#include <float.h>
#include <assert.h>


double complex evalPoly(int n, const double complex c[], double complex z) {
  assert(n >= 2);
  double complex u = z+c[n-1];
  for (int i = n-2; i >= 0; i--){
    u = u*z + c[i];
  }
  return u;
}

int main(){
  int n;
  double complex c[20];
  double complex z[20];
  double complex delZ[20];
  int i = 0;
  double a, b; 
  int kmax = 50;
  double complex Q;
  double zMax;

  while (scanf("%lf %lf", &a, &b) == 2) {
    c[i++] = a + b * I;
  }
  n = i;

  double maxCo = 0;
  for ( int i = 0; i < n; i++) {
    double x = cabs(c[i]);
    if ( x > maxCo)
      maxCo = x;
  }
  double R = maxCo + 1;

  for ( int j = 0; j < n; j++){
    double t = j * (2* M_PI)/n;
    z[j] = (cos(t) + I*sin(t)) * R;
  }
 
  for ( int k = 1; k <= kmax; k++){
    printf("iter %d\n", k);
    for ( int j = 0; j < n; j++){
      printf("z[%d] = %lf + %lf i\n", j, creal(z[j]), cimag(z[j]));
    }

    zMax = 0;

    for ( int j = 0; j < n; j++) {
      Q = 1;
      for ( int i = 0; i < n; i++ ) {
	if ( i == j ) 
	  continue;
	Q = Q * (z[j] - z[i]);
      }

      double complex fz = 0;
      fz = evalPoly(n, c, z[j]);
      delZ[j] = -fz/Q;
      if (cabs(delZ[j]) > zMax) 
	zMax = cabs(delZ[j]);
    }
    for(int j = 0; j < n; j++){
      z[j] = z[j] + delZ[j];
    }

    if(zMax <= .000001)
      break;
  }
  return 0;
}
