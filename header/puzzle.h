#ifndef PUZZLE_H
#define PUZZLE_H

#include <stdio.h>

typedef struct puzzle* puzzle;

typedef enum
{
	TOP = 0, BOTTOM = 1,
	RIGHT = 2, LEFT = 3

} edge;

puzzle create_puzzle(int size);
void free_puzzle(puzzle p);

//letter get_constraint(edge e, unsigned int i);
//letter get_letter(unsigned int i, unsigned int j);
int get_size(puzzle p);
char* get_bord(puzzle p, edge e);
char** get_grille(puzzle p);
char get_cell(puzzle p, int row, int col);
void load_top_from_file(puzzle p, FILE* f);
void load_left_from_file(puzzle p, FILE* f);
void load_right_from_file(puzzle p, FILE* f);
void load_bottom_from_file(puzzle p, FILE* f);
void load_grid_from_file(puzzle p, FILE* f);
void init_file(FILE* f, int ligne_to_skip);
void display_bords(puzzle p);
puzzle load_puzzle(const char* filepath);

void print_puzzle(puzzle p);

#endif // PUZZLE_H
