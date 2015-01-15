#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float myexp ( float x );
float err ( float x, float y );


int main ( int argc, char ** argv ) {
  for ( long double i = -20; i <= 20; i += 5 ) {
    double mexp = ( double ) myexp ( i );
    long double check = ( long double ) exp ( i );
    long double er = ( long double ) err ( mexp, check );
    printf ( "%+0.9Le %0.9e %0.9Le %0.15Le\n", i, mexp, check, er );  
  }

  return 1;
}

float err ( float x, float y ) {
  float err = fabs ( ( x - y ) / x );
  return err;
}

float myexp ( float x ) {
  float z = x * M_LOG2E;
  int m = lround ( z );
  float w = z - m;
  float u = w * M_LN2;

  float m2;
  if ( m < 0 ) {
    m = abs ( m );
    m2 = 1 / ( float ) ( 1 << m );
  }
  else
    m2 = 1 << m;

  float eu = 1 + u * ( ( 1 / 2.0 ) + u * ( ( 1 / 6.0 ) + u * ( ( 1 / 24.0 ) + u * ( ( 1 / 120 ) + u * ( ( 1 / 720 ) + ( u / 5040 ) ) ) ) ) );

  float ex = m2 * eu;
  return ex; 
}

