#include "newton-cotes-solver.h"

double Trapezium (const double a, const double b, set_analit_fn *f, const int i, const int j)
{
    //fprintf(stdout,"[Newton-Cotes] a = %.10lf || b = %.10lf\n",a,b);

    // Calculate size of the subintervals of integral
    double h = (b-a) / NSUBINTERVAL;

    // Compute the integral following the rule ...
    double total_int = (f(a,i,j) + f(b,i,j)) / 2.0;
    for (int k = 1; k < NSUBINTERVAL-1; k++)
    {
        double x = a + k*h;
        total_int += f(x,i,j);
    }
    total_int *= h;

    //fprintf(stdout,"\tIntegral = %.10lf\n",total_int);
    return total_int;
}

double Simpson13 (const double a, const double b, set_analit_fn *f, const int i, const int j)
{
    //fprintf(stdout,"[Newton-Cotes] a = %.10lf || b = %.10lf\n",a,b);

    // Calculate size of the subintervals
    double h = (b-a) / NSUBINTERVAL;

    // Compute the integral following the rule ...
    double total_int = (f(a,i,j) + f(b,i,j));
    for (int k = 1; k < NSUBINTERVAL-1; k++)
    {
        double x = a + k*h;
        if (i % 2 == 0)
            total_int += 2.0 * f(x,i,j);
        else
            total_int += 4.0 * f(x,i,j);
    }
    total_int *= (h / 3.0);

    //fprintf(stdout,"\tIntegral = %.10lf\n",total_int);
    return total_int;
}

double Simpson38 (const double a, const double b, set_analit_fn *f, const int i, const int j)
{
    //fprintf(stdout,"[Newton-Cotes] a = %.10lf || b = %.10lf\n",a,b);

    // Calculate size of the subintervals
    double h = (b-a) / NSUBINTERVAL;

    // Compute the integral following the rule ...
    double total_int = (f(a,i,j) + f(b,i,j));
    for (int k = 1; k < NSUBINTERVAL-1; k++)
    {
        double x = a + i*h;
        if (i % 3 == 0)
            total_int += 2.0 * f(x,i,j);
        else
            total_int += 3.0 * f(x,i,j);
    }
    total_int *= (3.0 * h / 8.0);

    //fprintf(stdout,"\tIntegral = %.10lf\n",total_int);
    return total_int;
}