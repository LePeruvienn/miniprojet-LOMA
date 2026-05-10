/*
* Je faisais ça mais si tu comprend ou si tu veut juste faire vsy au pire
*/

#ifndef SOLVER_H
#define SOLVER_H

#include "cnf.h"
#include "puzzle.h"

typedef struct solver* solver;

solver create_solver(puzzle p);
solver create_solver_for(char* path);

void free_solver(solver s);

void make_cnf(solver s);

void write_dimacs(solver s, char* outpath);
void print_dimacs(solver s);

void deny_solution(solver s, var* solution, unsigned int size);

#endif // SOLVER_H
