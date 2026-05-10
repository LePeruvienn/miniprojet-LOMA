#ifndef INTERFACE_H
#define INTERFACE_H

#define TMP_DIR "tmp"
#define DEFAULT_GLUCOSE_EXE "glucose"
#define DEFAULT_DIMACS_PATH TMP_DIR "/puzzle.dimacs"
#define DEFAULT_SAT_PATH TMP_DIR "/sat.txt"
#define DEFAULT_RESULT_PATH TMP_DIR "/result.txt"
#define ENV_GLUCOSE_EXE "SOLVER_GLUCOSE_EXE"

typedef struct {

	char* glucose_exe;
	char* puzzle_path;
	char* dimacs_path;
	char* sat_path;
	char* result_path;

} config;

void check_arguments(int argc, char** argv);
config get_config(int argc, char** argv);
void print_config(config conf);

#endif // INTERFACE_H
