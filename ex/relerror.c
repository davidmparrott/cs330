#include <math.h>
#include <stdio.h>

double fac ( double x );
/*
  fac() computes factorial recursively. Double is used to
  avoid casting in main.
 */
double fac ( double x ) {
  
  if ( x == 1 ) //base case
    return x;
  else {        //multiply and recurse
    double y = x * fac ( x - 1 );
    return y;
  }
  return 0;
}

/*
  main computes and prints the relative error to be used in myexp()
  natural ln2 / 2 is cached early to avoid redunt computations.
  fac() is used to quickly calculate factorials.
 */
int main ( int argc, char ** argv ) {
  double l = log ( 2 ) / 2;       //cache ln2/2
  for ( int i = 1; i <= 15; i++ ) {
    double f = 2 / fac ( i + 1 ); //f contains 2 / the factorial
    double p = pow ( l, i + 1 );  //p contains l ^ i+1
    double r = f * p;             //r holds the result of multiplying f * p
    printf ( "Relative error of %d is : %0.9lf\n", i, r );
    double x = fac ( i );
    printf ( "Factorial of %d is : %lf\n", i, x );
  }
}
