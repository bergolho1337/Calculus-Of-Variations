#ifndef PROBLEM1_H
#define PROBLEM1_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Constants
const double L = 1.0f;
const double q0 = 1.0f;
const double A = 1.0f;
const double E = 1.0f;

// Aproximation functions
double phi (const double x, const int i, const int j);
double Lphi (const double x, const int i, const int j);
double f (const double x, const int i, const int j);
// Integral
double Lphi_phi (const double x, const int i, const int j);
double f_phi (const double x, const int i, const int j);

// Analitical functions
double int_Lphi_phi (const double x, const int i, const int j);
double int_f_phi (const double x, const int i, const int j);

double u (const double x, const int i, const int j);


#endif