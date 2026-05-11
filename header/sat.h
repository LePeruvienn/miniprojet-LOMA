#ifndef sat_H
#define sat_H

#include "cnf.h"
#include "letter_pos.h"

#define SAT 10
#define NOT_SAT 20
#define NOT_COMPUTED 0

typedef struct sat* sat;

sat create_sat(char* dimacs_path, char* sat_path, char* result_path, int puzzle_size);

void free_sat(sat s);
int get_status(sat s);
void set_status(sat s, int status);
var* get_result(sat s);
var* get_result_copy(sat s);
void set_result(sat s, var* result);
letter** get_solution(sat s);
void display_solution(sat s);
void display_result(sat s);

/*
 * run_glucose
 *
 * ATTENTION :
 * - `glucose` doit être le chemin vers l'exécutable Glucose
 *   (ex: /home/maxence/sat/glucose/simp/glucose)
 *
 * - `input` doit avoir un dossier contenant :
 *      input/problem.cnf
 *
 * - `out` doit avoir un dossier existant qui contiendra :
 *      out/satisfaisable.txt
 *      out/result.txt
 *
 * Exemple :
 * run_glucose(glucose_path, "../input", "../out");
 */
void run_glucose(sat s, char* glucose_exe);
void insert_letter(sat s, letter_pos lp);

/*
 * read_result_build_solution
 *
 * ATTENTION `out` doit avoir un file result.txt
 *
 * Exemple :
 * read_result_build_solution(sat, "../out");
 */
void read_result_build_solution(sat s);

#endif
