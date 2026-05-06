#include "cnf.h"

#include <stdlib.h>

struct cnf
{
	unsigned int nb_clauses;
	unsigned int nb_vars;
	unsigned int* clauses;
};

cnf create_cnf(puzzle p)
{
	cnf c = malloc(sizeof(struct cnf));

	c->nb_clauses = 0;
	c->nb_vars = 0;
	c->clauses = NULL;
	
	return c;
}

void free_cnf(cnf c)
{
	if(c == NULL)
	{
		return;
	}

	if(c->clauses != NULL)
	{
		free(c->clauses);
	}

	free(c);
}
