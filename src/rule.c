#include "rule.h"
#include "cnf.h"
#include "letter.h"
#include "letter_pos.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct coord_xy
{
	unsigned int x;
	unsigned int y;

} coord_xy;

void make_rule_one_letter_per_row_column(cnf c, unsigned int puzzle_size, unsigned int letter_amount)
{
	lit* lits_rows_tmp = malloc(sizeof(lit) * puzzle_size);
	lit* lits_cols_tmp = malloc(sizeof(lit) * puzzle_size);

	// 1. EXACTEMENT UNE SEUL LETTER LIGNE PAR COLONNE ET LIGNE !
	for (letter l = 1; l <= letter_amount; ++l)  // On commence à 1 car 0 == EMPTY on ne veut pas que des cases soit vide!
	{
		// Dans chaque ligne et coll
		for (int i = 0; i < puzzle_size; ++i)
		{
			for (int j = 0; j < puzzle_size; ++j)
			{
				var v_row = get_var_from_letter_pos(l, j, i, puzzle_size);
				var v_col = get_var_from_letter_pos(l, i, j, puzzle_size);

				lits_rows_tmp[j] = v_row;
				lits_cols_tmp[j] = v_col;
			}

			exactlyOne(c, lits_rows_tmp, puzzle_size);
			exactlyOne(c, lits_cols_tmp, puzzle_size);
		}
	}

	free(lits_cols_tmp);
	free(lits_rows_tmp);
}


void make_rule_unique_letter_per_case(cnf c, unsigned int puzzle_size, unsigned int letter_amount)
{
	letter start_letter = (puzzle_size - letter_amount == 0) ? 1 : 0; // 0 == EMPTY
	unsigned int lits_case_size = letter_amount - start_letter + 1;
	lit* lits_case_tmp = malloc(sizeof(lit) * lits_case_size);

	for (unsigned int i = 0; i < puzzle_size; ++i)
	{
		for (unsigned int j = 0; j < puzzle_size; ++j)
		{
			for (letter let = start_letter; let <= letter_amount; ++let)
			{
				lit li = get_var_from_letter_pos(let, i, j, puzzle_size);
				lits_case_tmp[let - start_letter] = li;
			}

			exactlyOne(c, lits_case_tmp, lits_case_size);
		}
	}

	free(lits_case_tmp);
}


void make_rule_letter_borders(cnf c, unsigned int puzzle_size, unsigned int letter_amount, puzzle p)
{
	unsigned int empty_space_size = puzzle_size - letter_amount;
	bool have_empty = empty_space_size > 0;

	for (edge e = 0; e < 4; ++e) // de 0 à 4 car il y a 4 edges
	{
		char* border = get_bord(p, e);

		for (unsigned int i = 0; i < puzzle_size; ++i)
		{
			letter l = get_letter(border[i]);
		
			if (l == EMPTY) continue;

			if (have_empty)
			{
				make_rule_letter_border_with_empty(c, puzzle_size, empty_space_size, l, e, i);
			}
			else
			{
				make_rule_letter_border_no_empty(c, puzzle_size, l, e, i);
			}
		}
	}
}

coord_xy edge_to_xy(edge e, unsigned int puzzle_size, unsigned int edge_index, unsigned int offset)
{
	unsigned int x, y;

	switch (e)
	{
		case TOP:
			x = edge_index;
			y = 0 + offset;
			break;

		case BOTTOM:
			x = edge_index;
			y = puzzle_size - offset - 1;
			break;

		case LEFT:
			x = 0 + offset;
			y = edge_index;
			break;

		case RIGHT:
			x = puzzle_size - offset - 1;
			y = edge_index;
			break;
	}

	return (coord_xy) {x, y};
}

void make_rule_letter_border_no_empty(cnf c, unsigned int puzzle_size, letter l, edge e, unsigned int edge_index)
{
	coord_xy pos = edge_to_xy(e, puzzle_size, edge_index, 0);

	var v = get_var_from_letter_pos(l, pos.x, pos.y, puzzle_size);

	add_lit(c, v);
	end_clause(c);
}

void make_rule_letter_border_with_empty(cnf c, unsigned int puzzle_size, unsigned int empty_space_size, letter l, edge e, unsigned int edge_index)
{
	for (unsigned int i = 0; i <= empty_space_size; ++i)
	{
		for (unsigned j = 0; j < i; ++j)
		{
			coord_xy prev_pos = edge_to_xy(e, puzzle_size, edge_index, j);

			var v = get_var_from_letter_pos(EMPTY, prev_pos.x, prev_pos.y, puzzle_size);
			add_lit(c, - (lit) v);
		}

		coord_xy cur_pos = edge_to_xy(e, puzzle_size, edge_index, i);

		var var_empty_pos = get_var_from_letter_pos(EMPTY, cur_pos.x, cur_pos.y, puzzle_size);
		var var_letter_pos = get_var_from_letter_pos(l, cur_pos.x, cur_pos.y, puzzle_size);

		add_lit(c, var_empty_pos);
		add_lit(c, var_letter_pos);

		end_clause(c);
	}
}

void make_rule_preplaced_letters(cnf c, unsigned int puzzle_size, unsigned int letter_amount, puzzle p)
{
	char** puzzle_content = get_grille(p);

	for (unsigned int i = 0; i < puzzle_size; ++i)
	{
		for (unsigned int j = 0; j < puzzle_size; ++j)
		{
			letter l = get_letter(puzzle_content[j][i]); // Flipped i & j cause else it dont work 

			if (l == EMPTY) continue;

			var v = get_var_from_letter_pos(l, i, j, puzzle_size);
			add_lit(c, v);
			end_clause(c);
		}
	}
}

void make_rule_deny_solution(cnf c, var* solution, unsigned int size)
{
	for (unsigned i = 0; i < size; ++i)
	{
		var v = solution[i];
		lit l = - (lit) v;

		add_lit(c, l);
	}
	end_clause(c);
}
