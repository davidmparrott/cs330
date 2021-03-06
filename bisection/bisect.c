#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <float.h>

//bisection gets a function passed as well as a bracket to evaluate
float bisection(float (*f)(float), float a, float b){
  assert(b > a); //will exit if this is not true
  //store end points for efficiency
  float fa = f(a);
  float fb = f(b);
  //float maga = absf(a);
  //float magb = absf(b);
  assert(fa*fb < 0);
  const float mag = (fabsf(a) + fabsf(b))/2;
  //a and b must have opposite signs in order for the function
  //to equal 0 at some point between them
  //assert(fa*fb > 0);
  float c;
  double err = (b - a) / 2;
  for (;;) {
    //guess the point in the middle
    c = 0.5 * (a + b);
    err /= 2;
    if ( err <= FLT_EPSILON * mag)
      return c;
    const float fc = f(c);
    if (fa * fc < 0) {
      b = c;
      fb = fc;
    } else {
      a = c;
      fa = fc;
    }
  }
  
}

float f(float x){
  return x*(x-1)-15;
}

float falsePositioin(float (*f)(float), float a, float b) {
  assert (b > a);
  float fa = f(a);
  float fb = f(b);
  assert(fa * fb < 0);
  const float mag = (fabsf(a) + fabsf(b))/2;
  float c, fc;
  int leftMoves = 0, rightMoves = 0;
  const int maxIters = 100;
  for (int iters = 0; iters <= maxIters; iters++){
    if (leftMoves >= 2){
      c = (a * fb - 2*b*fa)/(fb-2*fa);
      leftMoves = 0;
    } else if (rightMoves >= 2) {
      c = (a * 2 * fb - b * fa)/(2 * fb - fa);
      rightMoves = 0;
    } else {
      c = (a*fa - b*fb)/(fb-fa);
    }
    fc = f(c);
    if (fa * fc < 0){
      if (b <= c) break;
      b = c;
      fb = fc;
      rightMoves++;
      leftMoves =0;
    } else {
      if (a >= c) break;
      a = c;
      fa = fc;
      rightMoves = 0;
      leftMoves++;
    }
    if ((b - a) <= FLT_EPSILON * mag) {
      break;
    }
    return c;
  }
}
#define MAX(a,b) ((a) > (b)?(a):(b));

float newton(float (*f)(float), float (*df)(float), float x){
  const float mag = MAX(fabsf(x), 1);
  const int maxIters = 100;
  for ( int iters = 0; iters <= maxIters; iters++) {
    float xnext = x - f(x)/df(x);
    if (fabsf(x - xnext) < FLT_EPSILON*mag)
      break;
    x = xnext;
  }
}

float df (float x) {
  return x;
}

int main() {
  //  float r = bisection(f, 4, 5);
  float r = newton( f, df, 2);
  printf("r = %0.10f\n", r);
  return 0;
}
