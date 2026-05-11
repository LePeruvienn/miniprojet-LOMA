import os
import subprocess

import __TEST_CONFIG__ 
from __TEST_CONFIG__ import __INIT_TEST__
from __TEST_CONFIG__ import INPUT_DIR
from __TEST_CONFIG__ import PROGRAM

TEST_NAME = "Puzzle Basique"
TEST_DESC = f"Essaye de résoudre un puzzle de variante basique"
__INIT_TEST__(TEST_NAME, TEST_DESC)

################################################

PUZZLE = """# Puzzle Basique
6 6
   C   F D A
 . . . . . .A
E. . . . . . 
A. . . . . .E
D. . . . . .B
F. . . . . .D
 . . . . . .F
 C   A B   F
"""

puzzle_path = os.path.join(INPUT_DIR, "puzzle_tmp.data")
with open(puzzle_path, "w", encoding="utf-8") as f:
    f.write(PUZZLE)

subprocess.run([PROGRAM, "-pi" ,puzzle_path])
