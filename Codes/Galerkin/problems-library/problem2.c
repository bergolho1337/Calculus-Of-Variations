#include "problem2.h"

// Basis function
double phi (const double x, const int i, const int j)
{
    return pow(x,i+1);
}

// Linear operator apply over the basis function
double Lphi (const double x, const int i, const int j)
{
    return i*(i+1)*pow(x,i-1);
}

// Reaction term ...
double f (const double x, const int i, const int j)
{
    return 0.0f;
}

// Aproximation function for matrix integral
double Lphi_phi (const double x, const int i, const int j)
{
    return E*I*Lphi(x,i,0)*Lphi(x,j,0);
}

// Aproximation function for the RHS integral
double f_phi (const double x, const int i, const int j)
{
    return f(x,i,0)*phi(x,i,0);
}

// Analitical solution for the matrix integral
double int_Lphi_phi (const double x, const int i, const int j)
{
    return j * (j+1) * i * (i+1) * pow(L,i+j-1) / (i + j - 1);
    
}

// Analitical solution for the RHS integral
double int_f_phi (const double x, const int i, const int j)
{
    return 0.0f;
}

// Analitical solution of the problem
double u (const double x, const int i, const int j)
{
    return (M*x*x) / (2.0f*E*I); 
}

// Boundary condition function
double boundary_condition (const double x, const int i, const int j)
{
    return M * (i+1) * pow(L,i);
}