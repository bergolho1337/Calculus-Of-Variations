#ifndef NEWTON_COTES_H
#define NEWTON_COTES_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <dlfcn.h>

#include "problem.h"

// Flag to allow a function export ...
#define EXPORT_FN

#define NEWTON_COTES_RULE 0
// 0 = Trapezium
// 1 = 1/3 Simpson
// 2 = 3/8 Simpson

// Function pointer
#define SET_NEWTON_COTES(name) EXPORT_FN double name(const double a, const double b,\
                                                    set_analit_fn *f,\
                                                    const int i, const int j)
typedef SET_NEWTON_COTES(set_newton_cotes_fn);

struct newton_cotes_data
{
    void *handle;                   // Handle to the library that integrate the points
    char *integral_rule_name;       // Name of the integral rule 
    set_newton_cotes_fn *function;  // Pointer to the Newton-Cotes function
};

struct newton_cotes_data* new_newton_cotes_data ();
void free_newton_cotes_data (struct newton_cotes_data *n);
char* get_rule_name ();
set_newton_cotes_fn* get_rule_function (void *handle, const char rule_name[]);


#endif