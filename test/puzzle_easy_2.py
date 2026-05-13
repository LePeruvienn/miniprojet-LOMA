import os
import subprocess

import __TEST_CONFIG__ 
from __TEST_CONFIG__ import __INIT_TEST__
from __TEST_CONFIG__ import INPUT_DIR
from __TEST_CONFIG__ import OUT_DIR
from __TEST_CONFIG__ import PROGRAM

TEST_NAME = "Puzzle easy 2"
TEST_DESC = f"Essaye de resoudre un puzzle de variante easy 2"
__INIT_TEST__(TEST_NAME, TEST_DESC)

################################################

PUZZLE = """#Puzzle easy 2
6 4
 C A A   D B
 . . . . . .B
D. . . . . .C
A. . . . . .
C. . . . . .
 . . . . . .D
 . . . . . .A
 B       C D
"""


puzzle_path = os.path.join(INPUT_DIR, "puzzle_tmp.data")
with open(puzzle_path, "w", encoding="utf-8") as f:
    f.write(PUZZLE)

result = subprocess.run([PROGRAM, "-pi" ,puzzle_path])

assert result.returncode == 1
print("[OK] Return code valide")

expected = """-1 2 -3 4 -5 -6 -7 8 9 -10 -11 -12 13 -14 -15 -16 -17 18 19 -20 -21 -22 23 -24 -25 -26 27 28 -29 -30 -31 -32 -33 -34 35 36 -37 -38 39 -40 -41 -42 -43 -44 -45 -46 47 -48 -49 50 -51 -52 -53 -54 -55 -56 -57 -58 -59 60 61 -62 -63 -64 -65 -66 -67 -68 -69 70 -71 -72 -73 -74 -75 -76 -77 78 -79 -80 -81 82 -83 -84 -85 -86 -87 -88 89 -90 -91 -92 93 -94 -95 -96 -97 98 -99 -100 -101 -102 103 -104 -105 -106 -107 -108 109 -110 -111 -112 -113 -114 -115 -116 -117 -118 -119 120 -121 -122 -123 124 -125 -126 -127 128 -129 -130 -131 -132 -133 -134 -135 -136 137 -138 -139 -140 141 -142 -143 -144 -145 -146 -147 -148 149 -150 151 -152 -153 -154 -155 -156 -157 -158 159 -160 -161 -162 -163 -164 -165 166 -167 -168 -169 -170 -171 -172 -173 174 -175 176 -177 -178 -179 -180 0
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