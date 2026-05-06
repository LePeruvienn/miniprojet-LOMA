#include "puzzle.h"

#include <stdlib.h>

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
