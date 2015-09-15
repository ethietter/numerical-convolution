# Numerical Convolution #

### Introduction ###

This C++ program was written for my Signals and Systems class (UNM - ECE 314). It uses a numerical integration method to approximate the result of convolving two functions.  After the approximate convolution is computed, the program finds the trigonometric Fourier Series representation of the function in the limits that the function exists. It accepts as input (1) the two functions; (2) the finite limits between which each function exists (these limits do not have to be the same for each function); (3) the resolution to use to approximate the convolution; and (4) the number of Fourier coefficients to compute.

It outputs the result of the convolution in a format that can be plotted using MATLAB.

### Building the program ###

The program can be built using the provided Makefile. The Boost C++ library is required - the provided Makefile assumes this library is located at ~/lib/boost_1_56_0.  

Since it was written on a Windows platform (MinGW/g++), the resultant program has a .exe extension

### Running the program ###

Convolution.exe accepts input via the following command line arguments: 

* --fn1: (String) First function to convolve (independent variable is t)
* --fn2: (String) Second function to convolve (independent variable is t)
* --t1min and --t1max: (Float) Limits between which fn1 is defined, inclusive
* --t2min and --t2max: (Float) Limits between which fn2 is defined, inclusive
* --datapoints: (int) Number of discrete data points used to plot the final convolution function.
* --fourier: (int) Number of Fourier coefficients to compute
* --help: (No arguments) Prints usage instructions