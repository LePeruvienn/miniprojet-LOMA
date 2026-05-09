#ifndef LETTER_H
#define LETTER_H

#include <stdio.h>

typedef enum
{
	EMPTY = 0,
	A, B, C, D, E, F, G, H, I, J, 
	K, L, M, N, O, P, Q, R, S, T, 
	U, V, W, X, Y, Z,

	LETTER_COUNT = 26

} letter;

static const letter _ = EMPTY;

letter get_letter(char c);

void print_letter(letter l);
void fprint_letter(FILE* f, letter l);

#endif // LETTER_H
