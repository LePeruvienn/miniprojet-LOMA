#include "puzzle.h"
#include "cnf.h"

#include <stdlib.h>

#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define MAX(i, j) (((i) > (j)) ? (i) : (j))

const unsigned int global_width  = 5;
const unsigned int global_height = 5;

const unsigned int width = global_width - 2;
const unsigned int height = global_height - 2;

const unsigned int max_letter_amount = MAX(width, height);
const unsigned int lit_amount = max_letter_amount * width * height;

letter data[] = {
	_, A, _, _, _,
	_, 0, 0, 0, _,
	_, 0, 0, 0, B,
	_, 0, 0, 0, _,
	_, _, _, _, _,
};

var get_var_from_letter_pos(letter l, unsigned int x, unsigned int y)
{
	unsigned int let_offset = (l * width * height) + 1; // +1 cause lit 0 is CLAUSE_END
	unsigned int pos_offset = (y * height) + x;

	return let_offset + pos_offset;
}

int main()
{

	cnf c = create_cnf();
	
	lit* rows_lits = malloc(sizeof(lit) * width);
	lit* cols_lits = malloc(sizeof(lit) * height);

	for (letter l = EMPTY + 1; l < max_letter_amount; ++l)
	{
		// AtLeastOne[ L(0,1), L(0,2), L(i,j) ]

		// Pour toutes les ligne de du puzzle
		for (unsigned int y = 0; y < height; ++y)
		{
			for (unsigned int x = 0; x < width; ++x)
			{
				rows_lits[x] = get_var_from_letter_pos(l, x, y);
			}
			
			atLeastOne(c, rows_lits, width);
		}

		// Pour toutes les collonne de du puzzle
		for (unsigned int x = 0; x < width; ++x)
		{
			for (unsigned int y = 0; y < height; ++y)
			{
				cols_lits[y] = get_var_from_letter_pos(l, x, y);
			}

			atLeastOne(c, cols_lits, height);
		}
	}

	free(rows_lits);
	free(cols_lits);

	print_cnf(c);

	return 0;
}
