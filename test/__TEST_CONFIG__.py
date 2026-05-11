import os

################# CONSTANTS #################

BINARY_NAME = "puzzle_solver"

if sys.platform == "win32" or os.name == "nt":
    BINARY_NAME += ".exe"

#################### INIT ####################

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
INPUT_DIR  = os.path.abspath(os.path.join(SCRIPT_DIR, "..", "input"))
BIN_DIR    = os.path.abspath(os.path.join(SCRIPT_DIR, "..", "bin"))
OUT_DIR    = os.path.abspath(os.path.join(SCRIPT_DIR, "..", "out"))

PROGRAM = os.path.join(BIN_DIR, BINARY_NAME)

if not os.path.isfile(PROGRAM):
    print("ERROR: Could not find program binary : " + PROGRAM)
    print("- Try compiling first.")
    exit(1)

def __INIT_TEST__(name, desc):
    print("Test Name\t : " + name)
    print("Description\t : "  + desc)
    print()

