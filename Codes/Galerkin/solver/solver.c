#include "solver.h"

void Usage (int argc, char *argv[])
{
    fprintf(stderr,"-----------------------------------------------------------------------\n");
    fprintf(stderr,"Usage:> ./bin/galerkin <problem_id> <linear_system_id> <aprox_integral> <nbasis>\n");
    fprintf(stderr,"-----------------------------------------------------------------------\n");
    fprintf(stderr,"<problem_id> = Problem identifier\n");
    fprintf(stderr,"-----------------------------------------------------------------------\n");
    fprintf(stderr,"<linear_system_id> = Linear System identifier\n");
    fprintf(stderr,"\t0 = Jacobi\n");
    fprintf(stderr,"\t1 = Gauss-Seidel\n");
    fprintf(stderr,"\t2 = BiCG\n");
    fprintf(stderr,"-----------------------------------------------------------------------\n");
    fprintf(stderr,"<aprox_integral> = Approximate integral ?\n");
    fprintf(stderr,"\t0 = Analitical\n");
    fprintf(stderr,"\t1 = Approximate using Newton-Cotes\n");
    fprintf(stderr,"-----------------------------------------------------------------------\n");
    fprintf(stderr,"<nbasis> = Number of basis functions to use in the Galerkin method\n");
    fprintf(stderr,"-----------------------------------------------------------------------\n");  
}

struct solver_data* new_solver_data (int argc, char *argv[])
{
    struct solver_data *s = (struct solver_data*)malloc(sizeof(struct solver_data));

    s->problem_id = atoi(argv[1]);
    s->linear_system_id = atoi(argv[2]);
    s->analitical_integral = atoi(argv[3]);
    s->nbasis = atoi(argv[4]);

    s->linear_system_solver = new_linear_system(s->linear_system_id);


    return s;
}

void free_solver_data (struct solver_data *s)
{
    assert(s);

    if (s->linear_system_solver)
        free_linear_system(s->linear_system_solver);
    
    free(s);
}

/*
Solver::Solver (int argc, char *argv[])
{
    nbasis = atoi(argv[1]);
    problem_id = atoi(argv[2]);

    // Allocate memory for the linear system
    K = new double[nbasis*nbasis];
    F = new double[nbasis];
    c = new double[nbasis];

    build_matrix();
    print_matrix();

}

Solver::~Solver ()
{
    cout << "[!] Cleaning Solver ..." << endl;
    delete [] K;
    delete [] F;
    delete [] c;
}

void Solver::build_matrix ()
{
    assert(K);

    double a = 0.0f;
    double b = 1.0f;

    for (int i = 0; i < nbasis; i++)
    {
        for (int j = 0; j < nbasis; j++)
        {
            K[i*nbasis+j] = Lphi_phi(a,b,i+1,j+1);
        }
    }
}

void Solver::solve ()
{
    cout << "[!] Solving problem ..." << endl;
}

void Solver::print_matrix ()
{
    assert(K);

    for (int i = 0; i < nbasis; i++)
    {
        for (int j = 0; j < nbasis; j++)
        {
            cout << fixed << setprecision(5) << K[i*nbasis+j] << " ";
        }
        cout << endl;
    }    
}

double Lphi_phi (const double a, const double b, const int i, const int j)
{
    if (i == j)
        return -pow(M_PI*j/b,2) * ((a+b)/2.0f);
    else
        return 0.0f;
}
*/