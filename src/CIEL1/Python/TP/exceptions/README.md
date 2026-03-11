---
title: TP — Découverte des exceptions en Python
author: Thomas Le Goff
geometry: margin=1in
---

# TP — Découverte des exceptions en Python

## Objectif

Dans ce TP, vous allez découvrir comment :

* identifier des exceptions Python
* intercepter des exceptions avec `try/except`
* lever vos propres exceptions avec `raise`
* comprendre la propagation des exceptions
* rendre un programme plus robuste face aux erreurs utilisateur
* rendre un programme plus cohérent pour éviter des erreurs de configuration / évolution

## Exercice 1 — Calcul de moyenne

On considère le programme suivant qui calcule la moyenne de plusieurs notes entrées par l'utilisateur.

```python
def compute_average():
    n = int(input("Combien de notes souhaitez-vous saisir ?"))
    total = 0

    for i in range(n):
        grade = float(input("Entrez une note : "))
        total += grade

    avg = total / n
    print("Moyenne :", avg)


if __name__ == "__main__":
    compute_average()
```

### Question 1

Donnez **deux entrées utilisateur différentes** qui provoqueront deux exceptions **différentes** dans ce programme.

Pour chacune :

* indiquer l’entrée utilisateur
* indiquer le nom de l’exception Python correspondante

### Question 2

Écrire une nouvelle version `compute_average_safe_a()` qui **vérifie les entrées avant d’effectuer les opérations** afin d’éviter les erreurs.

Le programme doit :

* vérifier que `n` est un entier positif
* vérifier que les notes sont des nombres
* afficher un message d’erreur en cas de mauvaise entrée

### Question 3

Écrire une version `compute_average_safe_b()` qui réalise **le même comportement**, mais en utilisant **la structure `try/except`**.

Le programme doit intercepter les exceptions suivantes :

* `ValueError`
* `ZeroDivisionError`


## Exercice 2 — Système de réservation de livres

On souhaite simuler un **terminal de réservation automatique dans une bibliothèque**.

```python
class InvalidUserId(Exception):
    pass

class InvalidBookCode(Exception):
    pass


def get_user_id(book):
    user = input("Entrez votre identifiant d'utilisateur : ")
    if len(user) == 6:
        return {"utilisateur": user}
    else:
        raise InvalidUserId


def get_book_code(book):
    code = input("Confirmez le code du livre : ")
    if code.startswith("BK"):
        return {"code livre": code}
    else:
        raise InvalidBookCode


book_codes = ["BK100", "BK200", "BK300", "BK400", "BK500", "BK666"]

books = {
    "BK100": "Introduction to Python",
    "BK200": "Algorithms and Data Structures",
    "BK300": "Artificial Intelligence Basics",
    "BK400": "C# 10 in a nutshell",
    "BK500": "Introduction to deep learning with Keras and Tensorflow",
    "BK666": "The holy bible"
}

required = {
    "BK100": [get_user_id],
    "BK200": [get_user_id],
    "BK300": [get_user_id, get_book_code],
    "BK400": [get_user_id, get_book_code],
    "BK500": [get_user_id, get_book_code],
    "BK666": [get_user_id, get_book_code]
}


def treat_reservation(book_name, book):
    reservation = {}

    for req in required[book_name]:
        reservation.update(req(book))

    return reservation


def main():
    print("Bienvenue sur le terminal de réservation.")
    print("Quel livre souhaitez-vous réserver ?")

    for b in book_codes:
        print(b, "-", books[b])

    choice = input()

    reservation = treat_reservation(choice, books[choice])

    print("Reservation confirmée : ", reservation)


if __name__ == "__main__":
    main()
```

### Question 1

Ce programme contient plusieurs défauts.

Donnez **deux exemples d’entrées utilisateur** provoquant **deux erreurs différentes** dans le programme.

Pour chaque cas :

* expliquer la cause
* donner le nom de l’exception

### Question 2

Certaines erreurs peuvent, aussi, provenir **de la structure même du programme** et non de l’utilisateur.

> Comprendre par là que le programme n'est peut-être pas bien écrit ... 

Proposez **deux modifications simples du code** qui provoqueraient une exception différente.

Quelques pistes :

* modification d’une clé de dictionnaire
* modification d’un élément d'une liste

> Demandez-vous, par exemple, quelle(s) modification(s) il faudrait apporter pour ajouter un livre au système.

### Question 3

Proposer une **version améliorée du programme** qui gère correctement les cas suivants :

* choix d'un livre inexistant
* utilisation d'un identifiant utilisateur incorrect
* code de livre incorrect (corrigez la fonction `get_book_code`)
* configuration interne incorrecte

Le programme ne doit **jamais se terminer brutalement**, il doit se terminer par un message clair à destination de l'utilisateur final.

# Exercice 3 — Extension du programme

Ajouter une fonction :

```python
def get_library_pin(book):
    # Code à compléter
    pass
```

qui :

* demande un **code PIN de 4 chiffres**
* vérifie que ce code correspond à une constante dans le programme

Si le PIN n’est pas valide, la fonction doit lever une exception :

```python
InvalidPin
```

Ajoutez un livre : 

```python
"BK666": "The holy bible"
```

Dans la liste des livres disponibles et demandez la saisie d'un code pin lors de sa réservation.

> Pour créer votre propre exception appuyez-vous sur la définition de `InvalidUserId` ou `InvalidBookCode`.