#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "puzzle.h"

struct puzzle
{
	int size;
	char* bords[4];// TOP, BOTTOM, RIGHT, LEFT using emun "edge"
	char** grille;
};

puzzle create_puzzle(int size)
{
	puzzle p = malloc(sizeof(struct puzzle));
	if (!p) return NULL;

	p->size = size;

	p->bords[TOP] = malloc(size * sizeof(char));
	p->bords[BOTTOM] = malloc(size * sizeof(char));
	p->bords[RIGHT] = malloc(size * sizeof(char));
	p->bords[LEFT] = malloc(size * sizeof(char));

	// grid
	p->grille = malloc(size * sizeof(char*));

	for (int i = 0; i < size; i++) {
		p->grille[i] = malloc(size * sizeof(char));
	}

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
	for (int i = 0; i < p->size; i++) {
		free(p->grille[i]);
	}

	free(p->grille);

	free(p->bords[TOP]);
	free(p->bords[BOTTOM]);
	free(p->bords[RIGHT]);
	free(p->bords[LEFT]);

	free(p);
}

char get_edge(puzzle p, edge e, int i)
{
	return p->bords[e][i];
}

void load_top_from_file(puzzle p, FILE* f)
{
	char line[256];
	init_file(f, 2);
	int fin_atteinte = 0;

	// read third line
	if (fgets(line, sizeof(line), f)) {

		for (int j = 0; j < p->size; j++) {
			int index = (j * 2) + 1; // Saute un espace
			if (fin_atteinte == 1) {
				p->bords[TOP][j] = ' ';
			}
			else {
				p->bords[TOP][j] = line[index]; // ecrie le charactere 
				if (line[index + 1] == '\n') { // check if end of ligne
					fin_atteinte = 1;
				}
			}
		}
	}
}

void load_left_from_file(puzzle p, FILE* f)
{
	char line[256];
	init_file(f, 3);

	for (int j = 0; j < p->size; j++) {
		if (fgets(line, sizeof(line), f)) {
			p->bords[LEFT][j] = line[0]; // ecrie le charactere 
		}
	}
}

void load_right_from_file(puzzle p, FILE* f)
{
	char line[256];
	init_file(f, 3);

	for (int j = 0; j < p->size; j++) {
		if (fgets(line, sizeof(line), f)) {
			int index = (p->size * 2);
			if (line[index] == '\n') {
				p->bords[RIGHT][j] = ' ';
			} else {
				p->bords[RIGHT][j] = line[index]; // ecrie le charactere 
			}
		}
	}
}

void load_bottom_from_file(puzzle p, FILE* f)
{
	char line[256];
	init_file(f, 3 + p->size);
	// int fin_atteinte = 0;

	// read third line
	if (fgets(line, sizeof(line), f)) {
		int longeur_ligne = strlen(line);

		for (int j = 0; j < p->size; j++) {
			int index = (j * 2) + 1; // Saute un espace
			if (index + 1 > longeur_ligne) { // check if end of ligne
				p->bords[BOTTOM][j] = ' ';
			}
			else {
				p->bords[BOTTOM][j] = line[index]; // ecrie le charactere 
				
			}
		}
	}
}

void load_grid_from_file(puzzle p, FILE* f)
{
	char line[256];
	init_file(f, 3);

	for (int i = 0; i < p->size; i++) { // pour chaque ligne 
		if (fgets(line, sizeof(line), f)) {// next ligne
			// int len = strlen(line);
			for (int j = 0; j < p->size; j++) {// next usefull charchacter
				p->grille[i][j] = line[(j * 2) + 1];
			}
		}
	}
}

void init_file(FILE* f, int ligne_to_skip)
{
	char tmp[256];

	// restart the file
	rewind(f);

	for (int i = 0; i < ligne_to_skip; i++) {
		if (!fgets(tmp, sizeof(tmp), f)) {
			break; // si y'a pas assez de ligne
		}
	}
}

void display_bords(puzzle p)
{

	printf("TOP:    ");
	for (int i = 0; i < p->size; i++)
		printf("%c ", p->bords[TOP][i]);
	printf("/\n");

	printf("LEFT:   ");
	for (int i = 0; i < p->size; i++)
		printf("%c ", p->bords[LEFT][i]);
	printf("/\n");

	printf("RIGHT:  ");
	for (int i = 0; i < p->size; i++)
		printf("%c ", p->bords[RIGHT][i]);
	printf("/\n");

	printf("BOTTOM: ");
	for (int i = 0; i < p->size; i++)
		printf("%c ", p->bords[BOTTOM][i]);
	printf("/\n");
}

void display_grid(puzzle p)
{
	printf("GRID: \n");
	for (int i = 0; i < p->size; i++) {
		for (int j = 0; j < p->size; j++) {
			printf("%c ", p->grille[i][j]);
		}
		printf("\n");
	}
}
