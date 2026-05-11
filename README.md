# 🧩 Solveur Easy as ABC — Projet LOMA
**Arthur & Maxence — ENSIIE FISA 1A**

Développement un solveur pour les puzzle de type "Easy as ABC".

---

## 📖 Sommaire
1. [Présentation du Projet](#présentation-du-projet)
2. [Installation et Compilation](#installation-et-compilation)
3. [Format de Fichier](#format-de-fichier-abc)
4. [Utilisation](#utilisation)
5. [Modélisation CNF](#architecture-et-modélisation)
6. [Tests et Validation](#tests-et-validation)

---

## 🎯 Présentation du Projet
L'objectif est de résoudre une grille $n \times n$ en plaçant chaque lettre d'un alphabet donné une seule fois par ligne et par colonne.

Le programme respecte les indices de bord qui indiquent la première lettre visible dans une direction donnée.

Le projet traite trois variantes :
* **Basique** : Chaque ligne/colonne est entièrement remplie.
* **Easy(N)** : Avec N cases vide par ligne/colonne.
  * Easy(1), Easy(2), ...


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

## 🚀 Utilisation


```bash
usage: [-options] [puzzle.data] | optional, outputed files path: (puzzle.dimacs) (sat.txt) (result.txt)
```

## 🧠 Architecture et Modélisation

* **Variables** : Utilisation de variables propositionnelles $X_{ijl}$ pour représenter la présence de la lettre $l$ en $(i, j)$.


* **Clauses** : Transformation des contraintes *atleast* et *atmost* en clauses logiques.


* **Solveur** : Utilisation de [Glucose/SAT4J/python-sat] pour traiter l'ensemble des clauses.


## 🧪 Tests et Validation

Les tests nécessitent Python et permettent de vérifier les performances sur différentes tailles de grilles.

```bash
python tests/run_tests.py
```
