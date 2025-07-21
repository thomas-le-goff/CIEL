---
title: Python Introduction - BTS CIEL
version: 1.0.0
theme: default
_class: invert
footer: Thomas Le Goff - 2025
header: Python Introduction - BTS CIEL
paginate: true
marp: true
style: |
    section {
      font-size: 1.6em;
    }

    img[alt~="center"] {
        display: block;
        margin: 0 auto;
      }
---

# Introduction au langage Python

*BTS CIEL*

![bg right right:33%]](./img/python_introduction_cover.png)

---

## Sommaire

- Pourquoi apprendre Python ?
- Programmation structurée
    - Instructions, variables et blocs
    - Séquence
    - Sélection
    - Itération
- Documentation et références
- Environnement de développement
- Exercices

![bg right right:33%]](./img/summary.png)

---

# Pourquoi apprendre Python ?

- 🧰 Généraliste :
    - Web : Django, Flask
    - IA et data : Numpy, Panda, PyTorch
    - Administration Système : cross-platform, pré-installé sur Linux, interprété
    - Programmation embarqué : MicroPython, CircuitPython, MicroBit
    - Facilité d'interfacage avec le langage C
- 🌱 Facile à apprendre (choisi par l'éducation nationale)
    - Syntaxe allégé pour se concentrer sur la logique
- 👷‍♀️ Populaire dans les milieux professionel et scolaire :
    - N°1 sur l'Index [Tiobe (27% des parts)](https://www.tiobe.com/tiobe-index/) et
      sur [PYPL (31%)](https://pypl.github.io/PYPL.html)

---

# Langage interprété

---

# Programmation structurée

La programmation structurée définie les primitives suivantes

- 🔽 La séquence
- 🔀 La sélection
- 🔁 L'itération

![w:880 center](./img/structured_programming_primitives.png)

---

# 🔽 Séquence - variable

```python
ma_variable = 10  # integer
mon_autre_variable = "du texte"  # string
mon_bool = True  # boolean
```
---

# 🔽 Séquence - typage

Types natifs du langage :
- Numériques `int`, `float`, `complex`
- Séquences
- Dictionnaires
- Classes, instancess et exceptions ()

> ℹ️ Natif signifie qu'ils sont fourni par l'interpréteur Python.

> ℹ️ D'autres types peuvent être fournis par des bibliothèques (Numpy, Panda, etc.)

---

# 🔽 Séquence - typage

Python utilise un typage dit **dynamique** et **strique**.

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

> ⚠️ En Python l'erreur sera levée lors de l'exécution du programme

---

# 🔽 Séquence - typage

`Définition`

__Typage Dynamique / statique__
Est-ce qu'une variable de type **A** peut contenir une valeur de type **B** sans être rédéfinie.

__Typage faible / fort__
Est-ce qu'une variable de type **A** peut-être utilisée en tant que type **B** (sans cast explicite)

---

# 🔽 Séquence - opérations mathématiques

Python défini trois types numériques : `int`, `float`, `complexe`

| Opération | Définition                |
|-----------|---------------------------|
| `x + y`   | somme de x et y           |
| `x - y`   | différence de x et y      |
| `x * y`   | produit de x et y         |
| `x / y`   | quotient de x et y        |
| `x // y`  | quotient entier de x et y |
| `x % y`   | reste de x / y            |
| `-x`      | négatif de x              |

---

# 🔽 Séquence - instruction et bloc

```python
```

---

# 🔽 Séquence - appel de fonction

```python
print("Hello world !")
le_max = max(10, 15)
```

---

# 🔀 Sélection - if / elif / else

```python
ma_variable = 10
if ma_variable == 11:
    print("foo")
elif ma_variable == 12:
    print("or")
else:
    print("bar")
```

---

# 🔀 Sélection - opérations de comparaison

| Opération | Définition              |
|-----------|-------------------------|
| `<`       | strictement inférieur   |
| `<=`      | inférieur ou égal       |
| `>`       | strictement supérieur   |
| `>=`      | supérieur ou égal       |
| `==`      | égal                    |
| `!=`      | différent               |
| `is`      | identité d'objet        |
| `is not`  | contraire de l'identité |

---
# 🔀 Sélection - véridicité des types

Considérés comme étant **faux** :
- Les constantes `None` et `False`
- zéro de tout type numérique : `0`, `0.0`, `0j`
- les chaînes et collections vides : `''`, `()`, `[]`, `{}`

Tout le reste est considéré comme étant **vrai**.

---

# 🔀 Sélection - opérations booléennes

| Opération | Définition                                |
|-----------|-------------------------------------------|
| `x or y`  | si x est vrai alors x, sinon y            |
| `x and y` | si x est faux, alors x sinon y            |
| `not x`   | si x est faux, alors `True` sinon `False` |

---

# 🔀 Sélection - pattern matching

```python
match status:
    case 400:
        print("Bad request")
    case 404:
        print("Not found")
    case 418:
        print("I'm a teapot")
    # Cas par défaut
    case _:
        print("Code erreur inconnu")
```

---

# 🔀 Sélection - pattern matching

```python
match point:
    case (0, 0):
        print("Origin")
    case (0, y):
        print(f"Y={y}")
    case (x, 0):
        print(f"X={x}")
    case (x, y):
        print(f"X={x}, Y={y}")
```

---

# 🔁 Itération - while loop

```python
i = 0

while i < 10:
    print(i)
    i += 1

# Résultat: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9

animals = ["chien", "chat", "souris"]
i = 0

while i < 3:
    print(animals[i])
    i += 1

# Résultat: "chien", "chat", "souris"
```

---

# 🔁 Itération - for loop

```python
animals = ["chien", "chat", "souris"]

for animal in animals:
    print(animal)

# Résultat: "chien", "chat", "souris"
```

---


# 🔁 Itération - fonction range

```python
ma_liste = list(range(5, 10))
# [5, 6, 7, 8, 9]

for e in ma_liste:
    print(e)

# Résultatet: 5, 6, 7, 8, 9

for i in range(1, 10):
    print(i)

# Résultat: 1, 2, 3, 4, 5, 6, 7, 8, 9
```

---

# Env de développement - versions de Python

Pour connaître la version de python (3) installée

```shell
python3 --version
```

![center](img/python_version_table_2025.png)

---

# Env - éditeurs

- Visual Studio Code
    - Python
    - Python Debugger
- PyCharm
- Qt Creator
- Mu et Micro:bit Python Editor

![bg right](./img/editors.png)