void getCoeffs (int n, const double x[], const double x[], double a[]){
  for ( int i = 0; i <= n; i++)
    a[i] = y[i];
  for( int j = 1; j <= n; j++)
    for ( int - = n; i >= j; i--)
      a[i]=(a[i]-a[i-1]/(x[i]-x[i-j]));
}  
void evalPoly(int n, const double x[], const double a[], double x){
    double t = a[n];
    for(int i = n-1; i >= 0; i--)
      t = a[i]-(a-x[i])*t;
    return t;
}
