#include "interface.h"
#include "puzzle.h"
#include "solver.h"
#include "sat.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	
	int status;
	var* result;

} sat_result ;

unsigned int nb_solution_found = 0;

sat_result find_solution(config conf, puzzle p)
{
	// Creating SAT solver
	sat _sat = create_sat(conf.dimacs_path,
	                      conf.sat_path,
	                      conf.result_path,
	                      get_size(p));

	run_glucose(_sat, conf.glucose_exe);
	read_result_build_solution(_sat);

	sat_result res;

	res.status = get_status(_sat);
	res.result = get_result_copy(_sat);

	if (res.status == SAT)
	{
		printf("SAT !\n");
	}

	display_solution(_sat);

	free_sat(_sat);

	return res;
}

int main(int argc, char** argv)
{
	config conf = get_config(argc, argv);

	if (conf.print_config)
	{
		print_config(conf);
	}

	puzzle p = load_puzzle(conf.puzzle_path);

	if (p == NULL)
	{
		perror("Failed to load puzzle");
		return 10;
	}

	if (conf.print_input)
	{
		printf("\n -------- Input -------- \n\n");
		print_puzzle(p);
		printf("\n ----------------------- \n");
	}

	solver s = create_solver(p);
	
	if (s == NULL)
	{
		perror("Failed to create solver");
		return 11;
	}

	make_cnf(s);
	write_dimacs(s, conf.dimacs_path);

	printf("\n>>> Finding puzzle solution ...\n\n");

	// Try to find a solution
	sat_result res = find_solution(conf, p);

	if (res.status != SAT)
	{
		printf("\nResults: No solution found :(\n");
		return nb_solution_found;
	}

	++nb_solution_found;

	printf("\n>>> Trying to find second solution ...\n\n");

	deny_solution(s, res.result, get_size(p));
	write_dimacs(s, conf.dimacs_path);

	sat_result res2 = find_solution(conf, p);

	if (res2.status == SAT)
	{
		printf("\nResults: 2 solutions found :D\n");
		++nb_solution_found;
	}
	else
	{
		printf("\nResults: 1 solution found !\n");
	}

	free_solver(s);
	free(res.result);
	free(res2.result);

	return nb_solution_found;
}
