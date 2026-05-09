#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <puzzle.h>
#include <sat.h>

int main()
{

    puzzle p = load_puzzle("../input/puzzle3.data");

    display_bords(p);


    // TODO ARTHUR from p create problem.cnf


    sat sat = create_sat(3);

    run_glucose("wsl /home/maxence/sat/glucose/simp/glucose", "../input", "../out");

    read_result_build_solution(sat, "../out");
    display_result(sat);
    display_solution(sat);

    free_sat(sat);

    return 0;
}