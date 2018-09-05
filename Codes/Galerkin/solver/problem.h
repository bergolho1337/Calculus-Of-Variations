#ifndef PROBLEM_H
#define PROBLEM_H

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

static const int NAPROX = 3;
static const int NANALIT = 3;

// Flag to allow a function export ...
#define EXPORT_FN

// This works like a function pointer macro ...
#define SET_APROX_TYPE(name) EXPORT_FN double name(const double x, const int n)
typedef SET_APROX_TYPE(set_aprox_fn);

#define SET_ANALIT_TYPE(name) EXPORT_FN double name(const double x, const int i, const int j)
typedef SET_ANALIT_TYPE(set_analit_fn);

struct problem_data
{
    void *handle;                   // Handle to the library that stores the equations of the problem
    char *problem_name;             // Problem name
    char *library_path;             // Path to the library
    unsigned int neq;               // Number of equations of the problem
    set_analit_fn **aprox;           // Array of pointers to the aproximation functions of the problem
    // aprox[0] = Lphi_phi
    // aprox[1] = f_phi
    // aprox[2] = phi
    set_analit_fn **analit;         // Array of pointers to the analitical functions of the problem
    // analit[0] = int_Lphi_phi
    // analit[1] = int_f_phi
    // analit[2] = u
};

// Constructor and destructor
struct problem_data* new_problem (const int problem_id, const int analitical_integral);
void free_problem (struct problem_data *p);

// Auxiliary functions
char* getProblemName (const int problem_id);
char* getLibraryPath (const int problem_id);
int getNumberEquations (const char *library_path);
set_analit_fn** getAproxFunctions (void *handle, const char *library_path);
set_analit_fn** getAnaliticalFunctions (void *handle, const char *library_path);

#endif