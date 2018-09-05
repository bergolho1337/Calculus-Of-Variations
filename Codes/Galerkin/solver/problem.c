#include "problem.h"

struct problem_data* new_problem (const int problem_id, const int analitical_integral)
{
    struct problem_data *p = (struct problem_data*)malloc(sizeof(struct problem_data));

    p->problem_name = getProblemName(problem_id);
    p->library_path = getLibraryPath(problem_id);

    p->aprox = getAproxFunctions(p->handle,p->library_path);
    p->analit = getAnaliticalFunctions(p->handle,p->library_path);
    
    /*
    if (analitical_integral == 0)
        p->aprox = getAproxFunctions(p->handle,p->library_path);
    else
        p->analit = getAnaliticalFunctions(p->handle,p->library_path);
    */

    fprintf(stdout,"[Problem] Solving '%s'\n",p->problem_name);

    return p;

}

void free_problem (struct problem_data *p)
{
    if (p->handle)
        dlclose(p->handle);

    if (p->aprox)
        free(p->aprox);

    if (p->analit)
        free(p->analit);
    
    free(p);
}

char* getProblemName (const int problem_id)
{
    switch (problem_id)
    {
        case 1: return "problem1";
        case 2: return "problem2";
    }
    fprintf(stderr,"[-] ERROR! Problem identifier not found !\n");
    return NULL;
}

char* getLibraryPath (const int problem_id)
{
    switch (problem_id)
    {
        case 1: return "./shared-libs/libproblem1.so";
        case 2: return "./shared-libs/libproblem2.so";
    }
    fprintf(stderr,"[-] ERROR! Problem identifier not found !\n");
    return NULL;
}

set_analit_fn** getAproxFunctions (void *handle, const char *library_path)
{
    fprintf(stdout,"\n[Problem] Using APROXIMATIONS to calculate the integrals from the linear system\n");

    set_analit_fn **aprox = (set_analit_fn**)malloc(sizeof(set_analit_fn*)*NAPROX);

    handle = dlopen(library_path,RTLD_LAZY);
    if (!handle) 
    {
        fprintf(stderr,"%s\n",dlerror());
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(stdout,"\n[+] Problem library \"%s\" open with sucess\n",library_path);
    }
    
    aprox[0] = dlsym(handle,"Lphi_phi");
    if (dlerror() != NULL)  
    {
        fprintf(stderr, "\n'Lphi_phi' function not found in the provided problem library\n");
        exit(EXIT_FAILURE);
    }
    aprox[1] = dlsym(handle,"f_phi");
    if (dlerror() != NULL)  
    {
        fprintf(stderr, "\n'f_phi' function not found in the provided problem library\n");
        exit(EXIT_FAILURE);
    }
    aprox[2] = dlsym(handle,"phi");
    if (dlerror() != NULL)  
    {
        fprintf(stderr, "\n'phi' function not found in the provided problem library\n");
        exit(EXIT_FAILURE);
    }

    return aprox;
}

set_analit_fn** getAnaliticalFunctions (void *handle, const char *library_path)
{
    fprintf(stdout,"\n[Problem] Using ANALITICAL form of the integrals for the linear system\n");

    set_analit_fn **analit = (set_analit_fn**)malloc(sizeof(set_analit_fn*)*NANALIT);

    handle = dlopen(library_path,RTLD_LAZY);
    if (!handle) 
    {
        fprintf(stderr,"%s\n",dlerror());
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(stdout,"\n[+] Problem library \"%s\" open with sucess\n",library_path);
    }
    
    analit[0] = dlsym(handle,"int_Lphi_phi");
    if (dlerror() != NULL)  
    {
        fprintf(stderr, "\n'int_Lphi_phi' function not found in the provided problem library\n");
        exit(EXIT_FAILURE);
    }
    analit[1] = dlsym(handle,"int_f_phi");
    if (dlerror() != NULL)  
    {
        fprintf(stderr, "\n'int_f_phi' function not found in the provided problem library\n");
        exit(EXIT_FAILURE);
    }
    analit[2] = dlsym(handle,"u");
    if (dlerror() != NULL)  
    {
        fprintf(stderr, "\n'u' function not found in the provided problem library\n");
        exit(EXIT_FAILURE);
    }

    return analit;
}