#ifndef LETTER_POS_H
#define LETTER_POS_H

#include "letter.h"
#include "cnf.h"

#include <stdio.h>

typedef struct 
{
	letter l;
	unsigned int x;
	unsigned int y;

} letter_pos;


var get_var_from_letter_pos(letter l, unsigned int x, unsigned int y, int puzzle_size);
letter_pos get_letter_pos_from_var(var v, int puzzle_size);

void print_letter_pos(letter_pos lp);
void fprint_letter_pos(FILE* f, letter_pos lp);

void fprint_letters_pos_comment(FILE* f, unsigned int puzzle_size);

#endif // LETTER_POS_H
