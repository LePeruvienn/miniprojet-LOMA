#include "sat.h"
#include "letter_pos.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

struct sat
{
    int s; // -1 not sat / 0 not computed / 1 sat
    int size;
    var* result; // the result.txt file 
    letter** solution; // the solution
};

sat create_sat(int size)
{
    sat sat = malloc(sizeof(struct sat));

    if (sat == NULL) {
        return NULL;
    }

    sat->s = 0;
    sat->size = size; 
    sat->result = NULL;

    sat->solution = malloc(size * sizeof(char*));

    if (sat->solution == NULL) {
        free(sat);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        sat->solution[i] = malloc(size * sizeof(char));
    }

    return sat;
}

void free_sat(sat sat)
{
    for (int i = 0; i < sat->size; i++) {
        free(sat->solution[i]);
    }

    free(sat->solution);

    if (sat->result != NULL) {
        free(sat->result);
    }

    free(sat);
}

int get_status(sat sat)
{
    return sat->s;
}

var* get_result(sat sat)
{
    return sat->result;
}

letter** get_solution(sat sat)
{
    return sat->solution;
}

void set_status(sat sat, int s)
{
    sat->s = s;
}

void set_result(sat sat, var* result)
{
    sat->result = result;
}

void display_result(sat sat)
{
    if (sat->result == 0) {
        printf("Not computed yet.\n");
        return;
    }
    if (sat->s == -1) {
        printf("UNSATISFIABLE\n");
        return;
    }

    printf("Result :\n");
    for (int i = 0; i < (sat->size * sat->size) ; i++) {
        printf(" %d ", sat->result[i]);
    }
    printf("\n");
}

void display_solution(sat sat)
{
    if (sat->result == 0) {
        printf("Not computed yet.\n");
        return;
    }
    if (sat->s == -1) {
        printf("UNSATISFIABLE\n");
        return;
    }

    printf("Solution: \n");
    for (int i = 0; i < sat->size; i++) {
        for (int j = 0; j < sat->size; j++) {
            print_letter(sat->solution[j][i]); // Flipped j & i or else the print will be flipped
            printf(" ");
        }
        printf("\n");
    }
}

void run_glucose(const char* glucose, const char* input, const char* out) {

    char command[1024];

    snprintf(command, sizeof(command),
        "%s %s/problem.cnf > %s/satisfaisable.txt %s/result.txt",
        glucose, input, out, out);

    system(command);
    // system("wsl /home/maxence/sat/glucose/simp/glucose ../input/problem.cnf > ../out/satisfaisable.txt ../out/result.txt");
}

void insert_letter(sat sat, letter_pos lp) {

    sat->solution[lp.x][lp.y] = lp.l;
}

void read_result_build_solution(sat sat, char* out_dir) {

    char file_path[512];

    snprintf(file_path, sizeof(file_path), "%s/result.txt", out_dir);

    FILE* f = fopen(file_path, "r");

    if (f == NULL) {
        printf("Erreur fichier result not found\n");
        return;
    }

    sat->result = calloc(sat->size * sat->size, sizeof(int));
    if (sat->result == NULL) {
        printf("Erreur calloc\n");
        return;
    }

    int n;
    int taille = 0;
    while (fscanf(f, "%d", &n) == 1) {
        if (n > 0) {
            sat->result[taille] = n;
            taille++;
        }
    }

    fclose(f);

    for (int i = 0; i < taille; i++) {

        lit v = sat->result[i];

        if (v < 0)
        {
            continue;
        }

        letter_pos lp = get_letter_pos_from_var(v, sat->size);
        insert_letter(sat, lp);
    }
}
