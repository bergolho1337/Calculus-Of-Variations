#include "problem1.h"

double phi (const double x, const int n)
{
    return sin(n*M_PI*x/L);
}

double Lphi (const double x, const int n)
{
    return -(pow(n*M_PI/L,2))*sin(n*M_PI*x/L);
}

double f (const double x, const int n)
{
    return q0/(A*E);
}

double int_Lphi_phi (const double x, const int i, const int j)
{
    return -(pow(j*M_PI/L,2))*(L/2);
}

double int_f_phi (const double x, const int i, const int j)
{
    if (i % 2 == 0)
        return 0.0f;
    else
        return -2.0f*(q0/(A*E))*(-L/(i*M_PI));
}