#ifndef CNF_H
#define CNF_H

#include "puzzle.h"

#define CLAUSE_END 0

/* 
 * Structure représentant une Forme Normale Conjonctive (CNF en anglais)
 *
 * Elle est représeter par : 
 *
 * - Son nombre de variables prépositionnel
 * - Son nombre de clauses
 * - Ses clauses
 *
 * Chaque clause est une ligne de littéraux, la fin d'une ligne est représenter par un 0.
 */
typedef struct cnf* cnf;

/* 
 * Représente une variable propositionnel 
 * Ex: (A, B, C, ...)
 */
typedef unsigned int var;

/* 
 * Représente un litteral
 * Ex: ( A, -A )
 */
typedef int lit;

cnf create_cnf();
cnf create_cnf_from_puzzle(puzzle p);

void cnf_set_nb_vars(cnf c, unsigned int nb_vars);

lit get_last_lit(cnf c);

void add_clause(cnf c, lit* ls, unsigned int size);
void add_lit(cnf c, lit l);
void end_clause(cnf c);

void atLeastOne(cnf c, lit* ls, unsigned int size);
void atMostOne(cnf c, lit* ls, unsigned int size);
void exactlyOne(cnf c, lit* ls, unsigned int size);

void print_cnf(cnf c);
void fprint_cnf(FILE* str, cnf c);

void free_cnf(cnf c);

#endif // CNF_H
