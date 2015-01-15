David Parrott
david.m.parrott@email.wsu.edu

Estimating Pi using Numerical Integration
pi.c uses four methods of numerical intergration to estimate pi. Instead of
displaying what the estimation of pi is, pi.c uses a pre-defined value for 
pi (3.1415926535897932384626433827950288) and compares the estimation with
this value, displaying the error between calculated and defined for each
method in a table. 

Each method of numerical integration is contained within a subroutine. 
Trapezoid - trap()
Simpson's Composite 1/3 - simpsons13()
Simpson's Composite 3/8 - simpsons38()
Boole's Rule - booles()
The four subroutines are passed f(), a, b, n in identical manner.

To Compile:
gcc -std=c99 -Wall -pedantic pi.c -o pi

To Execute:
./pi

file list:
pi.c
README.TXT