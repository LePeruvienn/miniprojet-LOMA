import os
import subprocess

################# CONSTANTS #################

TEST_NAME = "Solve all puzzles"
BINARY_NAME = "puzzle_solver"

#################### INIT ####################

script_dir = os.path.dirname(os.path.abspath(__file__))
input_dir  = os.path.abspath(os.path.join(script_dir, "..", "input"))
bin_dir    = os.path.abspath(os.path.join(script_dir, "..", "bin"))

program = os.path.join(bin_dir, BINARY_NAME)

if not os.path.isfile(program):
	print("Couldnt found program binary : " + program)
	print("- Try compiling first.")
	exit(1)

print("Running test : \"" + TEST_NAME + "\"")
print()

#################### TEST ####################

puzzle_amount   = 0
fail_amount     = 0
solution_amount = 0

puzzle_files = sorted(os.listdir(input_dir))

for file_name in puzzle_files:

	puzzle_path = os.path.join(input_dir, file_name)

	r = subprocess.run(
		[program, puzzle_path],
		stdout=subprocess.DEVNULL,
		stderr=subprocess.DEVNULL
	)

	rcode = r.returncode
	is_test_ok = rcode in (0, 1, 2)

	print(f" [ {file_name} ] \t: {'OK !\t number of solution =' if is_test_ok else 'FAILED !\t return code ='} {rcode}")

	puzzle_amount += 1

	if is_test_ok:
		solution_amount += rcode
	else:
		fail_amount += 1

print()
print("DONE !")
print(f"Runned {puzzle_amount} tests, {fail_amount} failed, {solution_amount} solutions founded !")
