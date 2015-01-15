#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846262338327950288
#endif

long double f(long double x){
  return 4.0L/(1.0L + x*x);
}

long double trap(long double (*f)(long double), 
		      long double a, long double b, int n){
  long double h = (b - a)/n;
  long double s = f(a) + f(b);
  long double x = a + h;

  for(int i = 1; i < n; i++){
    s += 2 * f(x);
    x += h;
  }
  return s * h / 2.0;
}

long double simpsons(long double (*f)(long double), long double a,
		       long double b, int n){
  assert((n & 1) == 0);
  long double h = (b - a)/n;
  long double s = f(a) + f(b);
  for(int i = 1; i < n; i+=2){
    s += 4 * f(a + i * h);
  }
  for(int i = 2; i < n; i += 2){
    s += 2 * f(a + i * h);
  }
  return s*h/3;
}

long double simpsons38(long double(*f)(long double), long double a,
		       long double b, int n){
  int m = 3 * n;
  long double h = (b - a) / m;
  long double s = f(a) + f(b);
  long double x = a + h;
  int j = 1;
  for( int i = 1; i < m; i ++){
    if (j == 3){
      s += 2*f(x);
      x += h;
      j = 1;
    }else{
      s += 3*f(x);
      x += h;
      j++;
    }
  }
  return (3*h*s)/8.0;
}

    


 
long double booles(long double (*f)(long double), long double a, 
		   long double b, int n){ 
  long double h = (b - a)/(4 * n);
  long double x;
  long double s = 7*f(a) + 32*(f(a + h) + f(a + (3 * h))) + 12*f(a + (2*h)) + 
    7*f(b);

  for(int i = 1; i < n; i++){
    x = a + 4*i*h;
    s += (14*f(x) + 32*(f(x + h) + f(x + 3*h)) + 12*f(x + 2*h));
  }
  return (4*h*s)/90;
}




int main(void){
  const unsigned maxn = 800000;
  printf("n\t trapezoid\t simpsons13\t simpsons38\t booles\n");
  for(unsigned n = 12; n <= maxn; n *= 2){
    const long double I_trap = trap(f, 0, 1, n);
    const long double error_trap = fabsl(M_PI - I_trap);
    const long double I_simp = simpsons(f, 0, 1, n);
    const long double error_simp13 = fabsl(M_PI - I_simp);
    const long double I_simp38 = simpsons38(f, 0, 1, n);
    const long double error_simp38 = fabsl(M_PI - I_simp38);
    const long double I_booles = booles(f, 0, 1, n);
    const long double error_booles = fabsl(M_PI - I_booles);
    printf("%6d %0.10Le %0.10Le %0.10Le %0.10Le\n", n,
	   error_trap, error_simp13, error_simp38, error_booles);
  }
  return 0;
}
