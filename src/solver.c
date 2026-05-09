#include "solver.h"
#include "logger.h"
#include "puzzle.h"
#include "cnf.h"
#include "letter_pos.h"

#include <stdlib.h>
#include <stdio.h>

struct solver
{
	cnf c;
	puzzle p;
};

solver create_solver(puzzle p)
{
	if (p == NULL)
	{
		LOG_ERROR("Puzzle is null !");
		return NULL;
	}

	solver s = malloc(sizeof(struct solver));

	s->c = create_cnf();
	s->p = p;
	
	return s;
}

solver create_solver_for(char* path)
{
	puzzle p = load_puzzle(path);

	if (p == NULL)
	{
		LOG_ERROR("Failed to load puzzle");
		return NULL;
	}

	solver s = create_solver(p);

	return s;
}

void make_cnf(solver s)
{
	puzzle p = s->p;
	cnf c = s->c;

	int puzzle_size = get_size(p);

	unsigned int letter_amount = puzzle_size; 

	// Le nombre de variable propositionnel X_ijl (+1 car on compte aussi les variable pour les positions de EMPTY)
	unsigned int var_amount = (letter_amount + 1) * puzzle_size * puzzle_size;
	cnf_set_nb_vars(c, var_amount);

	lit* lits_rows_tmp = malloc(sizeof(lit) * puzzle_size);
	lit* lits_cols_tmp = malloc(sizeof(lit) * puzzle_size);

	// vvv EXACTEMENT UNE SEUL LIGNE PAR COLONNE ET LIGNE !
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

	lit* lits_case_tmp = malloc(sizeof(lit) * letter_amount);

	// EXACTEMENT 1 SEUL LETTER PAR CASE
	for (int i = 0; i < puzzle_size; ++i)
	{
		for (int j = 0; j < puzzle_size; ++j)
		{
			for (letter let = 1; let <= letter_amount; ++let)  // On commence à 1 car 0 == EMPTY on ne veut pas que des cases soit vide!
			{
				lit li = get_var_from_letter_pos(let, i, j, puzzle_size);
				lits_case_tmp[let - 1] = li;
			}

			exactlyOne(c, lits_case_tmp, letter_amount);
		}
	}

	free(lits_rows_tmp);
	free(lits_cols_tmp);
	free(lits_case_tmp);
}

void write_dimacs(solver s, char* outpath)
{
	FILE* f = fopen(outpath, "w");

	if (f == NULL)
	{
		LOG_ERROR("Erreur fichier result not found");
		return;
	}

	fprint_letters_pos_comment(f, get_size(s->p));
	fprint_cnf(f, s->c);

	fclose(f);
}

void print_dimacs(solver s)
{
	print_cnf(s->c);
}
