---
title: CIEL 1 — Évaluation — Gestion des exceptions et structures de données
author: Thomas Le Goff
geometry: margin=1in
---

# CIEL 1 — Évaluation — Gestion des exceptions et structures de données (sujet B)

## Exercice 1 — Calcul du prix des fruits

On considère le programme suivant qui permet d'accéder à un produit dans une liste, d'indiquer la quantité que l'on souhaite acheter et de calculer le prix total.

```python
def get_product_total():
    products = ["pomme", "banane", "orange"]
    products_prices = [2, 4, 5]

    print("Produits disponibles : ", products.join(', '))
    index = int(input("Entrez l'index du produit (0-2) : "))
    quantity = int(input("Entrez la quantité (en KG) : "))

    selected_product = products[index]
    price = products_prices[index]
    total = quantity * price

    print("Produit :", selected_product)
    print("Total :", total, "€")


if __name__ == "__main__":
    get_product_total()
```

\pagebreak{}

### Question 1

Donnez **deux entrées utilisateur différentes** qui provoqueront deux exceptions **différentes** dans ce programme.

Pour chacune :

- indiquer l'entrée utilisateur
- indiquer le nom de l'exception Python correspondante

```



```

### Question 2

Écrivez une version du programme qui **traite les exceptions (les erreurs)** en s'appuyant sur la **la structure `try/except`**.

```python
def get_product_total():




















if __name__ == "__main__":
    get_product_total()
```

### Question 3

Proposez une modification du programme pour éviter de l'incohérence dans la structuration des données.

Indice : demandez-vous qu'elle(s) modification(s) sont nécessaires pour ajouter un fruit et son prix.

```python
def get_product_total():




















if __name__ == "__main__":
    get_product_total()
```

## Exercice 2 - Programmes à compléter (10 points)

Complétez chaque programme pour obtenir la sortie attendue.

### Question 1

```python
fruits = ["pomme", "banane"]
fruits.__________("orange")

print(fruits)
```

**Affichage attendu :**

```
['pomme', 'banane', 'orange']
```

### Question 2

```python
fruits = ["pomme", "banane", "orange"]
fruits.__________(0)

print(fruits)
```

**Affichage attendu :**

```
['banane', 'orange']
```

### Question 3

```python
fruits = ["pomme", "banane"]
fruits = fruits ________ ["kiwi", "mangue"]

print(fruits)
```

**Affichage attendu :**

```
['pomme', 'banane', 'kiwi', 'mangue']
```

### Question 4

```python
fruits = ["pomme", "banane", "orange"]
result = __________(fruits)

print(result)
```

**Affichage attendu :**

```
['banane', 'orange', 'pomme']
```

### Question 5

```python
stock = {"pomme": 5}
stock.__________("banane", 2)

print(stock)
```

**Affichage attendu :**

```
{'pomme': 5, 'banane': 2}
```

### Question 6

```python
stock = {"pomme": 5, "banane": 3, "orange": 2}

total = 0

for fruit in stock:
    total = total ________ stock[fruit]

print(total)
```

**Affichage attendu :**

```
10
```

### Question 7

```python
fruits = ["pomme", "banane", "orange", "kiwi"]

count = 0

for f in fruits:
    if "a" ________ f:
        count += 1

print(count)
```

**Affichage attendu :**

```
2
```

### Question 8

```python
fruits = ["pomme", "banane", "orange", "kiwi"]

result = []

for f in fruits:
    if __________(f) > 5:
        result.__________(f)

print(result)
```

**Affichage attendu :**

```
['banane', 'orange']
```

### Question 9

```python
stock = {"pomme": 5, "banane": 0, "orange": 3}

for fruit in list(stock.keys()):
    if stock[fruit] == 0:
        __________ stock[fruit]

print(stock)
```

**Affichage attendu :**

```
{'pomme': 5, 'orange': 3}
```

### Question 10

```python
fruits = ["pomme", "banane", "kiwi"]

result = {}

for f in fruits:
    result[f] = __________(f)

print(result)
```

**Affichage attendu :**

```
{'pomme': 5, 'banane': 6, 'kiwi': 4}
```