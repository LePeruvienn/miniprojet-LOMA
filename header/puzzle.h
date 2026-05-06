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
	EMPTY,
	A, B, C, D, E, F

} letter;

puzzle create_puzzle(char* puzzle_path);
void free_puzzle(puzzle p);

letter get_constraint(edge e, unsigned int i);
letter get_letter(unsigned int i, unsigned int j);

#endif // PUZZLE_H
