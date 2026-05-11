import os

################# CONSTANTS #################

BINARY_NAME = "puzzle_solver"

#################### INIT ####################

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
INPUT_DIR  = os.path.abspath(os.path.join(SCRIPT_DIR, "..", "input"))
BIN_DIR    = os.path.abspath(os.path.join(SCRIPT_DIR, "..", "bin"))

PROGRAM = os.path.join(BIN_DIR, BINARY_NAME)

if not os.path.isfile(PROGRAM):
    print("Couldnt found program binary : " + PROGRAM)
    print("- Try compiling first.")
    exit(1)

def __INIT_TEST__(name):
    print("Running test : \"" + name + "\"")
    print()

