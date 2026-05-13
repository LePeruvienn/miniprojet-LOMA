# 🧩 Solveur Easy as ABC — Projet LOMA
**Arthur & Maxence — ENSIIE FISA 1A**

Développement un solveur pour les puzzle de type "Easy as ABC".

Consulter le rapport : [Rapport.pdf](https://github.com/LePeruvienn/miniprojet-LOMA/blob/main/Rapport.pdf)

## 📖 Sommaire
1. [Présentation du Projet](#-présentation-du-projet)
2. [Installation et Compilation](#-installation-et-compilation)
3. [Format de Fichier](#-format-de-fichier)
4. [Modélisation SAT du puzzle](#-modélisation-sat-du-puzzle)
5. [Utilisation du Logiciel](#-utilisation-du-logiciel)
6. [Tests Python](#-tests-python)


## 🎯 Présentation du Projet
L'objectif est de résoudre une grille $n \times n$ en plaçant chaque lettre d'un alphabet donné une seule fois par ligne et par colonne.

Le programme respecte les indices de bord qui indiquent la première lettre visible dans une direction donnée.

Le projet traite trois variantes :
- **Basique** : Chaque ligne/colonne est entièrement remplie.
- **Easy(N)** : Avec N cases vide par ligne/colonne.
  - Easy(1), Easy(2), ...


## 🛠️ Installation et Compilation
Le projet utilise **CMake** pour la gestion de la compilation sur Windows, Linux et MacOS.

```bash
# Génération des fichiers de build
cmake -B build

# Compilation
cmake --build build
```

La compilation peut être aussi faite à l'aide du wrapper `MakeFile` qui éxécute les commande de `CMake` à votre place.

```bash
make # Compile le tout
make clean # Efface les fichiers de compilations
```

La compilation peut être aussi faite via l'IDE Visual Studio.


## 📄 Format de Fichier

Nous avons conçu un format spécifique pour définir les puzzle :

```
# Puzzle
5 4
 A C     D
 . . . . .D
B. . . . .
 . . . . .B
 . . . . .C
 . . . . .
   D C
```

- Première ligne : un `#` suivie d'un titre
- Deuxième ligne : nombre qui est la taille du puzzle (ici `5`), suivie par le nombre de lettre par ligne/colonne (ici `4`) avec un espace entre les deux.

Le cotenue du puzzle est marquer d'un carré de points ou de lettres. Ces caractère sont séparer d'un espace entre eux en **ligne uniquement**.

Le contenue du puzzle (carré de caractère) doit être placer à **une distance du 1 espace du bord gauche**.

On peut placer des lettre autour du contenue du puzzle, ou un espace si on veut laisser cette partie du bord vide.

**Toutes les lettre doivent être en majuscule** !

## 🔢 Modélisation SAT du puzzle

### 1. Variables Propositionnelles

Pour chaque case $(i, j)$ de la grille de taille $N \times N$, nous définissons des variables $X_{i,j,\ell}$ :

* $i, j \in \{0, \dots, N-1\}$ (Coordonnées)
* $\ell \in \{0, \dots, K\}$ (Lettre, où $0$ représente une case vide)

### 2. Contraintes Structurelles

#### Lignes et Colonnes

Pour chaque lettre $\ell \in \{1, \dots, K\}$ (sans compté les cases vide donc on commence à 1) :

- **ExactlyOne** : Chaque lettre doit apparaître exactement une fois par ligne et par colonne.

#### Lettre unique par case

Pour chaque case $(i, j)$ :

- **ExactlyOne** : Une case contient exactement une seule valeur parmi $\{L_1, L_2, \dots, L_K\}$ en ajoutant la lettre 0 qui représente un case vide si le puzzle en possède.

### 3. Règles du Jeu

#### Lettres au bord du puzzle

Deux cas se présente :

1. Si il n'y a pas de cases vide possible alors on ajoute juste la variable $X_{ij\ell}$  du bord de l'écran aux clauses.

2. Si il peut avoir des cases vide, on doit créer une règle spécifique pour les cases dans la continuité de la bordure avec $N$ le nombre de cases vides possibles. Pour chaque case $i$ de $0$ à $N$, on ajoute la clause :

$$ (\neg E_{0,j}  \lor \neg E_{1,j} \lor \dots \lor \neg E{i-1} \lor E_{i,j} \lor L_{i,j}) $$

Cette clause garantit que si toutes les cases précédant $i$ sont vides et que la case $i$ n'est pas vide, alors elle contient obligatoirement la lettre $L$.

Pour ce code on rajoute par sécurité, qui est de forcer l'apparition de la lettre dans au moins une des N case près du bord :

$$ (\neg E_{0,j} \lor \neg E_{1,j} \lor \dots \lor \neg E_{i-1,j} \lor E_{i,j} \lor L_{i,j}) $$


#### Lettres Pré-placés

Pour chaque lettre $L$ déjà présente dans la grille initiale à la position $(i, j)$ :

- On ajoute la clause $X_{i,j,L}$ pour forcer le placement de la lettre dans lettre dans le puzzle.


## 🚀 Utilisation du Logiciel

Penser d'abord à bien compiler le programme comme vu ci dessus.

Placer vous à la racine du projet, le binaire compiler se trouve dans le dossier `bin`.

```bash
# Lancer le programme en prenant le puzzle1 comme entrée, [ ] = optionnel
./bin/puzzle_solver [ -option ] input/puzzle1.data [ ... ]
```

Si vous ne lancer pas le programme à la racine du projet, assurer vous d'avoir bien un dossier `out` à l'endroit d'ou vous lancer le programme afin de pouvoir récupérer les fichiers de sorties.

Le programme par défaut créer 3 fichiers dans le dossier `out` :

- `puzzle.dimacs`, `sat.txt` et `result.txt`

### Options

Le programme peut être lancer avec plusieurs arguments qui doivent être placer **AVANT LES ARGUMENTS**, sinon le logiciel ne fonctionnera pas correctement.

Voici les options disponibles :

- `-h` affiche dans le terminal un message d'information sur le fonctionnement du logiciel. *Testez le !*
- `-pc` affiche dans le terminal la configuration actuelle du logiciel. *Testez le !*
- `-pi` affiche dans le terminal le puzzle donner en entrée.

**RAPPEL** : Les options doivent être écrite **AVANT** les arguments !

### Arguments

Voici les arguments dans l'ordre :

1. `puzzle_path` : Chemin vers le puzzle à résoudre. **[ OBLIGATOIRE ]**

2. `puzzle.dimacs` : Chemin vers le fichier de sortie du `.dimacs` du puzzle
3. `sat.txt` : Chemin vers le fichier de sortie du résultat glucose
4. `result.txt` : Chemin vers le fichier de sortie la solution sous format de variable `.dimacs` du puzzle.

### Executable glucose

**⚠️ A LIRE IMPORTANT** 

Le solveur SAT utliser pour ce projet est **glucose**, il est obligatoire de l'avoir installer sur son ordinateur.

Mais un problème récurrent est que l'executable glucose ne possède pas le même chemin de fichier ou commande dans tout les système d'exploitation, il est donc libre à l'utlisateur de définir le sien (la commande par défaut utliser est `glucose`).

Il est alors possible de changer la commande/chemin de fichier vers  l'executable glucose via la variable d'environnement `SOLVER_GLUCOSE_EXE`.


Voici comment vous pouvez la défnir :

```bash
# Linux, souvent la commande glucose est déjà suffisante, donc pas besoin de faire ça
export SOLVER_GLUCOSE_EXE=...
# Exemple
export SOLVER_GLUCOSE_EXE=mon_exe_glucose

# Windows cmd
set SOLVER_GLUCOSE_EXE ...
# Exemple
set SOLVER_GLUCOSE_EXE mon_exe_glucose

# Windows Powershell
$env:SOLVER_GLUCOSE_EXE=""
# Exemples
$env:SOLVER_GLUCOSE_EXE="mon_exe_glucose"
$env:SOLVER_GLUCOSE_EXE="wsl /home/maxence/sat/glucose/simp/glucose" # Utiliser par Maxence sur Windows 11
```

## 🐍 Tests Python

Nous avons mit en place des programmes de tests en python afin d'assurer le fonctionnement du programme.

Tout les tests sont placer dans le dossier `test` du projet, et ils peuvent être lancer de la façon suivante :

```bash
python tests/test_1.py
```

Exemple d'un  test qui essaye de résoudre tout les puzzle qui sont dans le dossier `input`.

```bash
> python test/test_all.py 
Test Name        : Solve all puzzles
Description      : Essaye de trouver une solution pour tout les puzzles se trouvant dans le dossier /home/arthur/ensIIE/pydio/S2/miniprojet-LOMA/input.

 [ puzzle1.data ]       : OK !   number of solution = 0
 [ puzzle2.data ]       : OK !   number of solution = 1
 [ puzzle3.data ]       : OK !   number of solution = 1
 [ puzzle4.data ]       : OK !   number of solution = 1
 [ puzzle5.data ]       : OK !   number of solution = 1
 [ puzzle6.data ]       : OK !   number of solution = 2
 [ puzzle7.data ]       : OK !   number of solution = 2
 [ puzzle8.data ]       : OK !   number of solution = 1
 [ puzzle_tmp.data ]    : OK !   number of solution = 2

DONE !
Runned 9 tests, 0 failed, 11 solutions founded !
```

**IMPORTANT** : Pour que les test marche, lancer les depuis la racine du projet !

---

Merci d'avoir lu ☀️ !
