#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "puzzle.h"
#include "logger.h"

struct puzzle
{
	unsigned int size;
	unsigned int nb_letter;
	char* bords[4];// TOP, BOTTOM, RIGHT, LEFT using emun "edge"
	char** grille;
};

unsigned int get_size(puzzle p)
{
	return p->size;
}

unsigned int get_puzzle_nb_letter(puzzle p)
{
	return p->nb_letter;
}

char* get_bord(puzzle p, edge e)
{
	return p->bords[e];
}

char** get_grille(puzzle p)
{
	return p->grille;
}

char get_cell(puzzle p, int row, int col)
{
	return p->grille[row][col];
}

puzzle create_puzzle(unsigned int size, unsigned nb_letter)
{
	puzzle p = malloc(sizeof(struct puzzle));
	if (!p) return NULL;

	p->size = size;
	p->nb_letter = nb_letter;

	p->bords[TOP] = malloc(size * sizeof(char));
	p->bords[BOTTOM] = malloc(size * sizeof(char));
	p->bords[RIGHT] = malloc(size * sizeof(char));
	p->bords[LEFT] = malloc(size * sizeof(char));

	// grid
	p->grille = malloc(size * sizeof(char*));

	if (p->grille == NULL) {
		return NULL;
	}

	for (int i = 0; i < size; i++) {
		p->grille[i] = malloc(size * sizeof(char));
	}

	return p;
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

	// read third line
	if (fgets(line, sizeof(line), f)) {
		size_t longeur_ligne = strlen(line);

		for (int j = 0; j < p->size; j++) {
			int index = (j * 2) + 1; // Saute un espace
			if ((index + 1) > longeur_ligne) { // check if end of ligne
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

puzzle load_puzzle(const char* filepath)
{
	FILE* f = fopen(filepath, "r");

	if (f == NULL) {
		printf("Erreur fichier\n");
		return NULL;
	}

	char line[100];

	// Lire la première ligne (souvent inutile mais conservée comme ton main)
	if (fgets(line, sizeof(line), f) == NULL) {
		printf("Fichier vide\n");
		fclose(f);
		return NULL;
	}

	// Lire la ligne de taille
	if (fgets(line, sizeof(line), f) == NULL) {
		printf("Erreur lecture taille\n");
		fclose(f);
		return NULL;
	}

	int size;
	int nb_letter;
	(void) sscanf(line, "%d %d", &size, &nb_letter); // (void) enleve le warning 

	if (nb_letter <= 0 || size <= 0)
	{
		LOG_ERROR("Failed to read puzzle size and number of letter");
		return NULL;
	}

	if (nb_letter > size)
	{
		LOG_ERROR("The amout of letter of the puzzle cannot be more than the size of the puzzle");
		return NULL;
	}

	puzzle p = create_puzzle(size, nb_letter);

	load_top_from_file(p, f);
	load_left_from_file(p, f);
	load_right_from_file(p, f);
	load_bottom_from_file(p, f);
	load_grid_from_file(p, f);

	fclose(f);

	return p;
}

void print_puzzle(puzzle p)
{
	printf("Puzzle size = %d\n", p->size);
	printf("Puzzle nb letters = %d\n", p->nb_letter);

	char* top = p->bords[TOP];
	char* bot = p->bords[BOTTOM];
	char* left = p->bords[LEFT];
	char* right = p->bords[RIGHT];
	char** grille = p->grille;

	printf("    ");
	for (int j = 0; j < p->size; j++)
	{
		printf("%c ", top[j] == 0 ? '.' : top[j]);
	}

	printf("\n    ");

	for (int j = 0; j < p->size; j++)
	{
		printf("- ");
	}

	printf("\n");

	for (int i = 0; i < p->size; i++)
	{
		printf("%c | ", left[i] == 0 ? '.' : left[i]);

		for (int j = 0; j < p->size; j++)
		{
			char c = grille[i][j];
			printf("%c ", c == 0 ? ' ' : c);
		}

		printf("| %c\n", right[i] == 0 ? '.' : right[i]);
	}

	printf("    ");

	for (int j = 0; j < p->size; j++)
	{
		printf("- ");
	}

	printf("\n    ");

	for (int j = 0; j < p->size; j++)
	{
		printf("%c ", bot[j] == 0 ? '.' : bot[j]);
	}

	printf("\n");
}
