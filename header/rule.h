#ifndef RULE_H
#define RULE_H

#include "cnf.h"
#include "letter.h"

void make_rule_one_letter_per_row_column(cnf c, unsigned int puzzle_size, unsigned int letter_amount);
void make_rule_unique_letter_per_case(cnf c, unsigned int puzzle_size, unsigned int letter_amount);

void make_rule_letter_borders(cnf c, unsigned int puzzle_size, unsigned int letter_amount, puzzle p);
void make_rule_letter_border_no_empty(cnf c, unsigned int puzzle_size, letter l, edge e, unsigned int edge_index);
void make_rule_letter_border_with_empty(cnf c, unsigned int puzzle_size, unsigned int empty_space_size, letter l, edge e, unsigned int edge_index);

void make_rule_preplaced_letters(cnf c, unsigned int puzzle_size, unsigned int letter_amount, puzzle p);

void make_rule_deny_solution(cnf c, var* solution, unsigned int size);

#endif // RULE_H
