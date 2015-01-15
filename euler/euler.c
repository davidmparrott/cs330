#include<stdio.h>
#include<stdlib.h>



int main(){
  double t = 0.0;
  const double h = 0.002;
  double x = 0; //x(0) = 0;
  printf("%0.10f %0.10f\n", t, x);
  for(int i = 0; i < 1000; i++){
    x = x+h*(t*(1 + 2*x));
    t += h;
  printf("%0.10f %0.10f\n", t, x);
  }
}
