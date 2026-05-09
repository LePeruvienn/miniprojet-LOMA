#include "letter.h"
#include <stdio.h>

void print_letter(letter l)
{
	switch (l)
	{
		case A: printf("A"); break;
		case B: printf("B"); break;
		case C: printf("C"); break;
		case D: printf("D"); break;
		case E: printf("E"); break;
		case F: printf("F"); break;
		case G: printf("G"); break;
		case H: printf("H"); break;
		case I: printf("I"); break;
		case J: printf("J"); break;

		case EMPTY: printf("EMPTY"); break;
	}
}

void fprint_letter(FILE* f, letter l)
{
	switch (l)
	{
		case A: fprintf(f, "A"); break;
		case B: fprintf(f, "B"); break;
		case C: fprintf(f, "C"); break;
		case D: fprintf(f, "D"); break;
		case E: fprintf(f, "E"); break;
		case F: fprintf(f, "F"); break;
		case G: fprintf(f, "G"); break;
		case H: fprintf(f, "H"); break;
		case I: fprintf(f, "I"); break;
		case J: fprintf(f, "J"); break;

		case EMPTY: fprintf(f, "EMPTY"); break;
	}
}
