#ifndef LETTER_H
#define LETTER_H

#include <stdio.h>

typedef enum
{
	EMPTY = 0,
	A, B, C, D, E, F, G, H, I, J

} letter;

static const letter _ = EMPTY;

void print_letter(letter l);
void fprint_letter(FILE* f, letter l);

#endif // LETTER_H
