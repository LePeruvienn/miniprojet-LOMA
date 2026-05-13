import os
import subprocess

import __TEST_CONFIG__ 
from __TEST_CONFIG__ import __INIT_TEST__
from __TEST_CONFIG__ import INPUT_DIR
from __TEST_CONFIG__ import OUT_DIR
from __TEST_CONFIG__ import PROGRAM

TEST_NAME = "1 solution"
TEST_DESC = f"Essaye de resoudre un puzzle de variante 1 solution"
__INIT_TEST__(TEST_NAME, TEST_DESC)

################################################

PUZZLE = """#Puzzle
3 3
     
 . . A 
 . . .C
C. . . 
   A
"""

puzzle_path = os.path.join(INPUT_DIR, "puzzle_tmp.data")
with open(puzzle_path, "w", encoding="utf-8") as f:
    f.write(PUZZLE)

result = subprocess.run([PROGRAM, "-pi" ,puzzle_path])

assert result.returncode == 1
print("[OK] Return code valide")

expected = """-1 -2 -3 -4 -5 -6 -7 -8 -9 -10 -11 12 13 -14 -15 -16 17 -18 19 -20 -21 -22 23 -24 -25 -26 27 -28 29 -30 -31 -32 33 34 -35 -36 0
"""
output_path = os.path.join(OUT_DIR, "result.txt")
assert os.path.exists(output_path)
print("[OK] result.txt cree")
with open(output_path, "r", encoding="utf-8") as f:
    content = f.read()
assert content == expected, (
    f"ERREUR Contenu incorrect\n"
)
print("[OK] Content de result.txt bon")

expected2 = """UNSAT
"""
output_path2 = os.path.join(OUT_DIR, "result_2.txt")
assert os.path.exists(output_path2)
print("[OK] result_2.txt cree")
with open(output_path2, "r", encoding="utf-8") as f:
    content = f.read()
assert content == expected2, (
    f"ERREUR Contenu incorrect\n"
)
print("[OK] Content de result_2.txt bon")


print("[OK_ALL] Tous test on reussi")