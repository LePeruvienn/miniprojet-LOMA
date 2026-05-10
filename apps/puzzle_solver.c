#include "interface.h"
#include "puzzle.h"
#include "solver.h"
#include "sat.h"

#include <stdio.h>

typedef struct {
	
	int status;
	var* result;

} sat_result ;

sat_result find_solution(config conf, puzzle p)
{
	// Creating SAT solver
	sat _sat = create_sat(conf.dimacs_path,
	                      conf.sat_path,
	                      conf.result_path,
	                      get_size(p));

	run_glucose(_sat, conf.glucose_exe);
	read_result_build_solution(_sat);

	display_solution(_sat);

	sat_result res;

	res.status = get_status(_sat);
	res.result = get_result(_sat);

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
		return 1;
	}

	if (conf.print_input)
	{
		print_puzzle(p);
	}

	solver s = create_solver(p);
	
	if (s == NULL)
	{
		perror("Failed to create solver");
		return 2;
	}

	make_cnf(s);
	write_dimacs(s, conf.dimacs_path);

	// Try to find a solution
	sat_result res = find_solution(conf, p);

	if (res.status != SAT)
	{
		return 3;
	}

	printf("Trying to find second solution ...\n");

	deny_solution(s, res.result, get_size(p));

	sat_result res2 = find_solution(conf, p);

	if (res2.status == SAT)
	{
		printf("2 solution found !\n");
	}

	free_solver(s);

	return 0;
}
