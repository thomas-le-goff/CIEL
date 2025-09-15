# Liste chaînée

![](img/linked-list.png)

## Introduction

Vous travaillez sur un projet visant à développer un système de planification des trains pour un réseau ferroviaire très fréquenté.

On vous demande de développer le système de gestion des itinéraires de train.

Chaque itinéraire est constitué d'une **séquence de gares où un train donné s'arrête**.

--------------------------------------------------------------------------------

### Liste chaînée

La liste chaînée est une structure de données fondamentale en informatique, souvent utilisée dans l'implémentation d'autres structures de données.<br>
C'est une liste de « nœuds », où chaque nœud est lié à son ou ses voisins forment ainsi une chaîne.

Dans une **liste simplement chaînée**, chaque nœud est uniquement relié au nœud qui le suit.<br>
Dans une **liste doublement chaînée**, chaque nœud est relié à la fois au nœud qui le précède et à celui qui le suit.

![](https://upload.wikimedia.org/wikipedia/commons/2/26/Liste_doublement_cha%C3%AEn%C3%A9e.png)

Si vous voulez approfondir les listes chaînées, consultez [cet article][intro-linked-list], qui les explique à l'aide de jolis schémas.

## Instructions

Votre équipe a décidé d'utiliser une **liste doublement chaînée** pour représenter chaque itinéraire.

Le système doit suivre la spécification suivante :

- Chaque gare le long du trajet du train sera représentée par **un nœud de la liste chaînée**.

- Vous n'avez pas besoin de vous soucier des heures d'arrivée et de départ aux gares.

- Chaque gare **sera simplement représentée par un numéro**.

- Les itinéraires peuvent être prolongés, en ajoutant des gares au début ou à la fin du trajet.

- Ils peuvent également être raccourcis en retirant des gares au début ou à la fin du trajet.

- Parfois, une gare ferme, et dans ce cas elle doit être retirée de l'itinéraire, même si elle ne se trouve pas au début ou à la fin.

- La taille d'un itinéraire se mesure non pas en distance parcourue, mais par le nombre de gares desservies.

Les déclarations à implémenter sont dans le fichier `linked_list.h` et votre code doit être écrit dans le fichier `linked_list.c`

### Tests

Un jeu de tests unitaires correspondant aux spécifications a été rédigé pour vous permettre de valider les bons fonctionnement de votre programme (fichier `test_linked_list.c`).

Dans ce fichier chaque fonction correspond à un cas de test. Appuyez-vous sur son contenu pour concevoir et comprendre les attentes envers votre système (principe du TDD).

Les tests peuvent être executés via la commande suivante :

```shell
make test
```

Certains tests sont pour le moment ignorés (pour vous permettre d'implémenter chaque fonction petit à petit) ; pour activer plus de test vous pouvez supprimer les appels `TEST_IGNORE()` dans le fichier `test_linked_list.c`.

[Plus de details concernant le framework de test Unity](https://www.throwtheswitch.org/unity)

### Contraintes

Votre programme doit être écrit en suivante les recommandations de l'ANSSI (en terme de sécurité et qualité de code).

- <https://cyber.gouv.fr/publications/regles-de-programmation-pour-le-developpement-securise-de-logiciels-en-langage-c>

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
