#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdbool.h>

#define OUT_DIR "out"
#define DEFAULT_GLUCOSE_EXE "glucose"
#define DEFAULT_DIMACS_PATH OUT_DIR "/puzzle.dimacs"
#define DEFAULT_SAT_PATH OUT_DIR "/sat.txt"
#define DEFAULT_RESULT_PATH OUT_DIR "/result.txt"

#define ENV_GLUCOSE_EXE "SOLVER_GLUCOSE_EXE"

#define OPT_PRINT_HELP "-h"
#define OPT_PRINT_CONFIG "-pc"
#define OPT_PRINT_INPUT "-pi"

typedef struct {

	char* glucose_exe;
	char* puzzle_path;
	char* dimacs_path;
	char* sat_path;
	char* result_path;

	bool print_config;
	bool print_input;

} config;

void check_arguments(int argc, char** argv);
config get_config(int argc, char** argv);
void print_config(config conf);

#endif // INTERFACE_H
