#ifndef SOLVER_H
#define SOLVER_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#include "linear-system.h"

struct solver_data
{
    uint32_t nbasis;
    uint32_t problem_id;
    uint32_t linear_system_id;
    uint16_t analitical_integral;

    double *K;
    double *F;
    double *c;

    struct linear_system_data *linear_system_solver;
    //struct newton_cotes_data *newton_cotes_solver;
    //struct problem_data *problem;

};

struct solver_data* new_solver_data (int argc, char *argv[]);
void free_solver_data (struct solver_data *s);

void build_matrix (struct solver_data *s);
void build_rhs (struct solver_data *s);
void print_matrix (struct solver_data *s);
void print_rhs (struct solver_data *s);

void evaluate (struct solver_data *s);

void Usage (int argc, char *argv[]);

#endif