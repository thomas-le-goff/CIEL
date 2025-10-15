# CIEL 2 - Evaluation - Snake 🐍🍎

_Nom et prénom :_

## Avant de commencer

Ce projet utilise la bibliothèque [Raylib](https://www.raylib.com/) pour faciliter l'utilisation des entrées (clavier) et sorties (dessins sur l'écran).

Afin de télécharger et compiler la bibliothèque exécutez les commandes suivantes (à faire uniquement une fois):

```c
cd build
./premake5 gmake
cd ..
make
```

Vous pourrez ensuite pour compiler et lancer votre programme utiliser la commande suivante :

```c
make && ./bin/Debug/snaCke
```

> ℹ️ Me solliciter si vous rencontrez une erreur liée à la compilation/exécution du programme.

### Annexes

Pour réaliser ce TP, 4 documents annexes sont à votre disposition :

- Le cours d'introduction au langage C : [c_introduction.pdf](./c_introduction.pdf)
- Le cours sur la gestion de la mémoire en langage C : [c_memory.pdf](./c_memory.pdf)
- Une carte mentale du langage C : [mind_map_c.pdf](./mind_map_c.pdf)
- Un document de référence des fonctions de la bibliothèque Raylib [raylib_cheatsheet_v5.5.pdf](./raylib_cheatsheet_v5.5.pdf)

### Structure d'un jeu (GameLoop)

<center>
  <img src="./resources/gameloop.svg" alt="gameloop" width="500">
</center>

### Principe de la liste chaînée appliqué au jeu Snake

<center>
  <img src="./resources/snake_as_linked_list.svg" alt="snake_as_linked_list" width="500">
</center>

La liste chaînée est une structure de données représentant une collection ordonnée et de taille arbitraire d'éléments de même type.

Chaque cellule contient :

- la valeur associée à l'élément (dans notre cas il s'agit de la position de la cellule à l'écran).
- un pointeur vers l'élément suivant (ou successeur).

La valeur dîte sentinelle `NULL` permet de détecter la fin de la liste chaînée.

## Instructions

> ℹ️ Le symbole 💻 indique que la question nécessite une modification du code source du programme (dossier `src` emplacement signalé par un commentaire `TODO: x.y`, x.y étant le numéro de la question).

> ℹ️ Le symbole ✍️ indique que la question nécessite une réponse rédigé (directement sur le document en lieu et place des balises `<br>`).

> ℹ️ Les fonctions dans lesquelles vous devez intervenir se trouvent en début du fichier `src/main.c`.

### 1 - Déplacer le serpent 🐍 (5 points)

**1.1** 💻 - Sachant `IsKeyDown(KEY_UP)` permet de savoir quand la touche "flêche du haut" est appuyée adaptez les premières instructions de la fonction `update` pour permettre au serpent de descendre et d'aller à gauche.

<br>
<br>

**1.1.1** ✍️ - Quel est l'utilité de la deuxième partie de la condition suivante : `IsKeyDown(KEY_UP) && state.snake_direction > Down` ? Rappelez la particularité du type `enum` en langage C qui permet cette opération.

<br>
<br>

**1.2** 💻 - Adaptez l'instruction `switch` présente dans la fonction `update` pour gérer les cas `Down`, `Right`, `Left`.

<br>
<br>

**1.3** 💻 Sachant que `SnakeChunk *head` est un pointeur vers la tête du serpent et que le membre `position` correspond à sa position sur l'écran modifiez le corps de la fonction `move_snake` (on souhaite uniquement faire bouger la tête).

<br>
<br>

> ℹ️ à ce stade vous devriez avoir un serpent qui se déplace dans les 4 directions.

### 2 - Manger la pomme 🍎 (5 points)

**2.1** 💻 - En vous appuyant sur la forme géométrique de la pomme et de la tête du serpent modifier le corps de la fonction `check_square_collision` pour retourner `true` quand une collision a lieu entre le carré position `a` de côté `a_size` et le carré de position `b` de côté `b_size`.

<br>
<br>

**2.2** 💻 - Dans la fonction `update` détectez l'appel à la fonction `check_square_collision`. Mettez à jour le score, déplacez la pomme et faites grandir le serpent dans le cas où une collision avec la pomme est détectée.

<br>
<br>

**2.2.1** ✍️ - Comment se nomme la technique employé par la procédure `move_apple` pour déplacer la pomme sans nécessiter de valeur de retour et d'affectation par le code appelant ?

<br>
<br>

**2.2.2** ✍️ - Décrivez les étapes nécessaires pour réussir cette opération en utilisant l'autre technique (sans pointeur).

<br>
<br>

**2.3** 💻 - Ecrivez le corps de la fonction `draw_score` pour afficher un texte avec le score à l'endroit de votre choix sur l'écran (💡 [raylib_cheatsheet_v5.5.pdf](./raylib_cheatsheet_v5.5.pdf)).

<br>
<br>

> ℹ️ - à ce stade le serpent peut manger la pomme et le score est incrémenté.

### 3 - Faire grandir le serpent 🎢 (6 points)

**3.1** 💻 - La fonction `grow_snake` doit faire grandir le serpent d'un "morceau", **complétez** le corps de cette fonction en suivant les instructions suivantes :

- Allouez un espace mémoire pour contenir le nouveau "morceau" du serpent
- Le serpent utilise le principe de liste chaînée, chaque "morceau" (maillon) contient un pointeur vers le suivant :

  - Le nouveau "morceau" doit être inséré après le dernier morceau du serpent.
  - La position du nouveau maillon est la position actuelle de la tête.

<br>
<br>

**3.2** 💻 - Maintenant que le serpent grandit, il est nécessaire d'adapter la fonction `move_snake` pour que chaque maillon soit dessiné l'un après l'autre :

- Le maillon N+1 doit prendre la position du maillon N.
- La tête doit prendre la position passée en paramètre (`new_position`)

Complétez la fonction `move_snake`.

<br>
<br>

> ℹ️ - à ce stade le serpent grandit lorsqu'il mange la pomme.

### 4 - Game Over 😵 (2 points)

**4.1** 💻 - Dans le jeu d'origine, le joueur perd dès que le serpent se mange lui-même ou qu'il touche un mur. Complétez la fonction `game_is_over` pour détecter ces deux cas.

<br>
<br>

> ℹ️ - Pour rappel la fonction `check_square_collision` permet de détecter la collision entre deux carrés ... L'écran est un carré et chaque morceaux du serpent est aussi un carré ...

> ℹ️ - La fonction `Vector2Zero()` vous permez d'obtenir un `Vector2` initialisé à (0, 0).

**4.2** 💻 - Complétez la fonction`free_snake` pour qu'elle libère la mémoire allouée par le serpent.

> ℹ️ - La tếté du serpent est allouée sur la stack frame de la fonction main, il n'y a donc pas besoin de libérer cette espace mémoire.

<br>
<br>

### 5 - Adaptation libre (2 points + 2 points de compensations au besoin 🙃)

> ℹ️ Avant de faire cette partie veillez à conserver une version fonctionnelle du jeux pour ne pas risquer de dégrader les autres parties de l'évaluation (un simple `cp main.c main.bak` devrait suffir).

Ajouter un élément de gameplay/visuel au choix, par exemple :

- Une pomme qui change de couleur ou de forme
- Les yeux du serpent regardent toujours en direction de la pomme
- FX lors du ramassage de la pomme
- Plusieurs vies
- Double serpent
- Autre ?

## Crédits

On n'oubliera pas de remercier [Ramon Santamaria (raysan5)](https://github.com/raysan5) pour cette bibliothèque de qualité qui simplifie grandement les choses.
