#include <stdio.h>
#include <string.h>
#include <puzzle.h>

int main()
{
    FILE* f = fopen("../input/puzzle.data", "r");

    if (f == NULL) {
        printf("Erreur fichier\n");
        return 1;
    }

    char line[100];

    // Read first line
    if (fgets(line, sizeof(line), f) == NULL) {
        printf("Fichier vide\n");
        fclose(f);
        return 1;
    }

    fgets(line, sizeof(line), f);

    int size;

    // read seconde ligne of puzzle (taille)
    int scan = sscanf(line, "%d", &size);

    puzzle p = create_puzzle(size);

    load_top_from_file(p,f);
    load_left_from_file(p, f);
    load_right_from_file(p, f);
    load_bottom_from_file(p, f);
    load_grid_from_file(p, f);

    display_bords(p);
    display_grid(p);


    fclose(f);
    return 0;
}