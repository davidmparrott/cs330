#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>

float gold(float (*f)(float), float a, float b, float c, float tol){
  const float G = 0.3816;
  float fa = f(a), fb = f(b), fc = f(c);
  float x, fx;
  while (true) {
    
    if ( b - a > c - b) {
      x = b - G*(b - a);
      if (c - a < tol/2*(fabs(b) + fabs(x)))
	return (fb < fx) ? b:x;
      fx = f(x);
      if ( fx < fb ){
	c = b; fc = fb;
	b = x; f(b) = f(x);
      } else {
	a = x; fa = fx;
      }
    } else {
      x = b + G*(c - fx);
      if (c - a <= tol/2*(fabs(b) + fabs(x)))
	return (fb < fx) ? b:x; 
      fx = f(x);
      if (fb < fx){
	c = x; fc = fx;
      } else {
	a = b; fa = fb;
	b = x; fb = fx;
      }
    }
    
  }
  return 0;
}

flota f(float x){
  return -x*cosf(x);
}

int main(){
  float x = gold(f, 0, 1, 2, 1e-4);
  printf(" x = %0.10f\n", x);
  return 0;
}
