#include <stdio.h>
#include <string.h>
#include <puzzle.h>

int main()
{
    puzzle p = load_puzzle("../input/puzzle3.data");

    display_bords(p);
    display_grid(p);
    return 0;
}
