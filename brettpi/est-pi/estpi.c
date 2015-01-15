/**
Brett Carter
brett.carter@wsu.edu
CS330 - numerical computing
assignment #2 - estimating pi
 **/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288  /*pi*/
#endif

//the four methods of integration to estimate pi.


long double f(long double x){
  return 4.0L/(1.0L + x*x);
}

long double trapezoid(long double (*f)(long double), long double a,
		      long double b, int n){
  long double h = (b-a)/n;
  long double x = a+h;
  long double sum = f(a) + f(b);
  
  for(int i = 1; i < n; i++){
    sum += 2*f(x);
    x += h;
  }
  return (h*sum)/2.0;
}

long double simpsons13(long double(*f)(long double), long double a,
		       long double b, int n){
  //n must be even.
  
  //set-up initial vars.
  long double h = (b-a)/n;
  long double sum = f(a) + f(b);
  long double x = a + h;
  
  for(int i = 1; i < n; i += 2){
    //sum up the 4*f(x);
    sum += 4*f(x);
      x += 2*h;
  }
  //reset x to the second iteration.
  x = a + 2*h;
  for(int i = 2; i < n; i += 2){
    //sum up for the 2*f(x);
    sum += 2*f(x);
    x += 2*h;
  }
  return (h*sum)/3.0;
}

long double simpsons38(long double(*f)(long double), long double a,
		       long double b, int n){
  int m = 3*n;
  long double h = (b-a)/m;
  long double sum = f(a) + f(b);
  long double x = a + h;  //second input value.
  int j = 1;
  for(int i = 1; i < m; i++){
    if(j == 3){
      sum += 2*f(x);
      x += h;
      j = 1;
    }
    else{
      sum += 3*f(x);
      x += h;
      j++;
    }
  }
  return (3*h*sum)/8.0;
}

long double booles(long double (*f)(long double), long double a,
		 long double b, int n){
  int m = 4*n;
  long double h = (b-a)/m;
  long double x;
  //sum the end points and 3 midpoints.
  long double sum = 7*f(a) + 32*(f(a+h) + f(a+(3*h))) + 12*f(a+(2*h)) + 7*f(b);
  //sum the remaining terms in the 4 subintervals.
  for( int i = 1; i < n; i++){
    x = a + 4*i*h;
    sum += (14*f(x) + 32*(f(x+h)+f(x+(3*h))) + 12*f(x+(2*h)));
  }
  return (4*h*sum)/90;
}

int main(){
  const unsigned maxn = 800000;
  printf("n\t trapezoid\t simpsons13\t simpsons38\t booles\n");
  for(unsigned n = 12; n <= maxn; n *= 2){
    const long double trap = trapezoid(f,0,1,n);
    const long double traperr = fabs(M_PI - trap);
    const long double simp13 = simpsons13(f,0,1,n);
    const long double simp13err = fabs(M_PI - simp13);
    const long double simp38 = simpsons38(f,0,1,n);
    const long double simp38err = fabs(M_PI - simp38);
    const long double I_bool = booles(f,0,1,n);
    const long double I_boolerr = fabs(M_PI - I_bool);

    printf("%5d %0.10Le %0.10Le %0.10Le %0.10Le\n", n, traperr, simp13err,
	   simp38err, I_boolerr);
  }
  return 0;
}
