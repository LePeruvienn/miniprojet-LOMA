#ifndef PUZZLE_H
#define PUZZLE_H

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

puzzle create_puzzle(char* puzzle_path);
void free_puzzle(puzzle p);

void print_puzzle(puzzle p);
void print_letter(letter l);

letter get_constraint(edge e, unsigned int i);
letter get_letter(unsigned int i, unsigned int j);

#endif // PUZZLE_H
