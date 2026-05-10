#include "letter.h"
#include <stdio.h>

letter get_letter(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (letter) (c - 'A' + 1);
	}

	return EMPTY;
}

void print_letter(letter l)
{
	if (l >= A && l <= Z)
	{
		printf("%c", 'A' + (l - 1));
	} 
	else
	{
		printf("_");
	}
}

void fprint_letter(FILE* f, letter l)
{
	if (l >= A && l <= Z)
	{
		fprintf(f, "%c", 'A' + (l - 1));
	} 
	else
	{
		fprintf(f, "_");
	}
}
