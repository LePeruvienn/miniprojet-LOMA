#ifndef CNF_H
#define CNF_H

#include "puzzle.h"

typedef struct cnf* cnf;

cnf create_cnf(puzzle p);
void free_cnf(cnf c);

#endif // CNF_H
