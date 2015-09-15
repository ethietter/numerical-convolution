# Numerical Convolution #

### Introduction ###

This C++ program was written as the final project for my Signals and Systems class (UNM - ECE 314). It uses a numerical integration method to approximate the result of convolving two functions.  After the approximate convolution is computed, the program finds the trigonometric Fourier Series representation of the function in the limits that the function exists. It accepts as input (1) the two functions; (2) the finite limits between which each function exists (these limits do not have to be the same for each function); (3) the resolution to use to approximate the convolution; and (4) the number of Fourier coefficients to compute.

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

# Writing the program #

### Parsing and Tokenization ###

The intent of the project was to gain a more in-depth understanding of what convolution was. This goal was achieved, however, I found the parsing and tokenization process to be the most challenging module to implement. Here is an overview of how this was done:

A UserFunction object is used to store details about each function. It is initialized with the string value of the function and the function’s minimum and maximum time values.  The first stage of processing is tokenization. This stage involves reading through the string value of the function and breaking it into tokens so it can be evaluated.  Token types include functions (cos, sin, exp, ln, etc.), operators (+, -, *, /, ^), closing and opening parentheses, variables (t), and numbers (constant floating point values).

After the function is tokenized, the Shunting-Yard algorithm is used to convert the traditionally recognized infix notation (i.e. 5 + 7) to Reverse Polish Notation (i.e. 5 7 +). Converting to Reverse Polish Notation (RPN) is useful because it makes evaluating the function significantly easier. With RPN, a simple stack can be used to evaluate the function, which can be read linearly without worrying about operator precedence.