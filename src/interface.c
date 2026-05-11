#include "interface.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_help()
{
	printf("usage: [-options] [puzzle.data] | optional, outputed files path: (puzzle.dimacs) (sat.txt) (result.txt)\n");
	printf("\n- By default all the output files are in the \"%s\" dir (the folder must exist).\n", OUT_DIR);
	printf("\n- All the options must place at the begin of the command :\n");
	printf("  [ -pc ] : prints configuration\n");
	printf("  [ -pi ] : prints input\n");

	char* glucose_exe = getenv(ENV_GLUCOSE_EXE);

	if (glucose_exe == NULL)
	{
		printf("\nglucose executable not set ! You cant set is with the \"%s\" environment variable.\n", ENV_GLUCOSE_EXE);
		printf("- You can use `export %s=...` on linux or `set %s ...` on windows.\n", ENV_GLUCOSE_EXE, ENV_GLUCOSE_EXE);
	}

	printf("\nCurrent glucose executable is : \"%s\"\n",
		(glucose_exe == NULL) ? DEFAULT_GLUCOSE_EXE : glucose_exe);
}

void check_arguments(int argc, char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "ERROR: You must provide at least 1 argument.\n");
		print_help();
		exit(22);
	}
}

config get_config(int argc, char** argv)
{
	config conf;

	char* glucose_exe = getenv(ENV_GLUCOSE_EXE);

	// Set options false by default
	conf.print_config = false;
	conf.print_input = false;

	unsigned int start_index = 0;

	// Getting options
	for (unsigned int i = 1; i < argc; ++i)
	{
		char* opt = argv[i];

		if (strcmp(opt, OPT_PRINT_CONFIG) == 0)
		{
			conf.print_config = true;
			++start_index;
		}
		else if (strcmp(opt, OPT_PRINT_INPUT) == 0)
		{
			conf.print_input = true;
			++start_index;
		}
		else if (strcmp(opt, OPT_PRINT_HELP) == 0)
		{
			print_help();
			exit(20);
		}
		else if (opt[0] == '-')
		{
			fprintf(stderr, "Error: invalid option \'%s\'\n.", opt);
			exit(21);
		}
	}

	int argc_no_opt = argc - start_index;

	check_arguments(argc_no_opt, argv);

	unsigned int puzzle_path_index = 1;
	unsigned int dimacs_path_index = 2;
	unsigned int sat_path_index    = 3;
	unsigned int result_path_index = 4;
	
	conf.glucose_exe  = (glucose_exe == NULL) ? DEFAULT_GLUCOSE_EXE : glucose_exe;

	conf.puzzle_path  = argv[puzzle_path_index + start_index];
	
	conf.dimacs_path  = (argc_no_opt >= dimacs_path_index + 1) ? argv[dimacs_path_index + start_index] : DEFAULT_DIMACS_PATH;
	conf.sat_path     = (argc_no_opt >= sat_path_index    + 1) ? argv[sat_path_index    + start_index] : DEFAULT_SAT_PATH;
	conf.result_path  = (argc_no_opt >= result_path_index + 1) ? argv[result_path_index + start_index] : DEFAULT_RESULT_PATH;

	return conf;
}

void print_config(config conf)
{
	printf(" -------- Solver Configuration -------- \n");
	printf(" - glucose_exe \t: %s\n", conf.glucose_exe);
	printf(" - puzzle_path \t: %s\n", conf.puzzle_path);
	printf(" - dimacs_path \t: %s\n", conf.dimacs_path);
	printf(" - sat_path \t: %s\n", conf.sat_path);
	printf(" - result_path \t: %s\n", conf.result_path);
	printf(" -------------------------------------- \n");
}

