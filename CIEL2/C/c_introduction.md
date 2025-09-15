---
title: Langage C introduction - BTS CIEL
version: 1.0.0
theme: default
_class: invert
footer: Thomas Le Goff - 2025
header: Langage C introduction - BTS CIEL
paginate: true
marp: true
style: |-
  section {
    font-size: 1.6em;
  }

  img[alt~="center"] {
      display: block;
      margin: 0 auto;
    }
---

# Introduction au langage C

_BTS CIEL_

![bg right right:33%](./img/cover.png)

--------------------------------------------------------------------------------

## Sommaire

- Langage compilé
- Programmation structurée

  - Instructions, variables et blocs
  - Séquence
  - Sélection
  - Itération

- Pointeurs

- Exercices

![bg right right:33%](./img/summary.png)

--------------------------------------------------------------------------------

## Langage compilé

--------------------------------------------------------------------------------

## Programmation structurée

La programmation structurée définit les primitives suivantes

- 🔽 La séquence
- 🔀 La sélection
- 🔁 L'itération

![w:880 center](./img/structured_programming_primitives.png)

--------------------------------------------------------------------------------

## 🔽 Séquence - variable

```c
int ma_variable = 10  // integer
char * mon_autre_variable = "du texte"  // char *
bool mon_bool = true  // boolean

int ma_variable; // Attention, comportement non prédictible si non initialisé
```

--------------------------------------------------------------------------------

## 🔽 Séquence - typage

Types fondamentaux :

- Numériques entiers : (et variantes `signed` / `unsigned`)

  - `short` (16 bits)
  - `int` (32 bits)
  - `long` (32/64 bits)

- Numériques réels : `float`, `double`, `long double`

- Caractères : `char` (`char *`)

Structures de données :

- Tableaux : `int tab[10];`
- Structures : `struct`

> ℹ️ Ces types sont directement supportés par le langage C (sans bibliothèques externes).

--------------------------------------------------------------------------------

## 🔽 Séquence - typage

Python utilise un typage dit **dynamique** et **strict**.

```python
points = 3.2  # points est du type float
print("Tu as " + points + " points !")  # Génère une erreur de typage

points = int(points)  # points est maintenant du type int (entier), sa valeur est arrondie à l'unité inférieure (ici 3)
print("Tu as " + points + " points !")  # Génère une erreur de typage

print("Tu as " + str(points) + " points !")  # Plus d'erreur de typage, affiche 'Tu as 3 points !'
```

Le C utilise un typage dit **statique** et **faible**.

```c
float points = 3.2; // Typage statique : points est un float
points = (int) points; // Erreur points est de type float elle ne peut pas recevoir un int

int pts = (int) points; // Conversion explicite : float → int
printf("Tu as %s points !\n", pts); // Typage faible : conversion implicite
```

> ⚠️ En C l'erreur sera levée lors de la compilation du programme.

--------------------------------------------------------------------------------

## 🔽 Séquence - typage

`Définition`

**Typage Dynamique / statique** Est-ce qu'une variable de type **A** peut contenir une valeur de type **B** sans être redéfinie.

**Typage faible / fort** Est-ce qu'une variable de type **A** peut-être utilisée en tant que type **B** (sans cast explicite)

--------------------------------------------------------------------------------

## 🔽 Séquence - opérations mathématiques

En C, les types numériques de base sont :

- `int` (entier)
- `float` (réel simple précision)
- `double` (réel double précision)

Opération | Définition
--------- | -----------------------------------------
`x + y`   | somme de x et y
`x - y`   | différence de x et y
`x * y`   | produit de x et y
`x / y`   | quotient de x et y
`x % y`   | reste de la division (entiers uniquement)
`-x`      | opposé de x

--------------------------------------------------------------------------------

## 🔽 Séquence - instruction et bloc

```c
int x = 10;
{
    int y = 5;
    printf("%d\n", x + y);
}
return 0;
```

--------------------------------------------------------------------------------

## 🔽 Séquence - appel de fonction

```c
printf("Hello world !\n");

int a = 10, b = 15;
int le_max = (a > b) ? a : b;
printf("Max = %d\n", le_max);

double r = sqrt(16.0);
printf("Racine carrée = %.2f\n", r);
```

--------------------------------------------------------------------------------

## 🔀 Sélection - if / else if / else

```c
int ma_variable = 10;

if (ma_variable == 11) {
    printf("foo\n");
} else if (ma_variable == 12) {
    printf("or\n");
} else {
    printf("bar\n");
}

return 0;
```

--------------------------------------------------------------------------------

## 🔀 Sélection - opérations de comparaison

Opération | Définition
--------- | ---------------------
`<`       | strictement inférieur
`<=`      | inférieur ou égal
`>`       | strictement supérieur
`>=`      | supérieur ou égal
`==`      | égal
`!=`      | différent

> ⚠️ Pas d'opérateur `is` en C. On compare les adresses mémoire pour les pointeurs (`ptr1 == ptr2`).

--------------------------------------------------------------------------------

## 🔀 Sélection - véridicité des valeurs

En C :

- `0` (zéro) est considéré comme **faux**.
- Toute autre valeur entière est **vraie**.

```c
if (0) {
    printf("faux\n");
}
if (42) {
    printf("vrai\n");
}
```

--------------------------------------------------------------------------------

## 🔀 Sélection - opérations booléennes

Opération | Définition
--------- | -------------------------
`x \      | \                         | y` | vrai si x ou y est vrai
`x && y`  | vrai si x et y sont vrais
`!x`      | vrai si x est faux

--------------------------------------------------------------------------------

## 🔀 Sélection - switch / case

```c
int status = 404;

switch (status) {
    case 400:
        printf("Bad request\n");
        break;
    case 404:
        printf("Not found\n");
        break;
    case 418:
        printf("I'm a teapot\n");
        break;
    default:
        printf("Code erreur inconnu\n");
}
```

--------------------------------------------------------------------------------

## 🔁 Itération - while loop

```c
#include <stdio.h>

int main(void) {
    int i = 0;

    while (i < 10) {
        printf("%d\n", i);
        i++;
    }

    char *animals[] = {"chien", "chat", "souris"};
    i = 0;
    while (i < 3) {
        printf("%s\n", animals[i]);
        i++;
    }

    return 0;
}
```

--------------------------------------------------------------------------------

## 🔁 Itération - for loop

```c
char *animals[] = {"chien", "chat", "souris"};

for (int i = 0; i < 3; i++) {
    printf("%s\n", animals[i]);
}

return 0;
```

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Les tableaux en C

Un **tableau** est une zone mémoire contiguë contenant plusieurs éléments du **même type**.

```c
int tab1[5];               
int tab2[5] = {0};         
int tab3[5] = {1, 2, 3};
int tab4[]  = {10, 20, 30};

printf("%d\n", tab3[0]);
printf("%d\n", tab4[2]);
```

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Les tableaux en C

### Dimension d'un tableau

La dimension d'un tableau (sa taille) doit être une valeur **constante**.

```c
#define N 5

// Valide
int tab1[5]; // Valide
int tab2[N]; // Valide

// Invalide
int n = 5;
int tab3[n];

const int s = 5;
int tab4[s]; // Sauf en C99 (dans un contexte local) !
```

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Les tableaux en C

### Dimension d'un tableau

Dans une fonction :

```c
void ma_fonction(int n) {
    int tab[n];
}
```

> ℹ️ Ce principe est appelé **V**ariable **L**ength **A**rray.

> ⚠️ Le tableau sera alloué sur la pile.

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Les tableaux en C

### Calculer la taille d'un tableau

`sizeof()` permet d'obtenir l'espace mémoire occupé par un élément.

```c
int tab[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

printf("Taille mémoire occupée : %zu", sizeof(tab)) // 4 octets * 10 => 40 octets
printf("Taille du tableau (dimension) : %zu", sizeof(tab) / sizeof(int)) // 4 octets * 10 / 4 octets => 10
```

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Les tableaux en C

### Multi-indice

```c
int matrice[3][4] = {{0, 1, 3, 4}, {0, 1, 3, 4}, {0, 1, 3, 4}}
```

Exemples d'utilisation :

- Pixels d'une image
- Plateau d'un jeu d'échecs
- Algèbre linéaire
- Données tabulaires (classeur)

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Chaînes de caractères

### null-terminated

Une chaîne de caractères (`string`) peut-être représentée en utilisant un tableau de `char`.

```c
char chaine[] = "BTS";
```

Les chaînes de caractères se manipulent donc comme des tableaux.

> ℹ️ Le langage ajoute lui-même le caractère de fin de chaîne `\0`. La taille mémoire réelle utilisée par la variable est de `3 + 1 = 4 octets`

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Chaînes de caractères

### string.h

La bibliothèque `string.h` définit des fonctions permettant de manipuler les chaînes de caractères.

```c
#include <string.h>

size_t length = strlen("ma chaine de caractères");

printf("la chaîne est de taille : %zu \n", length); // 24
```

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Chaînes de caractères

### string.h

Fonction                              | Définition
------------------------------------- | ----------------------------------------------------------
`char * strcat(char * s1, char * s2)` | concaténation de `s1` et `s2`                              |
`char * strchr(char * s1, int c)`     | recherche un caractère `c` dans `s1`                       |
`int strcmp(char *s1, char *s2)`      | `-1` si `s1` est < `s2`, `1` si `s2` est > `s1`, `0` sinon |
`char *strcpy(char * s1, char *s2)`   | copie `s2` dans `s1` (attention **buffer overflow**)       |
`size_t strlen(char *s)`              | nombre d'octets qui composent la chaîne                    |

> ℹ️ Plus de détails ici : <https://en.wikibooks.org/wiki/C_Programming/String_manipulation>

> ⚠️ Ces fonctions ont des comportements particuliers, bien lire la documentation.

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Chaînes de caractères

### string.h

Les fonctions de `string.h` sont écrites pour l'encodage ASCII (ISO-8859-1).

Si vous souhaitez manipuler d'autres types d'encodage `wchar.h` est plus adapté.

> ℹ️ Table de référence de ISO-8859-1 <https://fr.wikipedia.org/wiki/ISO/CEI_8859-1>

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Les pointeurs en C

Un pointeur est une variable qui contient **l'adresse mémoire** d'une autre variable.

```c
#include <stdio.h>

int main(void) {
    int valeur = 42;
    int *ptr = &valeur;

    printf("Adresse = %p\n", ptr);
    printf("Valeur via ptr = %d\n", *ptr);

    *ptr = 99;
    printf("Nouvelle valeur = %d\n", valeur);

    return 0;
}
```

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Les pointeurs en C

### Incrémentation de pointeur

L'incrémentation d'un pointeur permet de le décaler de la taille mémoire du type de la variable pointée.

```c
int b = 10;
int *a = &b;

// Incrémente la valeur de b de 1
(*a)++; 

// Incrémente l'adresse de sizeof(int) (car il s'agit d'un pointeur vers un int)
a++;

// a contient désormais l'adresse de l'entier qui suit b
```

> ⚠️ Attention à la priorité de l'opérateur * 

## ![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Les pointeurs en C

- déclaration d'un pointeur : `type *ptr;`
- récupérer l'adresse d'une variable `var` : `&var;`
- déréférencement (accède à la valeur pointée) : `*ptr`

Les pointeurs permettent :

- de manipuler des **tableaux** et des **chaînes**
- de gérer la **mémoire dynamique** (`malloc`, `free`)
- de passer des paramètres **par adresse** aux fonctions

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Exercice 1 - copier une chaîne

```c
#include <stdio.h>

int main(void) {
    const char msg[] = "Hello";

    char copie[_];

    int i = 0;

    while (___________) {
        copie[i] = _______;
        i++;
    }
    copie[i] = _______;

    printf("%s\n", copie);
    return 0;
}
```

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Exercice 2 - échange avec des pointeurs

```c
#include <stdio.h>

int main(void) {
    int x = 42;
    int y = 12;

    echange(__, __);

    printf("Valeur de x = %d\n", x);
    printf("Valeur de y = %p\n", y);

    return 0;
}

void echange(___ _x, ___ _y)
{
    int temp = __;
    _x = _y;
    _y = temp;
}
```

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Exercice 3 - tableau ou pointeur ?

```c
#include <stdio.h>

int main(void) {
    int tab[3] = {10, 20, 30};
    int *p = ____;

    for (int i = 0; i < 3; i++) {
        printf("%d\n", ____);
        ___;
    }
    return 0;
}
```

![bg cover opacity:10%](./img/background.jpg)

--------------------------------------------------------------------------------

## Exercice 4 - recherche du plus grand

```c
#include <stdio.h>
#include <limits.h>

int main(void) {
    int tab[] = {0, -6, 8, 10, 20, 30, 400};
    int max = ______;
    int maxPos = -1;

    for (int i = _____; i < _____; i++) {



        if (_____________) {
            max = ____;
        }


    }

    printf("Max : %d à la position : %d", max, maxPos);

    return 0;
}
```

![bg cover opacity:10%](./img/background.jpg)
