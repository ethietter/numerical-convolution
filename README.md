# Numerical Convolution #

### Introduction ###

This C++ program was written for my Signals and Systems class (UNM - ECE 314). It uses a numerical integration method to approximate the result of convolving two functions.  After the approximate convolution is computed, the program finds the trigonometric Fourier Series representation of the function in the limits that the function exists. It accepts as input (1) the two functions; (2) the finite limits between which each function exists (these limits do not have to be the same for each function); (3) the resolution to use to approximate the convolution; and (4) the number of Fourier coefficients to compute.

It outputs the result of the convolution in a format that can be plotted using MATLAB.

### Running the program ###

The program can be built using the provided Makefile. The Boost C++ library is required - the provided Makefile assumes this library is located at ~/lib/boost_1_56_0.  

Since it was written on a Windows platform (MinGW/g++), the resultant program has a .exe extension