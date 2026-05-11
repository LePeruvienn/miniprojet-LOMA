#include "sat.h"
#include "letter_pos.h"
#include "logger.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sat
{
    int status; // 20 not sat / 0 not computed / 10 sat
    int size;

    char* dimacs_path;
    char* sat_path;
    char* result_path;

    var* result; // the result.txt file 
    letter** solution; // the solution
};

sat create_sat(char* dimacs_path, char* sat_path, char* result_path, int puzzle_size)
{
    sat s = malloc(sizeof(struct sat));

    if (s == NULL) {
        return NULL;
    }

    s->status = 0;
    s->size = puzzle_size; 
    s->dimacs_path = dimacs_path;
    s->sat_path = sat_path;
    s->result_path = result_path;

    s->result = NULL;

    s->solution = malloc(puzzle_size * sizeof(letter*));

    if (s->solution == NULL) {
        free(s);
        return NULL;
    }

    for (int i = 0; i < puzzle_size; i++) {
        s->solution[i] = malloc(puzzle_size * sizeof(letter));
    }

    return s;
}

void free_sat(sat s)
{
    if (s == NULL)
    {
        LOG_ERROR("Tried to free a NULL ptr.");
        return;
    }
    
    for (int i = 0; i < s->size; i++) {
        free(s->solution[i]);
    }

    free(s->solution);

    if (s->result != NULL) {
        free(s->result);
    }

    free(s);
}

int get_status(sat s)
{
    return s->status;
}

var* get_result(sat s)
{
    if (s == NULL || s->result == NULL)
    {
        LOG_ERROR("Sat or result is NULL !");
        return NULL;
    }

    return s->result;
}

var* get_result_copy(sat s)
{
    if (s == NULL || s->result == NULL)
    {
        LOG_ERROR("Sat or result is NULL !");
        return NULL;
    }

    unsigned int buf_size = sizeof(var) * (s->size * s->size);

    var* copy = malloc(buf_size);

    if (copy != NULL)
    {
        memcpy(copy, s->result, buf_size);
    }

    return copy;
}

letter** get_solution(sat s)
{
    return s->solution;
}

void set_status(sat s, int status)
{
    s->status = status;
}

void set_result(sat s, var* result)
{
    s->result = result;
}

void display_result(sat s)
{
    if (s->status == NOT_COMPUTED) {
        printf("Not computed yet.\n");
        return;
    }
    if (s->status == NOT_SAT) {
        printf("UNsISFIABLE\n");
        return;
    }

    printf("Result :\n");
    for (int i = 0; i < (s->size * s->size) ; i++) {
        printf(" %d ", s->result[i]);
    }
    printf("\n");
}

void display_solution(sat s)
{
    if (s->status == NOT_COMPUTED) {
        printf("Not computed yet.\n");
        return;
    }
    if (s->status == NOT_SAT) {
        printf("UNSATISFIABLE\n");
        return;
    }

    printf("Solution: \n");
    for (int i = 0; i < s->size; i++) {
        for (int j = 0; j < s->size; j++) {
            print_letter(s->solution[j][i]); // Flipped j & i or else the print will be flipped
            printf(" ");
        }
        printf("\n");
    }
}

void run_glucose(sat s, char* glucose_exe) {

    char command[1024];

    snprintf(command, sizeof(command),
        "%s %s > %s %s",
        glucose_exe, s->dimacs_path, s->sat_path, s->result_path);

    // system("wsl /home/maxence/sat/glucose/simp/glucose ../input/problem.cnf > ../out/satisfaisable.txt ../out/result.txt");
    int return_code = system(command);

    #ifdef _WIN32
        s->status = return_code;
    #else
        s->status = WEXITSTATUS(return_code);
    #endif
}

void insert_letter(sat sat, letter_pos lp) {

    sat->solution[lp.x][lp.y] = lp.l;
}

void read_result_build_solution(sat s) {

    FILE* f = fopen(s->result_path, "r");

    if (f == NULL) {
        printf("Erreur fichier result not found\n");
        return;
    }

    s->result = calloc(s->size * s->size, sizeof(var));
    if (s->result == NULL) {
        printf("Erreur calloc\n");
        return;
    }

    int n;
    int taille = 0;
    while (fscanf(f, "%d", &n) == 1) {
        if (n > 0) {
            s->result[taille] = n;
            taille++;
        }
    }

    fclose(f);

    for (int i = 0; i < taille; i++) {

        lit v = s->result[i];

        if (v < 0)
        {
            continue;
        }

        letter_pos lp = get_letter_pos_from_var(v, s->size);
        insert_letter(s, lp);
    }
}
