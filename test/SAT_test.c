#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <puzzle.h>

int main()
{
    // call glucose with wsl 
    // system("wsl /home/maxence/sat/glucose/simp/glucose ../input/problem.cnf > ../out/satisfaisable.txt ../out/result.txt");

    // read file
    FILE* f = fopen("../out/result.txt", "r");

    if (f == NULL) {
        printf("Erreur fichier\n");
        return 1;
    }

    int* liste = NULL;
    int taille = 0;
    int n; 

    while (fscanf_s(f, "%d", &n) == 1) {
        if (n > 0) {
            int* temp = realloc(liste, (taille + 1) * sizeof(int));

            if (temp != NULL) { // la memoire a bien été aloué sinon warning
                liste = temp;
                liste[taille] = n;
                taille++;
            }
        }
    }

    fclose(f);

    // create puzzle 
    puzzle p = create_puzzle(3);

    // for each num possitif 
    for (int i = 0; i < taille; i++) {
        int v = liste[i] - 1;
        // get what letter it is 
        int lettre = v % 3;
        int cellule = v / 3;
        int ligne = cellule / 3;
        int colonne = cellule % 3;

        // put the correct letter in puzzle 
        insert_letter(p, ligne, colonne, 'A' + lettre);
    }

    // afficher puzzle 
    display_grid(p);

    return 0;
}