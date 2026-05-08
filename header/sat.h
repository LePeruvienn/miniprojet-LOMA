/*
* MAXENCE TODO
*/

#ifndef sat_H
#define sat_H

#include "cnf.h"

typedef struct sat* sat;

typedef enum
{
	NOT_READY, READY,
	ERROR, FILE_ERROR,
	SAT, UNSAT

} sat_status;

sat sat_create(cnf c, char* dimacs_filepath);
void sat_free(sat s);

void sat_run(sat s);

const char* get_dimacs_filepath(sat s);
sat_status get_sat_status(sat s);

#endif // sat_H
