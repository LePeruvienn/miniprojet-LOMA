#include "solver.h"
#include "logger.h"
#include "puzzle.h"
#include "cnf.h"
#include "letter_pos.h"
#include "rule.h"

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
		LOG_ERROR("Solver failed to load puzzle.");
		return NULL;
	}

	solver s = create_solver(p);

	return s;
}

void free_solver(solver s)
{
	free_cnf(s->c);
	free_puzzle(s->p);
	free(s);
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

	// 1. EXACTEMENT UNE SEUL LETTER LIGNE PAR COLONNE ET LIGNE !
	make_rule_one_letter_per_row_column(c, puzzle_size, letter_amount);

	// 2. EXACTEMENT 1 SEUL LETTER PAR CASE (ou case vide si possible)
	make_rule_unique_letter_per_case(c, puzzle_size, letter_amount);

	// 3. REGLES POUR LES BORDS
	make_rule_letter_borders(c, puzzle_size, letter_amount, p);

	// 4. Regles pour les lettre déjà placer dans le puzzle
	make_rule_preplaced_letters(c, puzzle_size, letter_amount, p);
}

void deny_solution(solver s, var* solution, unsigned int size)
{
	cnf c = s->c;
	make_rule_deny_solution(c, solution, size);
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
