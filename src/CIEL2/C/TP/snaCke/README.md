# CIEL 2 - TP allocation dynamique de la mémoire 🐍🍎

Ce TP a pour objectif de vous faire comprendre la notion d'allocation dynamique et son intérêt en vous faisant programmer un jeu de Snake.
<center>
  <img src="/ciel2/s2-1_langage_c/snake.gif" alt="nokia-snake" width="280">
</center>

> Le code source nécessaire pour ce TP est disponible ici : [snacke.zip](/ciel2/s2-1_langage_c/snacke.zip)
> (partie 1 et 2 complétées : [snacke_3_4.zip](/ciel2/s2-1_langage_c/snacke_3_4.zip)).

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

> Voici un document de référence des fonctions mises à disposition par Raylib <https://www.raylib.com/cheatsheet/cheatsheet.html>

## Instructions

### 1 - Déplacer le serpent 🐍

**1.1** 💻 - Sachant `IsKeyDown(KEY_UP)` permet de savoir quand la touche "flêche du haut" est appuyée, adaptez les premières instructions de la fonction `update` pour permettre au serpent de descendre et d'aller à gauche.

<br>
<br>

**1.2** 💻 - Adaptez l'instruction `switch` présente dans la fonction `update` pour gérer les cas `Down`, `Right`, `Left`.

<br>
<br>

**1.3** 💻 Sachant que `SnakeChunk *head` est un pointeur vers la tête du serpent et en étudiant le fonctionnement de la fonction `draw_snake` (qui dessine le serpent) écrivez le corps de la fonction `move_snake`.

<br>
<br>

> ℹ️ à ce stade vous devriez avoir un serpent qui se déplace dans les 4 directions.

### 2 - Manger la pomme 🍎

**2.1** 💻 - En vous appuyant sur la forme géométrique de la pomme et de la tête du serpent modifier le corps de la fonction `check_square_collision` pour retourner `true` quand une collision a lieu entre le carré position `a` de côté `a_size` et le carré de position `b` de côté `b_size`.

<br>
<br>

**2.2** 💻 - Dans la fonction `update` détectez l'appel à la fonction `check_square_collision`. Mettez à jour le score, déplacez la pomme et faites grandir le serpent dans le cas où une collision avec la pomme est détectée.

<br>
<br>

**2.3** 💻 - Ecrivez le corps de la fonction `draw_score` pour afficher un texte avec le score à l'endroit de votre choix sur l'écran.

<br>
<br>

> ℹ️ - à ce stade le serpent peut manger la pomme et le score est incrémenté.

### 3 - Faire grandir le serpent 🎢

**3.1** 💻 - La fonction `grow_snake` doit faire grandir le serpent d'un "morceau", écrivez le corps de cette fonction en suivant les instructions suivantes :

- Allouez un espace mémoire pour contenir le nouveau "morceau" du serpent
- Le serpent utilise le principe de liste chaînée, chaque "morceau" (maillon) contient un pointeur vers le suivant (pour plus de détails : <https://fr.wikipedia.org/wiki/Liste_cha%C3%AEn%C3%A9e>) :

  - Le nouveau "morceau" doit être inséré juste après la tête.
  - La position du nouveau maillon est la position actuelle de la tête.

<br>
<br>

**3.2** 💻 - Maintenant que le serpent grandit, il est nécessaire d'adapter la fonction `move_snake` pour que chaque maillon soit dessiné l'un après l'autre :

- Le maillon N+1 doit prendre la position du maillon N.
- La tête doit prendre la position passée en paramètre (`new_position`)

<br>
<br>

> ℹ️ - à ce stade le serpent grandit lorsqu'il mange la pomme.

### 4 - Game Over 😵

**4.1** 💻 - Dans le jeu d'origine, le joueur perd dès que le serpent se mange lui-même ou qu'il touche un mur. Ajoutez dans la fonction `update` la détection de ces deux cas.

<br>
<br>

**4.2** 💻 - Ajoutez au programme une fonction `reset` qui prend un pointeur vers le `GameState` qui libère la mémoire initialement allouée par le serpent et qui réinitialise l'état du jeu.

<br>
<br>

## Crédits

On n'oubliera pas de remercier [Ramon Santamaria (raysan5)](https://github.com/raysan5) pour cette bibliothèque de qualité qui simplifie grandement les choses.
