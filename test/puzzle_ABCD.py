import os
import subprocess

import __TEST_CONFIG__ 
from __TEST_CONFIG__ import __INIT_TEST__
from __TEST_CONFIG__ import INPUT_DIR
from __TEST_CONFIG__ import OUT_DIR
from __TEST_CONFIG__ import PROGRAM

TEST_NAME = "Puzzle ABCD"
TEST_DESC = f"Essaye de resoudre un puzzle de variante ABCD"
__INIT_TEST__(TEST_NAME, TEST_DESC)

################################################

PUZZLE = """#Puzzle easy
4 4
 D C B A
D. . . .A
C. . . .B
A. . . .D
B. . . .C
 B A D C
"""

puzzle_path = os.path.join(INPUT_DIR, "puzzle_tmp.data")
with open(puzzle_path, "w", encoding="utf-8") as f:
    f.write(PUZZLE)

result = subprocess.run([PROGRAM, "-pi" ,puzzle_path])

output_path = os.path.join(OUT_DIR, "result.txt")

expected = """-1 -2 -3 -4 -5 -6 -7 -8 -9 -10 -11 -12 -13 -14 -15 -16 -17 -18 -19 20 -21 -22 23 -24 25 -26 -27 -28 -29 30 -31 -32 -33 -34 35 -36 -37 -38 -39 40 -41 42 -43 -44 45 -46 -47 -48 -49 50 -51 -52 53 -54 -55 -56 -57 -58 59 -60 -61 -62 -63 64 65 -66 -67 -68 -69 70 -71 -72 -73 -74 -75 76 -77 -78 79 -80 0
"""

assert result.returncode == 2
print("[OK] Return code valide")

assert os.path.exists(output_path)
print("[OK] Output.txt cree")

with open(output_path, "r", encoding="utf-8") as f:
    content = f.read()

assert content == expected, (
    f"ERREUR Contenu incorrect\n"
)

print("[OK] Content de output.txt bon")