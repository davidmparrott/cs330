David Parrott
LUdecomposition
11/4/13
CS 330

LUdecomp solves linear equations of the form Ax = b using LU decomposition. A matrix is
passed as an array of doubles to LUdecomp along with the size (assumed to be nXn). 

LUsolve finds the matrix solution.

LUdecompose frees space on the heap allocated to a given matrix.

To build:
./make
(note: ./make clean will remove files created during compilation)

To run:
LUdecomop has no main. It must be called by another program that builds matrices to
pass. Included is LUtest.c which will pass a 5X5, 10X10 and 600X600 matrix as
test cases

File list:
LUdecomp.h
LUdecomp.c
LUtest.c
Makefile
README.txt