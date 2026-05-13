import os
import subprocess

import __TEST_CONFIG__ 
from __TEST_CONFIG__ import __INIT_TEST__
from __TEST_CONFIG__ import INPUT_DIR
from __TEST_CONFIG__ import OUT_DIR
from __TEST_CONFIG__ import PROGRAM

TEST_NAME = "0 solution"
TEST_DESC = f"Essaye de resoudre un puzzle de variante avec 0 solution"
__INIT_TEST__(TEST_NAME, TEST_DESC)

################################################

PUZZLE = """#Puzzle
4 4
       B
 . . . .
 . . . .C
C. . A .
A. . . .
   A
"""

puzzle_path = os.path.join(INPUT_DIR, "puzzle_tmp.data")
with open(puzzle_path, "w", encoding="utf-8") as f:
    f.write(PUZZLE)

result = subprocess.run([PROGRAM, "-pi" ,puzzle_path])

assert result.returncode == 0
print("[OK] Return code valide")


expected = """UNSAT
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



print("[OK_ALL] Tous test on reussi")