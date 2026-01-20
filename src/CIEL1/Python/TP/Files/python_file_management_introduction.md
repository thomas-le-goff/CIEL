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

Voici deux exercices supplémentaires (8 et 9) axés sur la manipulation du système de fichiers avec le module **`os`** en Python. Ces exercices sont adaptés à des étudiants de BTS CIEL (niveau Licence) et couvrent la création, la suppression, la vérification et la navigation dans les dossiers.

### Exercice 8 - Création et gestion de dossiers

Objectif : Créer une arborescence de dossiers, vérifier leur existence et les supprimer si nécessaire.

#### Énoncé
1. Créez un dossier nommé `mon_super_projet` dans le répertoire courant.
2. À l’intérieur de `mon_super_projet`, créez deux sous-dossiers : `src` et `docs`.
3. Vérifiez que les dossiers ont bien été créés en affichant leur chemin absolu.
4. Supprimez le dossier `docs` et vérifiez qu’il n’existe plus.

#### Code de base à compléter
```python
import os

if not os.path.exists("mon_super_projet"):
    os.mkdir("mon_super_projet")
    print("Dossier 'mon_super_projet' créé.")
else:
    print("Le dossier 'mon_super_projet' existe déjà.")

chemin_src = os.path.join("mon_super_projet", "src")
chemin_docs = os.path.join("mon_super_projet", "docs")

if not os.path.exists(chemin_src):
    os.mkdir(chemin_src)
    print(f"Dossier '{chemin_src}' créé.")

if not os.path.exists(chemin_docs):
    os.mkdir(chemin_docs)
    print(f"Dossier '{chemin_docs}' créé.")

print(f"Chemin absolu de 'src' : {os.path.abspath(chemin_src)}")
print(f"Chemin absolu de 'docs' : {os.path.abspath(chemin_docs)}")

if os.path.exists(chemin_docs):
    os.rmdir(chemin_docs)
    print(f"Dossier '{chemin_docs}' supprimé.")
else:
    print(f"Le dossier '{chemin_docs}' n'existe pas.")
```

#### Questions
- Pourquoi utilise-t-on `os.path.exists` avant de créer un dossier ?
- Quel est le rôle de `os.path.join` ?
- Que se passe-t-il si on essaie de supprimer un dossier non vide avec `os.rmdir` ?
- Comment faire pour supprimer un dossier et tout son contenu (y compris les sous-dossiers et fichiers) ?

### Exercice 9 - Lister et parcourir les fichiers d’un dossier

Objectif : Lister les fichiers et dossiers d’un répertoire, puis déplacer un fichier d’un dossier à un autre.

#### Énoncé
1. Dans le dossier `mon_super_projet`, créez un fichier nommé `fichier_test.txt` avec un contenu quelconque.
2. Listez tous les fichiers et dossiers présents dans `mon_super_projet`.
3. Déplacez le fichier `fichier_test.txt` dans le dossier `src`.
4. Vérifiez que le fichier a bien été déplacé en listant à nouveau le contenu de `mon_super_projet` et de `src`.

#### Code de base à compléter
```python
import os

chemin_fichier = os.path.join("mon_super_projet", "fichier_test.txt")
with open(chemin_fichier, "w", encoding="utf-8") as f:
    f.write("Contenu de test pour le fichier.")

print("Contenu initial de 'mon_super_projet' :")
for element in os.listdir("mon_super_projet"):
    print(f"- {element}")

chemin_destination = os.path.join("mon_super_projet", "src", "fichier_test.txt")
if os.path.exists(chemin_fichier):
    os.rename(chemin_fichier, chemin_destination)
    print(f"Fichier déplacé vers '{chemin_destination}'.")

print("\nContenu de 'mon_super_projet' après déplacement :")
for element in os.listdir("mon_super_projet"):
    print(f"- {element}")

print("\nContenu de 'src' après déplacement :")
for element in os.listdir(os.path.join("mon_super_projet", "src")):
    print(f"- {element}")
```

#### Questions
- Pourquoi utilise-t-on `os.path.join` pour construire les chemins ?
- Quelle est la différence entre `os.listdir` et `os.scandir` ?
- Que se passe-t-il si le fichier de destination existe déjà lors de l’utilisation de `os.rename` ?
- Comment gérer les erreurs si le dossier de destination n’existe pas ?

## TODO exercice cumulant chargement d'un fichier et structure de données (JSON => dictionnaire) et (CSV => list /set)
