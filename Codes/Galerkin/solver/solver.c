#include "solver.h"

void Usage (int argc, char *argv[])
{
    fprintf(stderr,"-----------------------------------------------------------------------\n");
    fprintf(stderr,"Usage:> ./bin/galerkin <problem_id> <linear_system_id> <aprox_integral> <nbasis>\n");
    fprintf(stderr,"-----------------------------------------------------------------------\n");
    fprintf(stderr,"<problem_id> = Problem identifier\n");
    fprintf(stderr,"\t1 = Problem 1\n");
    fprintf(stderr,"\t2 = Problem 2\n");
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
    fprintf(stderr,"Example:\n");
    fprintf(stderr,"1) Solving Problem 1 with Gauss-Seidel, no aproximation for the integrals and 5 basis functions\n");
    fprintf(stderr,"\t./bin/galerkin 1 1 0 5\n");
    fprintf(stderr,"2) Solving Problem 2 with BiCG, aproximating the integrals using Newton-Cotes and 3 basis functions\n");
    fprintf(stderr,"\t./bin/galerkin 2 2 1 3\n");
}

struct solver_data* new_solver_data (int argc, char *argv[])
{
    struct solver_data *s = (struct solver_data*)malloc(sizeof(struct solver_data));

    // Parse the input form user
    s->problem_id = atoi(argv[1]);
    s->linear_system_id = atoi(argv[2]);
    s->analitical_integral = atoi(argv[3]);
    s->nbasis = atoi(argv[4]);

    // Initialize the structures for solving the problem
    s->linear_system_solver = new_linear_system(s->linear_system_id);
    s->problem = new_problem(s->problem_id,s->analitical_integral);
    if (s->analitical_integral)
        s->newton_cotes = new_newton_cotes_data();

    // Build the linear system related to the Galerkin method
    s->linear_system_solver->A = build_matrix(s);
    //print_matrix(s);

    s->linear_system_solver->b = build_rhs(s);
    //print_rhs(s);

    return s;
}

void free_solver_data (struct solver_data *s)
{
    assert(s);

    if (s->linear_system_solver)
        free_linear_system(s->linear_system_solver);

    if (s->problem)
        free_problem(s->problem);

    if (s->newton_cotes)
        free_newton_cotes_data(s->newton_cotes);
    
    free(s);
}

double* build_matrix (struct solver_data *s)
{
    assert(s);

    uint32_t nbasis = s->nbasis;
    double a = 0.0f;
    double b = 1.0f;    // TO DO: get this value from the problem library
    double *K;

    // Allocate memory
    K = (double*)malloc(sizeof(double)*nbasis*nbasis);

    if (!s->analitical_integral)
    {
        set_analit_fn **analit = s->problem->analit;

        for (int i = 0; i < nbasis; i++)
        {
            for (int j = 0; j < nbasis; j++)
            {
                // Lphi_phi
                K[i*nbasis+j] = analit[0](0.0f,i+1,j+1);
            }
        }
    }
    else
    {
        set_analit_fn **aprox = s->problem->aprox;
        struct newton_cotes_data *newton = s->newton_cotes;

        for (int i = 0; i < nbasis; i++)
        {
            for (int j = 0; j < nbasis; j++)
            {
                // Lphi_phi
                K[i*nbasis+j] = newton->function(a,b,aprox[0],i+1,j+1);
            }
        }
    }

    return K;
}

double* build_rhs (struct solver_data *s)
{
    assert(s);

    uint32_t nbasis = s->nbasis;
    double *F;
    double a = 0.0f;
    double b = 1.0f;    // TO DO: get this value from the problem library
    
    // Allocate memory
    F = (double*)malloc(sizeof(double)*nbasis);

    if (!s->analitical_integral)
    {
        fprintf(stdout,"\n[Problem] Using ANALITICAL form of the integrals for the linear system\n");

        set_analit_fn **analit = s->problem->analit;
        set_analit_fn *boundary = s->problem->boundary_condition;

        for (int i = 0; i < nbasis; i++)
        {
            // f_phi
            F[i] = analit[1](0.0f,i+1,i+1) + boundary(0.0f,i+1,i+1);
        }
    }
    else
    {
        fprintf(stdout,"\n[Problem] Using APROXIMATIONS to calculate the integrals from the linear system\n");

        set_analit_fn **aprox = s->problem->aprox;
        set_analit_fn *boundary = s->problem->boundary_condition;
        struct newton_cotes_data *newton = s->newton_cotes;


        for (int i = 0; i < nbasis; i++)
        {
            // f_phi
            F[i] = newton->function(a,b,aprox[1],i+1,i+1) + boundary(0.0f,i+1,i+1);
        }
    }

    return F;
}

void solve_linear_system (struct solver_data *s)
{
    assert(s);

    uint32_t nbasis = s->nbasis;
    // Allocate memory for the solution array
    s->linear_system_solver->x = (double*)malloc(sizeof(double)*nbasis);

    double *K = s->linear_system_solver->A;
    double *F = s->linear_system_solver->b;
    double *c = s->linear_system_solver->x;

    s->linear_system_solver->solver(K,F,nbasis,c);

    //for (int i = 0; i < nbasis; i++)
    //    printf("%.10lf\n",c[i]);

}

void evaluate (struct solver_data *s)
{
    assert(s);

    FILE *file = fopen("./scripts/solution.dat","w+");
    uint32_t nbasis = s->nbasis;
    double a = 0.0f;
    double b = 1.0f;    // TO DO: get this value from the problem library
    double h = (b-a) / NEVAL;
    double *c = s->linear_system_solver->x;
    set_analit_fn **analit = s->problem->analit;
    set_analit_fn **aprox = s->problem->aprox;
    
    fprintf(file,"%d\n",NEVAL);

    for (int i = 0; i < NEVAL+1; i++)
    {
        double x = a + i*h;
        double value = 0.0f;
        for (int j = 0; j < nbasis; j++)
            value += c[j] * aprox[2](x,j+1,0);
        fprintf(file,"%.10lf %.10lf %.10lf\n",x,analit[2](x,0,0),value);
    }

    fclose(file);

}

void print_matrix (struct solver_data *s)
{
    assert(s);

    uint32_t nbasis = s->nbasis;
    double *K = s->linear_system_solver->A;    

    for (int i = 0; i < nbasis; i++)
    {
        for (int j = 0; j < nbasis; j++)
            fprintf(stdout,"%.10lf ",K[i*nbasis+j]);
        fprintf(stdout,"\n");
    }
}

void print_rhs (struct solver_data *s)
{
    assert(s);

    uint32_t nbasis = s->nbasis;
    double *F = s->linear_system_solver->b;    

    for (int i = 0; i < nbasis; i++)
    {
        fprintf(stdout,"%.10lf\n",F[i]);
    }
}