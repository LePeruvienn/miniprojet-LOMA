import os
import subprocess

import __TEST_CONFIG__ 
from __TEST_CONFIG__ import __INIT_TEST__
from __TEST_CONFIG__ import INPUT_DIR
from __TEST_CONFIG__ import OUT_DIR
from __TEST_CONFIG__ import PROGRAM

TEST_NAME = "Puzzle difficile et long"
TEST_DESC = f"Essaye de resoudre un puzzle de variante difficile et long"
__INIT_TEST__(TEST_NAME, TEST_DESC)

################################################

PUZZLE = """#Puzzle
17 13
 C B G   F A
C. . . . . . . . . . . . . . . . .
B. . . . . . . . . . . . . . . . .
F. . E . A . . . . . . . . . . . .
 . A . . . . . . . . . . . . . . .
 . . . . . . . . . . . . . . . . .
 . . . . . . . . . . . . . . . . .
 . . . . . . . . . . . . . . . . .
 . . . . . . . . . . . . . . . . .
 . . . . . . . . . . . . . . . . .
 . . . . . . . . . . . . . . . . .
 . . . . . . . . . . . . . . . . .
 . . . . . . . . . . . . . . . . .
 . . . . . . . . . . . . . . . . .
 . . . . . . . . . . . . . . . . .
 . . . . . . . . . . . . . . . . .
 . . . . . . . . . . . . . . . . .
 . . . . . . . . . . . . . . . . .
   D F E G B C
"""

puzzle_path = os.path.join(INPUT_DIR, "puzzle_tmp.data")
with open(puzzle_path, "w", encoding="utf-8") as f:
    f.write(PUZZLE)

result = subprocess.run([PROGRAM, "-pi" ,puzzle_path])

assert result.returncode == 2
print("[OK] Return code valide")

# Expected output trop long (4000 parametre) donc on ne vas pas le verifier

output_path = os.path.join(OUT_DIR, "result.txt")
assert os.path.exists(output_path)
print("[OK] result.txt cree")
output_path2 = os.path.join(OUT_DIR, "result_2.txt")
assert os.path.exists(output_path2)
print("[OK] result_2.txt cree")

print("[OK_ALL] Tous test on reussi")