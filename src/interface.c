#include "interface.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void check_arguments(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("ERROR: You must provide at least 1 argument.\n");
		printf("usage: [puzzle.data] | optional, outputed files path: (puzzle.dimacs) (sat.txt) (result.txt)\n");
		printf("- By default all the output files are in the \"%s\" dir (the folder must exist).\n", TMP_DIR);
	
		char* glucose_exe = getenv(ENV_GLUCOSE_EXE);

		if (glucose_exe == NULL)
		{
			printf("\nglucose executable not set ! You cant set is with the \"%s\" environment variable.\n", ENV_GLUCOSE_EXE);
			printf("- You can use `export %s=...` on linux or `set %s ...` on windows.\n", ENV_GLUCOSE_EXE, ENV_GLUCOSE_EXE);
		}

		printf("\nCurrent glucose executable is : \"%s\"\n",
			(glucose_exe == NULL) ? DEFAULT_GLUCOSE_EXE : glucose_exe);

		exit(1);
	}
}

config get_config(int argc, char** argv)
{
	check_arguments(argc, argv);

	config conf;

	char* glucose_exe = getenv(ENV_GLUCOSE_EXE);
	
	conf.glucose_exe = (glucose_exe == NULL) ? DEFAULT_GLUCOSE_EXE : glucose_exe;
	conf.puzzle_path  = argv[1];
	conf.dimacs_path  = (argc == 3) ? argv[2] : DEFAULT_DIMACS_PATH;
	conf.sat_path = (argc == 4) ? argv[3] : DEFAULT_SAT_PATH;
	conf.result_path  = (argc == 5) ? argv[4] : DEFAULT_RESULT_PATH;

	conf.print_config = false;
	conf.print_input = false;

	for (unsigned int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], OPT_PRINT_CONFIG) == 0)
		{
			conf.print_config = true;
		}
		if (strcmp(argv[i], OPT_PRINT_INPUT) == 0)
		{
			conf.print_input = true;
		}
	}

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

