---
title: Python - Gestion des exceptions - BTS CIEL
version: 1.0.0
theme: default
_class: invert
footer: Thomas Le Goff - 2025
header: Python - Gestion des exceptions - BTS CIEL
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

  section.lead h1 {
      text-align: center;
  }
---

# Python - Gestion des exceptions

_BTS CIEL_

![bg right:33%](./img/python_exceptions_cover.png)

---

## Sommaire

- Qu'est-ce qu'une exception ?
- Exception en Python
  - Mot clé `raise`
  - Stacktrace
  - Structure `try` / `except`
  - Structure `else` / `finally` et `with`
  - Exceptions de la librairies standard
  - Exceptions sur-mesure
- Bien gérer les exceptions

![bg right:33%](./img/summary.png)

---

<style scoped>section{font-size:24px;}</style>

## Qu'est-ce qu'une exception ?

### Définition

En programmation, une exception est un **événement inattendu** (non-souhaité) qui a lieu lors de l'execution d'une instruction.

Lorsqu'une exception à lieu, il est généralement préférable de stopper l'execution du programme, mais, dans certains cas il est possible de proposer une alternative est de faire fonctionner l'opération autrement.

---

## Qu'est-ce qu'une exception ?

### Exemples d'exceptions

Lié au code lui-même :

- Manque de validation (ensemble incorrecte)
- Mauvais usage d'une méthode / fonction
- Opération impossible (division par zéro etc.)

Lié à l'environnement d'execution :

- Parser un fichier dans un format incorrect (JSON par exemple)
- Essayer d'écrire dans un fichier alors que le disque est plein
- Communication réseau en hors ligne

---

## Qu'est-ce qu'une exception ?

### Gestion intégrée

Les langages de haut niveau comme Python intègrent des mécanismes de gestion des exceptions, permettant aux développeurs de traiter les erreurs de manière structurée et naturelle, comme une composante essentielle du développement.

Python propose l'utilisation de l'instruction `try` / `except`.

> Loi de Murphy : « Tout ce qui est susceptible de mal tourner tournera mal. »

---

## Qu'est-ce qu'une exception ?

D'autres langages ont une philosophie différente : Il parfois préférable de laisser le programme planter que de créer un problème plus complèxe.

> Voir philosophie **Erlang** "Let It Crash" : https://wiki.c2.com/?DontCatchExceptions

---

## Exceptions en Python

Une exception est une instance de la classe `BaseException`.

Les exceptions qui héritent de `BaseException` sont divisées en deux familles (héritage):

- `Exception` faites pour être gérées (catch)
- les autres comme (qui héritent directement de `BaseException`) comme `KeyboardInterrupt` qui ne sont pas faites pour être gérées

---

## Exceptions en Python

### Mot clé `raise`

Le mot clé `raise` permet de lever une exception.

En levant (emettant) une exception le programme bascule en mode exception jusqu'à ce que l'exception soit "attrapée".

Si l'exception n'est pas attrapée, le programme est terminé en erreur.

---

## Exceptions en Python

### Mot clé `raise`

Le mot clé `raise` est utilisable depuis n'importe quel endroit du programme.

Il est utilisé pour indiquer que l'opération ne se passe pas comme prévue.

```python
raise Exception("voilà une exception")
```

Dans une méthode/fonction :

```python
def est_positif(n: str):
    if n.isnumeric():
        return n > 0
    raise Exception("N doit être un numérique.")
```

---

## Exceptions en Python

### Stacktrace (traceback)

```python
def est_positif(n: str):
    if n.isnumeric():
        return n > 0
    else:
        raise Exception("N doit être un numérique.")

if __name__ == "__main__":
	est_positif("t")
```

```shell
Traceback (most recent call last):
  File "/tmp/est_positif.py", line 7, in <module>
    est_positif("t")
  File "/tmp/est_positif.py", line 4, in est_positif
    raise Exception("N doit être un numérique.")
Exception: N doit être un numérique.
```

---

<style scoped>section{font-size:22px;}</style>

## Exceptions en Python

### Stacktrace (traceback)

```python
def division(a, b):
    return a / b

def calcul():
    return division(10, 0)

if __name__ == "__main__":
	calcul()
```

```shell
Traceback (most recent call last):
  File "/tmp/calcul_exception.py", line 8, in <module>
    calcul()
  File "/tmp/calcul_exception.py", line 5, in calcul
    return division(10, 0)
           ^^^^^^^^^^^^^^^
  File "/tmp/calcul_exception.py", line 2, in division
    return a / b
           ~~^~~
ZeroDivisionError: division by zero
```

---

## Structure `try` / `except`

La structure `try` / `except` permet d'attraper une exception.

Elle doit être placée sur une portion de code bien précise dans laquelle une exception est susceptible de survenir **et que l'on souhaite traiter le cas d'exception**.

> Certains langages comme Java obligent le développeur à traiter les cas d'exception ou préciser explicitement qu'ils sont ignorés. En Python il n'y a aucune obligation.

---

## Structure `try` / `except`

```python
import argparse

def division(a, b):
    return a / b

if __name__ == "__main__":
    args = argparse.ArgumentParser()
    args.add_argument("a", type=float)
    args.add_argument("b", type=float)
    a, b = args.parse_args().a, args.parse_args().b

    try:
        result = division(a, b)
    except ZeroDivisionError:
        result = 0
        print("Attention : division par zéro détectée. Résultat forcé à 0.")

    print(f"Résultat : {result}")
```

---

<style scoped>section{font-size:22px;}</style>

## Structure `try` / `except`

```python
import argparse

def division(a, b):
    try:
        return a / b
    except ZeroDivisionError:
        return 0

if __name__ == "__main__":
    # ...
    try:
        # L'exception ne sera jamais levée car déjà gérée dans la fonction division
        result = division(a, b)
    except ZeroDivisionError:
        result = 10 # Valeur par défaut 

    print(f"Résultat : {result}")
```

> Il est souvent préférable de laisser l'exception s'échapper pour ne pas alterer d'autre éléments du programme qui appelerait une fonction. Si on ne sait pas vraiment quoi faire d'une erreur c'est qu'il n'y a surement rien à faire !

---

## Structure `try` / `catch`

### Gérer plusieurs exceptions

```python
import sys

try:
    f = open('myfile.txt') # OSError possible
    s = f.readline()
    i = int(s.strip()) # ValueError possible
except OSError as err:
    print("OS error:", err)
except ValueError:
    print("Could not convert data to an integer.")
except Exception as err:
    print(f"Unexpected {err=}, {type(err)=}")
    raise
```

--- 
<!-- _class: lead -->

# Exercices

![bg right:50%](./img/exercices.png)

---

## Bien gérer les exceptions

- Est-ce qu'un pattern `with` standard est associé avec l'objet / méthode que j'utilise ?
- Est-ce que la méthode/fonction appelée est susceptible de générer des exceptions (voir la documentation) ?
- Suis-je capable de traiter le cas d'exception ? 
- Est-ce nécessaire de donner plus d'information à l'utilisateur (faut-il spécialiser l'exception)  