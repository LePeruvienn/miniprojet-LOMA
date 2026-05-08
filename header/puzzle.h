#ifndef PUZZLE_H
#define PUZZLE_H

#include <stdio.h>

typedef struct puzzle* puzzle;

typedef enum
{
	TOP, BOTTOM,
	RIGHT, LEFT

} edge;

typedef enum
{
	EMPTY,
	A, B, C, D, E, F

} letter;

puzzle create_puzzle(char* puzzle_path);
void free_puzzle(puzzle p);

letter get_constraint(edge e, unsigned int i);
letter get_letter(unsigned int i, unsigned int j);
void load_top_from_file(puzzle p, FILE* f);
void load_left_from_file(puzzle p, FILE* f);
void load_right_from_file(puzzle p, FILE* f);
void load_bottom_from_file(puzzle p, FILE* f);
void load_grid_from_file(puzzle p, FILE* f);
void init_file(FILE* f, int ligne_to_skip);
void display_bords(puzzle p);
void display_grid(puzzle p);

#endif // PUZZLE_H
