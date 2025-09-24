# CIEL 2 - TP fonctions et procédures en langage C

Ce TP a pour objectif de vous faire comprendre la différence entre une **fonction** et une **procédure**. Il vous permettra également de mettre en pratique le **passage par valeur** et le **passage par référence** (via les adresses mémoire).

## Avant de commencer

### Tests unitaires avec Unity

Tout au long du TP, vous validerez vos avancées grâce au framework de tests unitaires **Unity** et à une suite de tests fournie. Ces tests permettent de vérifier automatiquement que vos fonctions se comportent comme attendu.

Pour exécuter les tests, lancez la commande suivante :

```bash
make test
```

À ce stade, le projet contient **volontairement** des erreurs de compilation. Poursuivez vers la section _Exercices_ pour corriger ces erreurs et rendre le projet compilable.

### Notion de prototype de fonction

En langage C, le **prototype d'une fonction** est sa déclaration (ou signature), qui précise :

- le type de valeur retournée (`void` si la fonction ne renvoie rien) ;
- le nom de la fonction ;
- la liste et le type de ses paramètres.

Par exemple :

```c
int sum(int a, int b);
void displayMessage(const char* message);
```

Un prototype indique au compilateur **comment** la fonction doit être utilisée, sans en fournir l'implémentation. Il permet de vérifier que les appels respectent les types attendus et facilite la séparation entre la **déclaration** (dans le `.h`) et la **définition** (dans le `.c`).

<div style="page-break-before: always;"></div>

## Instructions

### 1 - Déclaration des fonctions

**1.1** ✍️ - Ouvrez le fichier `tests.c`. _Que constatez‑vous ?_

<br>
<br>

Ajoutez les déclarations (prototypes) manquantes dans le fichier `tp_functions.h` (header) afin que `tests.c` puisse référencer les fonctions sans erreur.

> 🎯 L'objectif est de déterminer les **prototypes** des fonctions et procédures à partir de leurs spécifications (principe de **TDD** -- Test‑Driven Development). Essayez de faire en sorte que le prototype de votre fonction reflète au mieux son intention.

> ℹ️ Un éditeur comme **VS Code** peut vous aider en signalant automatiquement les erreurs, mais vous pouvez aussi vérifier directement en compilant le projet.

**1.2** ✍️ - _Selon vous, quel est l'intérêt des fichiers d'en‑tête (`.h`) ?_

<br>
<br>

### 2 - Implémentation des fonctions

**2.1** 💻 - En vous appuyant sur le contenu des tests, implémentez chacune des fonctions et procédures attendues dans le fichier `tp_functions.c`.

> 🎯 Implémentez les fonctions **sans modifier** les prototypes déjà établis. L'implémentation doit respecter la spécification, et non l'inverse !

> ℹ️ Par défaut, certains tests sont ignorés. Pour activer un test, supprimez l'appel à la fonction `TEST_IGNORE` dans le cas correspondant.

**2.3** ✍️ - Il éxiste des différences subtiles entre une fonction et procédure. _Comptez combien de procédures et de combien de fonctions vous avez écrit_.

<br>
<br>

**2.3** ✍️ - Le cas `test_array_parameter_decays_to_pointer` est particulièrement important. _Expliquez‑le et donnez des cas où ce comportement peut être problématique._

<br>
<br>

**2.4** ✍️ - La fonction `sum_array_max_out` utilise une « astuce » pour retourner deux informations différentes. _Que pensez‑vous de ce principe ? Donnez un cas où ce principe peut être très utile._

<br>
<br>

**2.5** 💻 - _En utilisant ce principe, écrivez une procédure équivalente à `atoi`._