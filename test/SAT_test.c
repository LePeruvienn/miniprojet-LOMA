#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <puzzle.h>
#include <sat.h>

int main()
{

    sat sat = create_sat(3);

    run_glucose("glucose", "../input", "../out");

    read_result_build_solution(sat, "../out");
    display_result(sat);
    display_solution(sat);

    free_sat(sat);

    return 0;
}
