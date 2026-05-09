#include "cnf.h"
#include "logger.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define CLAUSE_END 0

#define CHECK_CLAUSE_ENDED(c, ret)                            \
	if (c->nb_lits != 0 && get_last_lit(c) != CLAUSE_END)  \
	{                                                         \
		LOG_ERROR("CHECK_CLAUSE_ENDED FAILED!");              \
		return ret;                                           \
	}

#define CHECK_CLAUSE_NOT_ENDED(c, ret)                \
	if (get_last_lit(c) == CLAUSE_END)                \
	{                                                 \
		LOG_ERROR("CHECK_CLAUSE_NOT_ENDED FAILED!");  \
		return ret;                                   \
	}

struct cnf
{
	unsigned int nb_vars;
	unsigned int nb_lits;
	unsigned int nb_clauses;
	unsigned int clauses_size;

	lit* clauses;
};

const unsigned int default_clauses_size = 10;

cnf create_cnf()
{
	cnf c = malloc(sizeof(struct cnf));

	c->nb_vars = 0;
	c->nb_lits = 0;
	c->nb_clauses = 0;

	c->clauses_size = default_clauses_size;
	c->clauses = malloc(sizeof(lit) * c->clauses_size);
	
	return c;
}

cnf create_cnf_from_puzzle(puzzle p)
{
	cnf c = malloc(sizeof(struct cnf));

	c->nb_lits = 0;
	c->nb_vars = 0;
	c->clauses = NULL;
	
	return c;
}

void realloc_if_needed(cnf c, unsigned int size)
{
	if(c->clauses_size < c->nb_lits + size)
	{
		unsigned int new_size = c->clauses_size + default_clauses_size + size;

		void* ptr = realloc(c->clauses, new_size * sizeof(lit));

		if (ptr == NULL)
		{
			LOG_ERROR("MALLOC FAILED");
			return;
		}

		c->clauses = ptr;
		c->clauses_size = new_size;
	}
}

void cnf_set_nb_vars(cnf c, unsigned int nb_vars)
{
	c->nb_vars = nb_vars;
}

lit get_last_lit(cnf c)
{
	if (c->clauses_size == 0)
	{
		return CLAUSE_END;
	}

	return c->clauses[c->nb_lits - 1];
}

void add_clause(cnf c, lit* ls, unsigned int size)
{
	CHECK_CLAUSE_ENDED(c, );

	realloc_if_needed(c, size);

	for(unsigned int i = 0; i < size; i++)
	{
		c->clauses[c->nb_lits++] = ls[i];
	}

	c->clauses[c->nb_lits++] = CLAUSE_END;
}

void add_lit(cnf c, lit l)
{
	realloc_if_needed(c, 1);
	c->clauses[c->nb_lits++] = l;
}

void end_clause(cnf c)
{
	CHECK_CLAUSE_NOT_ENDED(c, );

	realloc_if_needed(c, 1);

	c->clauses[c->nb_lits++] = CLAUSE_END;
	++c->nb_clauses;
}

void atLeastOne(cnf c, lit* ls, unsigned int size)
{
	CHECK_CLAUSE_ENDED(c, );

	for (unsigned int i = 0; i < size; ++i)
	{
		add_lit(c, ls[i]);
	}

	end_clause(c);
}

void atMostOne(cnf c, lit* ls, unsigned int size)
{
	CHECK_CLAUSE_ENDED(c, );

	for (unsigned int i = 0; i < size; ++i)
	{
		for (unsigned int j = i + 1; j < size; ++j)
		{
			add_lit(c, -ls[i]);
			add_lit(c, -ls[j]);
			end_clause(c);
		}
	}
}

void exactlyOne(cnf c, lit* ls, unsigned int size)
{
	atLeastOne(c, ls, size);
	atMostOne(c, ls, size);
}

void print_cnf(cnf c)
{
	fprint_cnf(stdout, c);
}

void fprint_cnf(FILE* str, cnf c)
{
	fprintf(str, "p cnf %d %d\n", c->nb_vars, c->nb_clauses);

	for (unsigned int i = 0; i < c->nb_lits; i++)
	{
		lit l = c->clauses[i];

		fprintf(str, "%d", l);
		
		if(l == CLAUSE_END || i == c->nb_lits)
		{
			fprintf(str, "\n");
		}
		else 
		{
			fprintf(str, " ");
		}
	}
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
