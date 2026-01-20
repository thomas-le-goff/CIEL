# CIEL1 – TP manipulation de tableaux en langage C

<center>
  <img src="https://t3.ftcdn.net/jpg/03/01/00/90/360_F_301009080_IETMrrXuLXop6jj6uViCWWBDL2zianEj.jpg" width="200/">
</center>

## Exercice 1 – Meilleure note, moins bonne note et moyenne

**Contexte :**<br>
Un professeur veut analyser les résultats de sa classe. Pour l'aider, on souhaite écrire un programme qui calcule la note la plus haute, la plus basse et la moyenne des élèves.

**Consignes :**

- Demander à l'utilisateur de saisir un entier `n` (nombre de notes).
- Déclarer un tableau de réels `notes` de taille maximale 100.
- Saisir `n` réels dans le tableau `notes`.
- Calculer et afficher la plus grande note, la plus petite note et la moyenne (réels `max`, `min`, `moyenne`).

  <div style="page-break-before:always">
  </div>

--------------------------------------------------------------------------------

<center>
  <img src="https://img.freepik.com/vecteurs-premium/dessin-encre-loupe_659215-1087.jpg" width="200/">
</center>

## Exercice 2 – Recherche d'une valeur et occurrences

**Contexte :**<br>
Un magasin souhaite savoir combien de fois un produit particulier apparaît dans sa liste de références. On veut vérifier si ce produit est présent et à quelles positions il se trouve.

**Consignes :**

- Demander à l'utilisateur de saisir un entier `n` (nombre d'éléments).
- Déclarer un tableau d'entiers `tab` de taille maximale 100.
- Saisir `n` entiers dans le tableau `tab`.
- Demander un entier `x` (valeur recherchée).
- Afficher si `x` existe, combien de fois (`nb_occ`), et à quelles positions.

<div style="page-break-before:always">
</div>

--------------------------------------------------------------------------------

<center>
  <img src="https://img.freepik.com/vecteurs-premium/main-cercle-dessiner-cadre-fond-crayon-circulaire-logo-doodle-rond_165079-78.jpg?semt=ais_hybrid&amp;w=740&amp;q=80" width="200/">
</center>

## Exercice 3 – Circular Buffer

**Contexte :**<br>
Dans une playlist musicale, lorsqu'on atteint la dernière chanson, on revient automatiquement à la première. C'est le même principe qu'un **buffer circulaire** utilisé en informatique pour stocker des données.

**Consignes :**

- Demander à l'utilisateur de saisir un entier `n` (nombre d'éléments).
- Déclarer un tableau d'entiers `tab` de taille maximale 100.
- Saisir `n` entiers dans le tableau `tab`.
- Demander un entier `k` (nombre de pas de décalage).
- Afficher le tableau réorganisé comme si les éléments avaient été décalés circulairement de `k` positions.

<div style="page-break-before:always">
</div>

--------------------------------------------------------------------------------

<center>
  <img src="https://thumbs.dreamstime.com/b/croquis-tir%C3%A9-par-la-main-d-escalier-71375061.jpg" width="200/">
</center>

## Exercice 4 – Tri par ordre croissant

**Contexte :**<br>
Un commerçant veut afficher ses prix en ordre croissant pour préparer un catalogue. Il faut donc trier les valeurs saisies.

**Consignes :**

- Demander à l'utilisateur de saisir un entier `n`.
- Déclarer un tableau d'entiers `tab` de taille maximale 100.
- Saisir `n` entiers dans le tableau `tab`.
- Réorganiser les valeurs du tableau en ordre croissant.
- Afficher le tableau trié.

  <div style="page-break-before:always">
  </div>

--------------------------------------------------------------------------------

<center>
  <img src="https://img.freepik.com/photos-premium/main-miroir-dessin-noir-blanc-encre_725369-1476.jpg" width="200/">
</center>

## Exercice 5 – Écriture à l'envers

**Contexte :**<br>
On souhaite développer une petite fonctionnalité qui affiche un mot ou un pseudonyme à l'envers, comme un effet miroir.

**Consignes :**

- Demander à l'utilisateur de saisir une chaîne de caractères `mot` (longueur maximale 100).
- Afficher cette chaîne à l'envers.

  <div style="page-break-before:always">
  </div>

--------------------------------------------------------------------------------

<center>
  <img src="https://thumbs.dreamstime.com/b/page-de-coloriage-v%C3%A9hicule-kayak-pour-enfants-une-mignonne-et-dr%C3%B4le-d-un-offre-des-heures-amusant-les-colorier-cette-est-tr%C3%A8s-252314231.jpg" width="200/">
</center>

## Exercice 6 – Palindrome

**Contexte :**<br>
Un palindrome est un mot qui se lit dans les deux sens (comme "radar" ou "kayak"). Ce type de test est souvent utilisé dans les jeux de lettres ou les vérifications de chaînes de caractères.

**Consignes :**

- Demander à l'utilisateur de saisir une chaîne de caractères `mot` (longueur maximale 100).
- Déterminer la longueur `n` du mot.
- Vérifier si le mot est un palindrome et afficher le résultat.

  <div style="page-break-before:always">
  </div>

--------------------------------------------------------------------------------

<center>
  <img src="https://ecdn.teacherspayteachers.com/thumbitem/Mots-etiquettes-Atelier-Puissance-4-4152746-1657233039/original-4152746-4.jpg" width="200/">
</center>

## Exercice 7 – Puissance 4

**Contexte :**<br>
On souhaite programmer une version simplifiée du jeu **Puissance 4** pour deux joueurs. Cela permet de manipuler un tableau à deux dimensions et de vérifier différentes conditions de victoire.

**Consignes :**

- Déclarer une grille de caractères `grille` de 6 lignes et 7 colonnes.
- Initialiser la grille avec des points `.`.
- Deux joueurs jouent à tour de rôle, chacun choisit une colonne `col` (entier).
- Le jeton tombe sur la case libre la plus basse de cette colonne.
- Représenter les jetons par un caractère `joueur` (`'X'` ou `'O'`).
- Le jeu continue jusqu'à ce qu'un joueur aligne 4 jetons ou que la grille soit pleine.
