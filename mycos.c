#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float mycos ( float x ) {
  x = fabsf( x );
  const int n = ( int ) floorf( x / ( 2 * M_PI ) );
  x -= n * ( 2 * M_PI );
  if ( x > M_PI ) 
    x = 2 * M_PI -x;
  float sign = +1;
  if ( x >= M_PI/2 ) {
    x = M_PI - x;
    sign = -1;
  }
  const float u = x - M_PI/4;
  const float r = M_SQRT2/2 * ( 1 + u * ( -1 + u * (-0.5 + ( 1 / 6.0 ) * u ) ) );
  /*return sign * r; */
  return copysignf ( r, sign );

  int main () {
    const float y = mycos ( 0.0f );

}
