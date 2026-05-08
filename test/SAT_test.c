#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

    printf("Nombres positifs (%d) : ", taille);
    for (int i = 0; i < taille; i++)
        printf("%d ", liste[i]);
    printf("\n");



    // create puzzle 

    // for each num possitif 
    //      read ligne of problem dot cnf 
    //      get what letter it is 
    //      put the correct letter in puzzle 
    // afficher puzzle 



    fclose(f);
    return 0;
}