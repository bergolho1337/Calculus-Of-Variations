#include "newton-cotes-solver.h"

double Trapezium (const double a, const double b, set_aprox_fn *f, const int n)
{
    //fprintf(stdout,"[Newton-Cotes] a = %.10lf || b = %.10lf\n",a,b);

    // Calculate size of the subintervals of integral
    double h = (b-a) / NSUBINTERVAL;

    // Compute the integral following the rule ...
    double total_int = (f(a,n) + f(b,n)) / 2.0;
    for (int i = 1; i < NSUBINTERVAL-1; i++)
    {
        double x = a + i*h;
        total_int += f(x,n);
    }
    total_int *= h;

    //fprintf(stdout,"\tIntegral = %.10lf\n",total_int);
    return total_int;
}

double Simpson13 (const double a, const double b, set_aprox_fn *f, const int n)
{
    //fprintf(stdout,"[Newton-Cotes] a = %.10lf || b = %.10lf\n",a,b);

    // Calculate size of the subintervals
    double h = (b-a) / NSUBINTERVAL;

    // Compute the integral following the rule ...
    double total_int = (f(a,n) + f(b,n));
    for (int i = 1; i < NSUBINTERVAL-1; i++)
    {
        double x = a + i*h;
        if (i % 2 == 0)
            total_int += 2.0 * f(x,n);
        else
            total_int += 4.0 * f(x,n);
    }
    total_int *= (h / 3.0);

    //fprintf(stdout,"\tIntegral = %.10lf\n",total_int);
    return total_int;
}

double Simpson38 (const double a, const double b, set_aprox_fn *f, const int n)
{
    //fprintf(stdout,"[Newton-Cotes] a = %.10lf || b = %.10lf\n",a,b);

    // Calculate size of the subintervals
    double h = (b-a) / NSUBINTERVAL;

    // Compute the integral following the rule ...
    double total_int = (f(a,n) + f(b,n));
    for (int i = 1; i < NSUBINTERVAL-1; i++)
    {
        double x = a + i*h;
        if (i % 3 == 0)
            total_int += 2.0 * f(x,n);
        else
            total_int += 3.0 * f(x,n);
    }
    total_int *= (3.0 * h / 8.0);

    //fprintf(stdout,"\tIntegral = %.10lf\n",total_int);
    return total_int;
}