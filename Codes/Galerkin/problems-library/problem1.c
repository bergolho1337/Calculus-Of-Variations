#include "problem1.h"

// Basis function
double phi (const double x, const int i, const int j)
{
    return sin(i*M_PI*x/L);
}

// Linear operator apply over the basis function
double Lphi (const double x, const int i, const int j)
{
    return -(pow(i*M_PI/L,2))*sin(i*M_PI*x/L);
}

// Reaction term ...
double f (const double x, const int i, const int j)
{
    return -q0/(A*E);
}

// Aproximation function for matrix integral
double Lphi_phi (const double x, const int i, const int j)
{
    return Lphi(x,i,0)*phi(x,j,0);
}

// Aproximation function for the RHS integral
double f_phi (const double x, const int i, const int j)
{
    return f(x,i,0)*phi(x,i,0);
}

// Analitical solution for the matrix integral
double int_Lphi_phi (const double x, const int i, const int j)
{
    if (i == j)
        return -(pow(i*M_PI/L,2))*(L/2);
    else
        return 0.0f;
}

// Analitical solution for the RHS integral
double int_f_phi (const double x, const int i, const int j)
{
    if (i % 2 == 0)
        return 0.0f;
    else
        return -2.0f*(-q0/(A*E))*(-L/(i*M_PI));
}

// Analitical solution of the problem
double u (const double x, const int i, const int j)
{
    return ( (-q0*x*x)/(2.0f*A*E) ) + ( (q0*L*x)/(2.0f*A*E) ); 
}

// Boundary condition function
double boundary_condition (const double x, const int i, const int j)
{
    return 0.0f;
}