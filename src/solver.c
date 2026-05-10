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

	unsigned int puzzle_size = get_size(p);

	unsigned int letter_amount = get_puzzle_nb_letter(p);

	// Le nombre de variable propositionnel X_ijl (+1 car on compte aussi les variable pour les positions de EMPTY)
	unsigned int var_amount = (letter_amount + 1) * puzzle_size * puzzle_size;
	cnf_set_nb_vars(c, var_amount);

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

	letter start_letter = (puzzle_size - letter_amount == 0) ? 1 : 0; // 0 == EMPTY
	unsigned int lits_case_size = letter_amount - start_letter + 1;
	lit* lits_case_tmp = malloc(sizeof(lit) * lits_case_size);

	// 2. EXACTEMENT 1 SEUL LETTER PAR CASE (ou case vide si possible)
	for (int i = 0; i < puzzle_size; ++i)
	{
		for (int j = 0; j < puzzle_size; ++j)
		{
			for (letter let = start_letter; let <= letter_amount; ++let)
			{
				lit li = get_var_from_letter_pos(let, i, j, puzzle_size);
				lits_case_tmp[let - start_letter] = li;
			}

			exactlyOne(c, lits_case_tmp, lits_case_size);
		}
	}

	// 3. REGLES POUR LES BORDS
	for (edge e = 0; e < 4; ++e) // de 0 à 4 car il y a 4 edges
	{
		char* border = get_bord(p, e);

		for (int i = 0; i < puzzle_size; ++i)
		{
			letter l = get_letter(border[i]);
		
			if (l == EMPTY) continue;
		
			unsigned int x;
			unsigned int y;

			switch (e)
			{
				case TOP: x = i; y = 0;
					break;

				case BOTTOM: x = i; y = puzzle_size - 1;
					break;

				case LEFT: x = 0; y = i;
					break;

				case RIGHT: x = puzzle_size - 1; y = i;
					break;
			}
	
			var v = get_var_from_letter_pos(l, x, y, puzzle_size);
			add_lit(c, v);
			end_clause(c);
		}
	}

	// 4. Regles pour les lettre déjà placer dans le puzzle
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

	free(lits_rows_tmp);
	free(lits_cols_tmp);
	free(lits_case_tmp);
}

void deny_solution(solver s, var* solution, unsigned int size)
{
	cnf c = s->c;

	for (unsigned i = 0; i < size; ++i)
	{
		var v = solution[i];
		lit l = - (lit) v;

		add_lit(c, l);
	}
	end_clause(c);
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
