/*
* Je faisais ça mais si tu comprend ou si tu veut juste faire vsy au pire
*/

#ifndef SOLVER_H
#define SOLVER_H

#include "puzzle.h"
#include "cnf.h"

typedef struct solver* solver;

typedef struct 
{
	letter l;
	unsigned int x;
	unsigned int y;

} letter_pos;

var get_var_from_letter_pos(solver s, letter l, unsigned int x, unsigned int y);
letter_pos get_letter_pos_from_var(solver s, var v);

#endif // SOLVER_H
