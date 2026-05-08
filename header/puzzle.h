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
	EMPTY = 0,
	A, B, C, D, E, F, G, H, I, J

} letter;

static const letter _ = EMPTY;

puzzle create_puzzle(int size);
void free_puzzle(puzzle p);

//void print_puzzle(puzzle p);
void print_letter(letter l);

//letter get_constraint(edge e, unsigned int i);
//letter get_letter(unsigned int i, unsigned int j);
void load_top_from_file(puzzle p, FILE* f);
void load_left_from_file(puzzle p, FILE* f);
void load_right_from_file(puzzle p, FILE* f);
void load_bottom_from_file(puzzle p, FILE* f);
void load_grid_from_file(puzzle p, FILE* f);
void init_file(FILE* f, int ligne_to_skip);
void insert_letter(puzzle p, int ligne, int collum, char letter);
void display_bords(puzzle p);
void display_grid(puzzle p);
void load_puzzle(const char* filepath);

#endif // PUZZLE_H
