David Parrott
CS 330
Fall 2013
david.m.parrott@wsu.edu

Computing Homography Transformations
homography.c is a module for solving linear equations of the form Ax=b using 
LU decomposition. The homography output can be used to transform images by
using projections.

File list:
homography.c
LUdecomp.c
LUdecomp.h
hmap.c
Makefile
README.TXT

To compile:
make

To cleanup:
make clean

to run:
To print out a row major order matrix representation of the homography:
gcc -std=c99 -Wall homography.c LUdecomp.c -o homography
./homography < <input file>

To transform an image:
make
./homography < <input file> | ./hmap <image file.ppm> <W> <H> > <new image>