#include "solver.h"

#include <stdlib.h>

struct solver
{
	char* dimacs_filepath;
	solver_status status;
};


solver solver_create(cnf c, char* dimacs_filepath)
{
	solver s = malloc(sizeof(struct solver));

	s->dimacs_filepath = dimacs_filepath;
	s->status = NOT_READY;

	return s;
}

void solver_free(solver s)
{
	free(s);
}

void solver_run(solver s)
{

}

const char* get_dimacs_filepath(solver s)
{
	return s->dimacs_filepath;
}

solver_status get_solver_status(solver s)
{
	return s->status;
}
