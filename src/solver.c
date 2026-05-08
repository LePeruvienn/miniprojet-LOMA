#include "solver.h"
#include "logger.h"

struct solver
{
	cnf c;

	unsigned int global_width;
	unsigned int global_height;

	unsigned int width;
	unsigned int height;
};

/*
var get_var_from_letter_pos(solver s, letter l, unsigned int x, unsigned int y)
{
	if (x > s->width || y > s->height)
	{
		LOG_ERROR("Les valeurs de x ou y sont trop grande !");
		return 0;
	}

	unsigned int let_offset = (l * s->width * s->height) + 1; // +1 cause lit 0 is CLAUSE_END
	unsigned int pos_offset = (y * s->height) + x;

	return let_offset + pos_offset;
}
*/

/*
letter_pos get_letter_pos_from_var(solver s, var v)
{
	// NOTE: First we are using a 1 first index based system for our modulo (%) computations

	unsigned int pos_buf_size = s->width * s->height; // The position "buffer" size for each letter
	unsigned int pos = pos_buf_size - (v % (pos_buf_size)) // With 1 the first case, and 9 the last

	unsigned int x = s->height - (pos % s->height);

	unsigned int let_offset = (l * s->width * s->height) + 1; // +1 cause lit 0 is CLAUSE_END
	unsigned int pos_offset = (y * s->height) + x;

	return let_offset + pos_offset;
}
*/
