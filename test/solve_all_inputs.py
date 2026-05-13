import os
import subprocess

import __TEST_CONFIG__ 
from __TEST_CONFIG__ import __INIT_TEST__
from __TEST_CONFIG__ import INPUT_DIR
from __TEST_CONFIG__ import PROGRAM

TEST_NAME = "Solve all puzzles"
TEST_DESC = f"Essaye de trouver une solution pour tout les puzzles se trouvant dans le dossier {INPUT_DIR}."
__INIT_TEST__(TEST_NAME, TEST_DESC)

################################################

puzzle_amount   = 0
fail_amount     = 0
solution_amount = 0

puzzle_files = sorted(os.listdir(INPUT_DIR))

for file_name in puzzle_files:

	puzzle_path = os.path.join(INPUT_DIR, file_name)

	r = subprocess.run(
		[PROGRAM, puzzle_path],
		stdout=subprocess.DEVNULL,
		stderr=subprocess.DEVNULL
	)

	rcode = r.returncode
	is_test_ok = rcode in (0, 1, 2)

	print(f" [ {file_name} ] : {'OK ! number of solution =' if is_test_ok else 'FAILED ! return code ='} {rcode}")

	puzzle_amount += 1

	if is_test_ok:
		solution_amount += rcode
	else:
		fail_amount += 1

print()
print("DONE !")
print(f"Runned {puzzle_amount} tests, {fail_amount} failed, {solution_amount} solutions founded !")
