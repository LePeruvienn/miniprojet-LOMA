#include "puzzle.h"

#include <stdlib.h>
#include <stdio.h>

struct puzzle
{
	unsigned int width;
	unsigned int height;
	unsigned char* buffer;
};

puzzle create_puzzle(char* puzzle_path)
{
	puzzle p = malloc(sizeof(struct puzzle));

	p->width = 0;
	p->height = 0;
	p->buffer = NULL;

	return p;
}

void print_letter(letter l)
{
	switch (l)
	{
		case A: printf("A");
		case B: printf("B");
		case C: printf("C");
		case D: printf("D");
		case E: printf("E");
		case F: printf("F");
		case G: printf("G");
		case H: printf("H");
		case I: printf("I");
		case J: printf("J");

		case EMPTY: printf("_");
	}
}

void free_puzzle(puzzle p)
{
	if(p == NULL)
	{
		return;
	}

	if (p->buffer != NULL)
	{
		free(p->buffer);
	}

	free(p);
}
