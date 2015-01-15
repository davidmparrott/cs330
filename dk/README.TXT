Durand-Kerner Method
David Parrott
david.m.parrott@email.wsu.edu

dk.c uses the Durand-Kerner Method to find the complex roots of ploynomials.
dk.c assumes that the polynomial to be solved does not contain more than
20 roots. Arrays that hold coefficients and roots are hard coded to only
allow 20 entries.

Polynomials to be solved are read into dk.c from stdin from a file in plain
text format (./dk < poly.txt). Real and imaginary parts of roots must be on
one line with one white space character seperation (1 2).

When dk.c executes a maximum of 50 iterations will be displayed as the function
converges towards probable roots. If the precision of the algorithm exceeds
common machine precision (10^-6 in this case) dk.c will exit before a 50
iterations.

To build from souce:
gcc -g -std=c99 -Wall -pedantic dk.c -o dk -lm

file list:
dk.c
READMET.TXT