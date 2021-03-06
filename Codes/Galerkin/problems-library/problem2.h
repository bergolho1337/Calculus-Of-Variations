#ifndef PROBLEM2_H
#define PROBLEM2_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Constants
const double L = 1.0f;
const double I = 1.0f;
const double E = 1.0f;
const double M = 1.0f;

// Aproximation functions for the integral
double phi (const double x, const int i, const int j);
double Lphi (const double x, const int i, const int j);
double f (const double x, const int i, const int j);
// Integral
double Lphi_phi (const double x, const int i, const int j);
double f_phi (const double x, const int i, const int j);

// Analitical functions for the integral
double int_Lphi_phi (const double x, const int i, const int j);
double int_f_phi (const double x, const int i, const int j);

// Analitical solution for the problem
double u (const double x, const int i, const int j);

// Boundary condition function
double boundary_condition (const double x, const int i, const int j);

#endif