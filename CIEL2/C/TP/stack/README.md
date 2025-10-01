# CIEL 2 - TP analyser la pile mémoire d'un programme

Ce TP a pour objectif de vous faire comprendre le lien entre la pile (stack) mémoire d'un programme et le code de ce dernier. En bonus, vous pourrez exploiter la faille d'un programme que vous découvrirez à l'aide du débogueur GDB.

## Avant de commencer

Ce TP ne propose pas de fichier `makefile` pour faciliter la compilation et l'exécution des programme.

Pour compiler et exécuter un programme vous pouvez simplement utiliser le compilateur `gcc` via la commande suivante dans un terminal :

```shell
gcc -O0 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-stack-protector -fno-inline  -mno-red-zone  exercice_1.c -o exercice_1.out && ./exercice_1.out
```

> ℹ️ Les options passées à la commande gcc permettent de désactiver certaines protections et optimisations pour rendre les exercices plus abordables.

Veillez à adapter `exercice_1` à l'exercice que vous souhaitez compiler.

## Instructions

### 1 - Un programme qui lit sa propre mémoire

**1.1** ✍️ - Compilez et exécutez le fichier `exercice_1.c`. _Que fait ce programme ?_

<br>
<br>

**1.2** 💻 - La fonction `dump_stack_memory` présente dans le fichier `read_stack_memory.h` permet de lire les adresses et les valeurs mémoires entre deux adresses mémoire. _Dans le fichier `exercice_1.c` ajoutez un appel à la fonction `dump_stack_memory`_

> ℹ️ Il est nécessaire d'ajouter une déclaration de variable pour appeler la fonction `dump_stack_memory`, demandez-vous quel est le type le plus approprié pour récupérer une case de la mémoire (aidez-vous aussi de la définition de la fonction ...).

<br>
<br>

**1.3** ✍️ - Dans la sortie du programme repérez les adresses des variables suivantes :

- char a;
- short i;
- char x;
- long sn1;
- long sn2;
- int y[];

_Copier ici les lignes pertinentes concernant ces variables._

_Que pouvez-vous dire concernant la valeur de `char x` ?_

> ℹ️ Chaque ligne affichée par `dump_stack_memory` représente un octet (donc un char / u8).

<br>
<br>

**1.4 (bonus)** 💻 - La fonction `dump_stack_memory` gère mal un certain cas. _Trouvez ce cas et corrigez-le_.

### 2 - Stack frame avant/après

**2.1** ✍️ - La fonction `main` dans `exercice_2.c` et la fonction `magic_function` de `magic_function.h` utilisent deux variables nommées respectivement `rsp` et `rbp`. _Que contiennent ces variables ? (bonus : nous sommes sur une architecture 64 bits comment ces variables auraient dû être nommées ?_

<br><br>

**2.2** 💻 - L'objectif de ce programme est de montrer l'état de stack **après** que la fonction `magic_function` ait exécuté sa suite d'instructions et **après** que la fonction `main` ait repris la 🖐️ (après le return). _Complétez la fonction `diff_dump` qui a pour objectif d'afficher la différence entre le snapshot avant et le snapshot après_.

**2.3** ✍️ - Lancez le programme. _Notez ici les éléments qui illustrent la notion de stack frame_

### 3 - Locking door failed

<center>
  <img src="./img/locking-door-fail-sliding-door.gif" alt="locking-door-fail-sliding-door" width="130">
</center>

> Cet exercice fait appel à l'outil GDB (**G**NU **D**e**b**ugger). Un débogueur permet (notamment) d'analyser la mémoire d'un programme.

> Le programme à étudier est le suivant (binaire uniquement)

**3.1** 💻 - Exécutez le programme `pwn-normal` (normalement). _Que vous demande ce programme ?_

**3.2** 💻 - Exécutez le programme `pwn-normal` à l'aide de `gdb`

```shell
gdb pwn-normal
```

Une fois dans l'outil GDB vous avez à disposition des commandes qui permettent de dérouler l'exécution du programme :

```shell
break main # positionner un point d'arrêt lors de l'appel à la fonction main

next # permet d'exécuter une ligne par une ligne
info locals # affiche les variables locales
info variables # affiche toutes les variables de la stack
```

_Sachant que le programme lit une entrée utilisateur au clavier (pour récupérer) le mot de passe, sur quelles fonctions pouvez-vous mettre un point d'arrêt pour valider que le programme l'utilise bien ?_

<br>
<br>

**3.3** ✍️ - Une première variable locale est `buf` une autre est `ok`. _Quel est son rôle ?_

<br>
<br>

**3.4** 💻 - En vous appuyant sur la **position** de la variable `ok` et en connaissant les risques associés à l'utilisation de la fonction découverte en **3.2** quelle faille pouvez-vous exploiter ? _Nommez cette faille et exploitez-la_.

_Notez la valeur utilisée pour effectuer cette attaque._

<br>
<br>

**3.5** ✍️ - Quelle option(s) intégrée(s) au compilateur permettent d'éviter ce genre de faille ? Quelle modification de ce code permettrait d'éviter ce problème "by design".

## Crédits

Ce TP prend appui sur les éléments et exercices présentés dans ce cours : <https://www.cs.ru.nl/~erikpoll/hic/> de l'Université de Radboud de Nimègue (Pays-Bas).
