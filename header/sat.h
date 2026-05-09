#ifndef sat_H
#define sat_H

#include "cnf.h"

typedef struct sat* sat;

sat create_sat(int size);
void free_sat(sat sat);
int get_status(sat sat);
void set_status(sat sat, int s);
int* get_result(sat sat);
void set_result(sat sat, int* result);
char** get_solution(sat sat);
void display_solution(sat sat);
void display_result(sat sat);

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
void run_glucose(const char* glucose, const char* input, const char* out);
void insert_letter(sat sat, int ligne, int collum, char letter);

/*
 * read_result_build_solution
 *
 * ATTENTION `out` doit avoir un file result.txt
 *
 * Exemple :
 * read_result_build_solution(sat, "../out");
 */
void read_result_build_solution(sat sat, char* out_dir);

#endif
