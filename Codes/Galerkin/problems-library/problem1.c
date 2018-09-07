#include "problem1.h"

double phi (const double x, const int i, const int j)
{
    return sin(i*M_PI*x/L);
}

double Lphi (const double x, const int i, const int j)
{
    return -(pow(i*M_PI/L,2))*sin(i*M_PI*x/L);
}

double f (const double x, const int i, const int j)
{
    return q0/(A*E);
}

double Lphi_phi (const double x, const int i, const int j)
{
    return Lphi(x,i,0)*phi(x,j,0);
}

double f_phi (const double x, const int i, const int j)
{
    return f(x,i,0)*phi(x,i,0);
}

double int_Lphi_phi (const double x, const int i, const int j)
{
    if (i == j)
        return -(pow(i*M_PI/L,2))*(L/2);
    else
        return 0.0f;
}

double int_f_phi (const double x, const int i, const int j)
{
    if (i % 2 == 0)
        return 0.0f;
    else
        return -2.0f*(q0/(A*E))*(-L/(i*M_PI));
}

double u (const double x, const int i, const int j)
{
    return ( (q0*x*x)/(2.0f*A*E) ) - ( (q0*L*x)/(2.0f*A*E) ); 
}

double boundary_condition (const double x, const int i, const int j)
{
    return 0.0f;
}