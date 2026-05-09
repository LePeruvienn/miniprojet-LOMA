#include "letter_pos.h"
#include "logger.h"

var get_var_from_letter_pos(letter l, unsigned int x, unsigned int y, int puzzle_size)
{
	if (x > puzzle_size || y > puzzle_size)
	{
		LOG_ERROR("Les valeurs de x ou y sont trop grande !");
		return 0;
	}

	unsigned int let_offset = (l * puzzle_size * puzzle_size) + 1; // +1 cause lit 0 is CLAUSE_END
	unsigned int pos_offset = (y * puzzle_size) + x;

	return let_offset + pos_offset;
}

letter_pos get_letter_pos_from_var(var v, int puzzle_size)
{
	if (v == 0)
	{
		LOG_ERROR("Une variable propositionnel qui vaut 0 est invalide !!");
		return (letter_pos ) {0, 0, 0};
	}

	unsigned int v0 = v - 1;

	unsigned int pos_buf_size = puzzle_size * puzzle_size; // The position "buffer" size for each letter
	unsigned int pos = v0 % pos_buf_size; // With 1 the first case, and 9 the last

	letter l = v0 / pos_buf_size;

	unsigned int x = pos % puzzle_size;
	unsigned int y = pos / puzzle_size;

	return (letter_pos) {l, x, y};
}

void print_letter_pos(letter_pos lp)
{
	print_letter(lp.l);
	printf("(%d,%d)", lp.x, lp.y);
}

void fprint_letter_pos(FILE* f, letter_pos lp)
{
	fprint_letter(f, lp.l);
	fprintf(f, "(%d,%d)", lp.x, lp.y);
}

void fprint_letters_pos_comment(FILE* f, unsigned int puzzle_size)
{
	unsigned int var_amount = (puzzle_size + 1) * puzzle_size * puzzle_size;

	fprintf(f, "c ---- VARIABLES ---- \n");
	for (var v = 1; v <= var_amount; ++v)
	{
		fprintf(f, "c %d \t == ", v);
		letter_pos lp = get_letter_pos_from_var(v, puzzle_size);
		fprint_letter_pos(f, lp);
		fprintf(f, "\n");
	}
	fprintf(f, "c ------------------- \n");
}
