#include "solver.h"
#include "sat.h"

char* puzzle_path = "input/puzzle4.data";
char* dimacs_path = "input/problem.cnf";

int main()
{
	puzzle p = load_puzzle(puzzle_path);

	if (p == NULL)
	{
		return 1;
	}
	
	int puzzle_size = get_size(p);

	solver s = create_solver(p);

	make_cnf(s);
	// print_dimacs(s);
	write_dimacs(s, dimacs_path);

	sat sat = create_sat(puzzle_size);

	run_glucose("glucose", "input", "out");

	read_result_build_solution(sat, "out");
	display_result(sat);
	display_solution(sat);

	free_sat(sat);

	return 0;
}
