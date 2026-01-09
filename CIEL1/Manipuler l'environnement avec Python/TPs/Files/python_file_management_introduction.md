---
title: CIEL 1 - Gestion des fichiers et du système de fichiers avec Python
author: Thomas Le Goff
geometry: margin=1in
---

## TP 3 - Gestion des fichiers et du système de fichiers avec Python

Ce TP a pour objectif de vous faire découvrir la gestion des fichiers en utilisant la fonction `open` et le module `os`.

---

## Outils à votre disposition

### Liens et références utiles pour ce TP

- [Documentation officielle de `open`](https://docs.python.org/fr/3/tutorial/inputoutput.html#reading-and-writing-files)
- [Documentation officielle du module `os`](https://docs.python.org/fr/3/library/os.html)
- [Tutoriel sur la gestion des fichiers en Python (OpenClassrooms)](https://openclassrooms.com/fr/courses/4464381-demarrez-votre-projet-avec-python/4464421-manipulez-des-fichiers-en-python)
- [Documentation du module `csv`](https://docs.python.org/fr/3/library/csv.html)

### Éditeur de code

Pour ce TP,il n'est pas nécessaire d'utiliser de carte MicroBit, vous pouvez utiliser l'éditeur de votre choix :

- Visual Studio Code
- Geany

\pagebreak

## 1 - Découverte de `open` et de `os`

Ces exercices ont pour objectifs de vous faire découvrir quelques usages courants de `open` et `os`.

### Exercice 1 - Créer et écrire dans un fichier

**Objectif** : Créer un fichier texte et y écrire une phrase.

```python
with open("mon_fichier.txt", "w", encoding="utf-8") as f:
    f.write("Bonjour, je suis un fichier créé avec Python !\n")
```

Questions :

- Que se passe-t-il si le fichier `mon_fichier.txt` existe déjà ?
- Quel est le rôle du paramètre `"w"` dans la fonction `open` ?
- Pourquoi utilise-t-on `encoding="utf-8"` ?
- Que signifie le `\n` à la fin de la phrase ? (essayer de trouver une alternative dans le module `os`)

### Exercice 2 - Lire le contenu d’un fichier

**Objectif** : Lire et afficher le contenu d’un fichier créé précédemment.

```python
with open("mon_fichier.txt", "r", encoding="utf-8") as f:
    contenu = f.read()
    print(contenu)
```

Questions :

- Que se passe-t-il si le fichier `mon_fichier.txt` n’existe pas ?
- Quelle est la différence entre les modes `"w"` et `"r"` ?
- Pourquoi utilise-t-on `with` pour ouvrir le fichier ?

### Exercice 3 - Lire un fichier ligne par ligne

```python
with open("data.txt", "r", encoding="utf-8") as f:
    for ligne in f:
        ligne = ligne.strip()
        print("→", ligne)
```

Lire un fichier ligne par ligne (v2) :

```python
with open("data.txt", "r") as f:
    lignes = f.readlines()
    for ligne in lignes:
        ligne = ligne.strip()
        print("→", ligne)
```

Questions :

- Quelle est la différence entre les deux versions ?
- Pourquoi utilise-t-on `strip()` ?

### Exercice 4 - Ouvrir un fichier et le créer s’il n’existe pas

```python
with open("log.txt", "a", encoding="utf-8") as f:
    f.write("Nouvelle entrée dans le fichier.\n")
```

Questions :

- Quel est le rôle du mode `"a"` ?
- Que se passe-t-il si le fichier `log.txt` n’existe pas ?
- Comment faire pour ajouter une date et une heure à chaque entrée ?

### Exercice 5 - Lire un fichier CSV

```python
with open("donnees.csv", "r", encoding="utf-8") as f:
    for ligne in f:
        cellules = ligne.strip().split(",")
        print(cellules)
```

Encore mieux : le module `csv` :

```python
import csv

with open("donnees.csv", "r", newline="", encoding="utf-8") as f:
    lecteur = csv.reader(f)
    for ligne in lecteur:
        print(ligne)
```

Questions :

- Pourquoi utilise-t-on `newline=""` dans la fonction `open` ?
- Quelle est la différence entre `split(",")` et `csv.reader` ?
- Comment gérer un fichier CSV avec des délimiteurs différents (par exemple, `;`) ?

### Exercice 6 - Charger un fichier par défaut

```python
import os

fichier_principal = "config.txt"
fichier_defaut = "config_default.txt"

if os.path.exists(fichier_principal):
    chemin = fichier_principal
else:
    chemin = fichier_defaut

with open(chemin, "r", encoding="utf-8") as f:
    contenu = f.read()

print(contenu)
```

Questions :

- À quoi sert la fonction `os.path.exists` ?
- Comment modifier ce code pour afficher un message si aucun des deux fichiers n’existe ?
- Comment vérifier si un fichier est vide avant de le lire ?

### Exercice 7 - Passer en majuscule toutes les lignes d’un fichier

```python
with open("entree.txt", "r", encoding="utf-8") as fin:
    with open("sortie.txt", "w", encoding="utf-8") as fout:
        for ligne in fin:
            fout.write(ligne.upper())
```

Questions :

- Pourquoi ouvre-t-on deux fichiers en même temps ?
- Comment faire pour que le fichier de sortie ait le même nom que le fichier d’entrée, mais avec le suffixe `_MAJ` ?
- Comment adapter se code pour réécrire dans `entree.txt` plutôt que dans `sortie.txt` ?

## TODO exercice cumulant chargement d'un fichier et structure de données (JSON => dictionnaire) et (CSV => list /set)
