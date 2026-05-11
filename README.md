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

La compilation peut être aussi faite à l'aide du wrapper `MakeFile` 

## 📄 Format de Fichier (.abc)

Nous avons conçu un format spécifique pour définir les instances du puzzle. Les fichiers doivent suivre cette structure :

```text
6 4          # Taille de la grille (n) | Nombre de lettres
C . . F D A  # Indices Bord Haut (. pour aucun)
B . A . . C  # Indices Bord Bas
. E . . . .  # Indices Bord Gauche
. . . B . .  # Indices Bord Droite
# Grille initiale (. pour vide, lettre pour case fixée)
. . . . . .
. F . . . .
. . . . A .
. . B . . .
. . . . . .
. . . . . .

```

## 🚀 Utilisation

Le logiciel automatise la transformation en DIMACS, l'appel au solveur et l'affichage du résultat.

### Résoudre un puzzle

```bash
./build/puzzle_solver --input instances/grille1.abc

```

### Trouver une deuxième solution

Conformément au sujet, le programme peut chercher une solution alternative en niant la première.

```bash
./build/puzzle_solver --input instances/grille1.abc --all

```

## 🧠 Architecture et Modélisation

* 
**Variables** : Utilisation de variables propositionnelles $X_{ijl}$ pour représenter la présence de la lettre $l$ en $(i, j)$.


* 
**Clauses** : Transformation des contraintes *atleast* et *atmost* en clauses logiques.


* 
**Solveur** : Utilisation de [Glucose/SAT4J/python-sat] pour traiter l'ensemble des clauses.



## 🧪 Tests et Validation

Les tests nécessitent Python et permettent de vérifier les performances sur différentes tailles de grilles.

```bash
python tests/run_tests.py
```
