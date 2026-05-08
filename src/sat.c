/*
* MAXENCE TODO
*/

#include "sat.h"

#include <stdlib.h>

struct sat
{
	char* dimacs_filepath;
	sat_status status;
};


sat sat_create(cnf c, char* dimacs_filepath)
{
	sat s = malloc(sizeof(struct sat));

	s->dimacs_filepath = dimacs_filepath;
	s->status = NOT_READY;

	return s;
}

void sat_free(sat s)
{
	free(s);
}

void sat_run(sat s)
{

}

const char* get_dimacs_filepath(sat s)
{
	return s->dimacs_filepath;
}

sat_status get_sat_status(sat s)
{
	return s->status;
}
