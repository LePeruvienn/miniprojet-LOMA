#include "interface.h"
#include "puzzle.h"
#include "solver.h"
#include "sat.h"

#include <stdio.h>

int main(int argc, char** argv)
{
	config conf = get_config(argc, argv);

	print_config(conf);

	puzzle p = load_puzzle(conf.puzzle_path);

	if (p == NULL)
	{
		perror("Failed to load puzzle");
		return 1;
	}

	solver s = create_solver(p);
	
	if (s == NULL)
	{
		perror("Failed to create solver");
		return 1;
	}

	make_cnf(s);
	write_dimacs(s, conf.dimacs_path);

	// Creating SAT solver
	sat _sat = create_sat(conf.dimacs_path,
	                      conf.sat_path,
	                      conf.result_path,
	                      get_size(p));

	run_glucose(_sat, conf.glucose_exe);
	read_result_build_solution(_sat);

	display_solution(_sat);

	free_solver(s);
	free_sat(_sat);

	return 0;
}
