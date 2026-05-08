#include "cnf.h"
#include "logger.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define CLAUSE_END 0

#define CHECK_CLAUSE_ENDED(c, ret)                \
	if (c->nb_clauses != 0 && get_last_lit(c) == CLAUSE_END)            \
	{                                             \
		LOG_ERROR("CHECK_CLAUSE_ENDED FAILED!");  \
		return ret;                               \
	}

#define CHECK_CLAUSE_NOT_ENDED(c, ret)            \
	if (get_last_lit(c) != CLAUSE_END)            \
	{                                             \
		LOG_ERROR("CHECK_CLAUSE_NOT_ENDED FAILED!");  \
		return ret;                               \
	}

struct cnf
{
	unsigned int nb_vars;
	unsigned int nb_clauses;
	unsigned int clauses_size;

	lit* clauses;
};

const unsigned int default_clauses_size = 10;

cnf create_cnf()
{
	cnf c = malloc(sizeof(struct cnf));

	c->nb_vars = 0;
	c->nb_clauses = 0;

	c->clauses_size = default_clauses_size;
	c->clauses = malloc(sizeof(lit) * c->clauses_size);
	
	return c;
}

cnf create_cnf_from_puzzle(puzzle p)
{
	cnf c = malloc(sizeof(struct cnf));

	c->nb_clauses = 0;
	c->nb_vars = 0;
	c->clauses = NULL;
	
	return c;
}

void realloc_if_needed(cnf c, unsigned int size)
{
	if(c->clauses_size < c->nb_clauses + size)
	{
		void* ptr = realloc(c->clauses, (c->clauses_size + default_clauses_size + size) * sizeof(lit));

		if (ptr == NULL)
		{
			return;
		}

		c->clauses = ptr;
	}
}

lit get_last_lit(cnf c)
{
	if (c->clauses_size == 0)
	{
		return CLAUSE_END;
	}

	return c->clauses[c->clauses_size - 1];
}

void add_clause(cnf c, lit* ls, unsigned int size)
{
	CHECK_CLAUSE_ENDED(c, );

	realloc_if_needed(c, size);

	for(unsigned int i = 0; i < size; i++)
	{
		c->clauses[c->nb_clauses++] = ls[i];
	}

	c->clauses[c->nb_clauses++] = CLAUSE_END;
}

void add_lit(cnf c, lit l)
{
	CHECK_CLAUSE_ENDED(c, );

	realloc_if_needed(c, 1);
	c->clauses[c->nb_clauses++] = l;
}

void end_clause(cnf c)
{
	CHECK_CLAUSE_NOT_ENDED(c, );

	realloc_if_needed(c, 1);

	c->clauses[c->nb_clauses++] = CLAUSE_END;
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

void print_lit(lit l)
{
	if (l < 0)
	{
		printf("-");
	}

	printf("%d", l);
}

void print_cnf(cnf c)
{
	printf("cnf %d %d\n", c->nb_vars, c->nb_clauses);

	for (unsigned int i = 0; i < c->nb_clauses; i++)
	{
		lit l = c->clauses[i];

		print_lit(l);
		
		if(l == CLAUSE_END || i == c->nb_clauses)
		{
			printf("\n");
		}
		else 
		{
			printf(" ");
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
