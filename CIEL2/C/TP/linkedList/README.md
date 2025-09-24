# CIEL2 - TP structure en langage C : implémentation d'une liste chaînée

![](img/linked-list.png)

## Avant de commencer

L'objectif de ce TP est de vous faire implémenter une liste chaînée en utilisant les structures et des fonctions associées.

### Liste chaînée

La liste chaînée est une structure de données fondamentale en informatique, souvent utilisée dans l'implémentation d'autres structures de données.<br>
C'est une liste de « nœuds », où chaque nœud est lié à son ou ses voisins forment ainsi une chaîne.

Dans une **liste simplement chaînée**, chaque nœud est uniquement relié au nœud qui le suit.<br>
Dans une **liste doublement chaînée**, chaque nœud est relié à la fois au nœud qui le précède et à celui qui le suit.

![](https://upload.wikimedia.org/wikipedia/commons/2/26/Liste_doublement_cha%C3%AEn%C3%A9e.png)

Si vous voulez approfondir les listes chaînées, consultez [cet article][intro-linked-list], qui les explique à l'aide de jolis schémas.

### Fichiers du projet

- Les déclarations à implémenter sont dans le fichier `linked_list.h` et votre code doit être écrit dans le fichier `linked_list.c`
- le fichier `make` contient les instructions pour construire le projet (compilation + exécution des tests)
- `test_linked_list.c` contient le jeu de test

### Tests unitaires avec Unity

Un jeu de tests unitaires correspondant aux spécifications a été rédigé pour vous permettre de valider le bon fonctionnement de votre programme (fichier `test_linked_list.c`).

Dans ce fichier chaque fonction correspond à un cas de test. Appuyez-vous sur son contenu pour concevoir et comprendre les attentes envers votre système (principe du TDD).

Les tests peuvent être exécutés via la commande suivante :

```shell
make test
```

Certains tests sont pour le moment ignorés (pour vous permettre d'implémenter chaque fonction petit à petit) ; pour activer plus de tests vous pouvez supprimer les appels `TEST_IGNORE()` dans le fichier `test_linked_list.c`.

[Plus de détails concernant le framework de test Unity](https://www.throwtheswitch.org/unity)

## Introduction

Vous travaillez sur un projet visant à développer un système de planification des trains pour un réseau ferroviaire très fréquenté.

On vous demande de développer le système de gestion des itinéraires de train.

Chaque itinéraire est constitué d'une **séquence de gares où un train donné s'arrête**.

## Instructions

### Spécifications fonctionnelles

Votre équipe a décidé d'utiliser une **liste doublement chaînée** pour représenter chaque itinéraire.

Le système doit suivre la spécification suivante :

- Chaque gare le long du trajet du train sera représentée par **un nœud de la liste chaînée**.

- Vous n'avez pas besoin de vous soucier des heures d'arrivée et de départ aux gares.

- Chaque gare **sera simplement représentée par un numéro**.

- Les itinéraires peuvent être prolongés, en ajoutant des gares au début ou à la fin du trajet.

- Ils peuvent également être raccourcis en retirant des gares au début ou à la fin du trajet.

- Parfois, une gare ferme, et dans ce cas elle doit être retirée de l'itinéraire, même si elle ne se trouve pas au début ou à la fin.

- La taille d'un itinéraire se mesure non pas en distance parcourue, mais par le nombre de gares desservies.

### 1 - Formalisation du problème

**1.1** ✍️ lisez le jeu de test `test_linked_list` et le fichier `linked_list.h` et donnez l'état de la liste après les opérations suivantes :

```c
struct list *list = list_create();

list_push(list, 1);
list_push(list, 2);
list_pop(list);
list_push(list, 3);
list_shift(list);
list_unshift(list, 4);
list_push(list, 5);
list_pop(list);
list_shift(list);
```

**1.2** ✍️ à partir de la spécification fonctionnelle et des autres éléments à votre disposition détaillez les éléments à mettre en place. _Donnez la/les structure(s), fonction(s) et ou procédure(s) nécessaire(s)_.

### 2 - Développement TDD

**2.1** 💻 En utilisant le principe de TDD (**T**est **D**riven **D**evelopment) implémentez les fonctions `list_create`,`list_push`, `list_pop` et `list_destroy` en vous inspirant des fonctions déjà implémentées `list_unshift`, `list_shift` et `list_delete`.

### 3 - From **int** to **station**

**3.1** ✍️ La liste chaînée actuellement implémentée permet de stocker uniquement des entiers or nous voulons stocker des `gares` proposez la modification.

**3.2** 💻 Adaptez le programme.

### Contraintes

Votre programme doit être écrit en suivante les recommandations de l'ANSSI (en terme de sécurité et qualité de code).

- <https://cyber.gouv.fr/publications/regles-de-programmation-pour-le-developpement-securise-de-logiciels-en-langage-c> (nous verrons cela en détail plus tard 😉)

Le fichier `makefile` est configuré pour approcher au maximum les contraintes et recommandations du document.

### Aides

Dans le cas d'une erreur se terminant par un message `Abandon (core dump créé)` il est possible d'analyser le dump en utilisant l'utilitaire gdb :

Lister les fichiers dumps :

```shell
coredumpctl list
```

En ouvrir un avec GDB :

```shell
coredumpctl gdb <PID>
```

[Cheatsheet GDB](https://darkdust.net/files/GDB%20Cheat%20Sheet.pdf)

## Crédits

Cet exercice provient de la plateforme [exercism.org](https://exercism.org/).

[intro-linked-list]: https://medium.com/basecs/whats-a-linked-list-anyway-part-1-d8b7e6508b9d
