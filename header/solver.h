#ifndef SOLVER_H
#define SOLVER_H

#include "cnf.h"

typedef struct solver* solver;

typedef enum
{
	NOT_READY, READY,
	ERROR, FILE_ERROR,
	SAT, UNSAT

} solver_status;

solver solver_create(cnf c, char* dimacs_filepath);
void solver_free(solver s);

void solver_run(solver s);

const char* get_dimacs_filepath(solver s);
solver_status get_solver_status(solver s);

#endif // SOLVER_H
