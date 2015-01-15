David Parrott
CS330 Numerical Computing
Fall 2013 WSUV
Programming Project 1, Computing exp(x)

package contents:
e_x.c
relerror.c
README.TXT

program descriptions:
e_x.c
Computes e^x manually and compares results to the c library exp() function
for values from -20 to 20. Results are calculated and displayed automatically
when e_x.c is compiled and executed.

relerror.c
Used to compute the smallest value, n, such that the relative error is
guaranteed to be below 1.19209*10^-7. Steps from 1 to 15 and prints the
error associated with a given value, n, as well as n!, which is used to
directly input values into the equation in e_x.c in lieu of calculating
factorial values at run time.

