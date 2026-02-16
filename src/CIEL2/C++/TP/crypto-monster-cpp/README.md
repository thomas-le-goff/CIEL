# CIEL2 - TP CryptoMonsters (introduction à la POO en C++)

## Avant de commencer

> Le code source nécessaire pour ce TP est disponible ici : [crypto-monster-cpp.zip](/ciel2/s2-4_poo_cpp/crypto-monster-cpp.zip)

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
make && ./bin/Debug/crypto-monster-cpp
```

> ℹ️ Me solliciter si vous rencontrez une erreur liée à la compilation/exécution du programme.

> Voici un document de référence des fonctions mises à disposition par Raylib <https://www.raylib.com/cheatsheet/cheatsheet.html>

## Introduction
Ce TP a pour objectif d’introduire le concept de programmation orientée objet en langage C++.

L’idée est de réaliser un programme de génération de monstres dont la forme et la couleur sont basées sur une séquence ADN générée aléatoirement. Ce principe de génération a récemment pris de l’ampleur avec la mise en place de *smart contracts* pour les [NFT (Non-Fungible Tokens)](https://fr.wikipedia.org/wiki/NFT) sur la blockchain Ethereum. Ce TP s’inspire librement du tutoriel [CryptoZombies](https://cryptozombies.io/) et des [CryptoKitties](https://www.cryptokitties.co/).

> **Attention** : Le principe des NFT repose sur l’utilisation d’un système blockchain pour certifier la propriété d’un actif numérique. Ici, nous ne reprenons que le mécanisme de génération aléatoire. Pour aller plus loin dans la découverte des blockchains et des NFT, des ressources comme [NaiveCoin](https://lhartikk.github.io/jekyll/update/2017/07/15/chapter0.html) sont recommandées.

---

## CryptoMonster

### ADN de monstre
Voici des exemples de monstres générés par le programme final, avec leur ADN associé :

- **ADN : 133484642967201967**
  ![Exemple de monstre](/ciel2/s2-4_poo_cpp/133484642967201967.png)

- **ADN : 328765965610937671**
  ![Exemple de monstre](/ciel2/s2-4_poo_cpp/328765965610937671.png)

- **ADN : 389579223599235987**
  ![Exemple de monstre](/ciel2/s2-4_poo_cpp/389579223599235987.png)

Chaque segment de la séquence ADN est composé de **2 chiffres** et encode une caractéristique du monstre. Par exemple, pour la séquence **13 34 84 64 29 67 20 19 67** :
- **13** → Type de bras (fichier `arm_13.png` dans le dossier `resources`).
- **34** → Type de corps.
- **84** → Type d’yeux.
- **64** → Type de jambes.
- **29** → Type de bouche.
- Les 4 derniers segments (**67 20 19 67**) sont libres pour des extensions futures.

> Le dossier `resources` contient toutes les images des membres et leurs variantes (`arm_1.png` à `arm_30.png`, etc.).

Le programme final permettra :
- De générer un nouveau monstre en appuyant sur la touche **Espace**.
- D’exporter le monstre actuel au format PNG avec la touche **Entrée**.

## Générer des monstres

### Code de rendu
Afin de visualiser les monstres générés, la bibliothèque **Raylib** est utilisée pour dessiner chaque membre du monstre via le code suivant :

```cpp
my_monster.describe();

// Dessin du monstre
// Corps
Texture body_texture = part_manager.getPartTexture("body", my_monster.getBodyType());
Vector2 monster_origin = {RENDER_TEXTURE_WIDTH / 2 - (float)body_texture.width / 2, RENDER_TEXTURE_HEIGHT / 2 - (float)body_texture.height / 2 - 75};

DrawTextureV(body_texture, monster_origin, WHITE);

// Jambes
Texture leg_texture = part_manager.getPartTexture("leg", my_monster.getLegType());
float y_leg_offset = body_texture.height - 100;
DrawTextureV(leg_texture, Vector2Add(monster_origin, Vector2{+(float)body_texture.width - leg_texture.width / 2, y_leg_offset}), WHITE);
DrawTextureRec(leg_texture, Rectangle{0, 0, -(float)leg_texture.width, (float)leg_texture.height}, Vector2Add(monster_origin, Vector2{-(float)leg_texture.width / 2, y_leg_offset}), WHITE);

// Bras
Texture arm_texture = part_manager.getPartTexture("arm", my_monster.getArmType());
float y_arm_offset = 50;
DrawTextureV(arm_texture, Vector2Add(monster_origin, Vector2{(float)body_texture.width - arm_texture.width / 2, y_arm_offset}), WHITE);
DrawTextureRec(arm_texture, Rectangle{0, 0, -(float)arm_texture.width, (float)arm_texture.height}, Vector2Add(monster_origin, Vector2{-(float)arm_texture.width / 2, y_arm_offset}), WHITE);

// Yeux
Texture eye_texture = part_manager.getPartTexture("eye", my_monster.getEyeType());
float y_eye_offset = 60;
DrawTextureV(eye_texture, Vector2Add(monster_origin, Vector2{(float)body_texture.width - eye_texture.width, y_eye_offset}), WHITE);
DrawTextureRec(eye_texture, Rectangle{0, 0, -(float)eye_texture.width, (float)eye_texture.height}, Vector2Add(monster_origin, Vector2{0, y_eye_offset}), WHITE);

// Bouche
Texture mouth_texture = part_manager.getPartTexture("mouth", my_monster.getMouthType());
DrawTextureV(mouth_texture, Vector2Add(monster_origin, Vector2{(float)body_texture.width / 2 - mouth_texture.width / 2, (float)body_texture.height / 2}), WHITE);
```

_🖥️ Copiez-collez ce code à la ligne 66 dans `main.cpp`, en lieu et place du commentaire `// TODO`._

Comme vous pouvez le constater, le code précédent utilise une variable nommée `my_monster` qui n’est déclarée nulle part ailleurs.

Cette variable est ce qu’on appelle **une instance/un objet** de la classe `CryptoMonster`, définie dans le fichier `crypto_monster.cpp`.

_🖥️ Déclarez une variable `my_monster` de type `CryptoMonster`, au bon endroit pour qu’elle soit utilisable par le code de rendu du monstre._

Une fois cette variable déclarée, le programme ne compile toujours pas (en théorie). En effet, il manque certaines **méthodes** à la classe `CryptoMonster`.

_🖥️ En vous appuyant sur le diagramme de classe suivant**, ajoutez les méthodes manquantes à la classe `CryptoMonster` :_

[![Diagramme de classe](https://mermaid.ink/img/pako:eNp1kstOwzAQRX8lGrFoRajyImm8g5YdBYRYoWzceppaqu3IdlDTKnw7TlpQi5pZeXzm3hk_DrBSDIHAakuNmXNaaioK6bnod7yZbiqrFkoai9o7HFEXd5IKJJ6xjBBjNZflGWOSDqDbC8PR-Ix8D6MS7YMWH02Fo7HHpb1Ej4o1Q-ypwSH0jOUQWqjabobgSy2WqF_Xztpc5e5i3P714zM0K82XXcGX4uzszpxyLukb1XbkLJ0tw53fuXuG7_FfH1ctUVOL71QyJcLpnJf8NNll75ujqC0k-FBqzoBYXaMPArWgXQr9qxZgNyiwAOKWDNe03toCCtk6WUXlp1LiV6lVXW6ArOnWuKyumJvj9HX-StCNr2eqlhZI3jsAOcAOSJyGkzSKgjiP4ijPwjTxoQGShZMgjqP7MI-SMEjSaevDvu8ZTLI8zaf3DkSJU2XtD8Tu0YM)](https://mermaid.live/edit#pako:eNp1kstOwzAQRX8lGrFoRajyImm8g5YdBYRYoWzceppaqu3IdlDTKnw7TlpQi5pZeXzm3hk_DrBSDIHAakuNmXNaaioK6bnod7yZbiqrFkoai9o7HFEXd5IKJJ6xjBBjNZflGWOSDqDbC8PR-Ix8D6MS7YMWH02Fo7HHpb1Ej4o1Q-ypwSH0jOUQWqjabobgSy2WqF_Xztpc5e5i3P714zM0K82XXcGX4uzszpxyLukb1XbkLJ0tw53fuXuG7_FfH1ctUVOL71QyJcLpnJf8NNll75ujqC0k-FBqzoBYXaMPArWgXQr9qxZgNyiwAOKWDNe03toCCtk6WUXlp1LiV6lVXW6ArOnWuKyumJvj9HX-StCNr2eqlhZI3jsAOcAOSJyGkzSKgjiP4ijPwjTxoQGShZMgjqP7MI-SMEjSaevDvu8ZTLI8zaf3DkSJU2XtD8Tu0YM)

_🖥️ Modifiez la méthode `describe` pour afficher dans la console l’ensemble des informations qui vous semblent utiles._

> Chacune de ces méthodes retourne le numéro de la variante du membre correspondant. Dans un premier temps, vous pouvez retourner **1**. Nous mettrons en place une génération aléatoire dans la suite du TP.

> À cette étape, vous devriez avoir un programme fonctionnel qui ne génère qu’un seul type de monstre.

### Classe CryptoMonster

Maintenant que le code de rendu est opérationnel, nous allons nous concentrer sur la génération de la séquence ADN. Étant donné que le code de rendu utilise des méthodes pour accéder aux morceaux d’ADN du monstre, aucune modification ne sera nécessaire dans le programme de rendu. Ce principe s’appelle **l’encapsulation** : la classe `CryptoMonster` expose des méthodes permettant de connaître chaque membre du monstre. On peut modifier la manière dont les membres sont générés sans « casser » le code qui utilise ces méthodes.

La fonction `static generateRandom18DigitNumber()` dans la classe `CryptoMonster` permet de générer une séquence d’ADN.

_🖥️ Ajoutez un attribut dans la classe `CryptoMonster` nommé `dna`. Cet attribut doit être **privé** (il ne sera utilisé que depuis l’intérieur de `CryptoMonster`)._

Les attributs doivent être initialisés lors de la construction/création de l’objet. Pour ce faire, une méthode spéciale nommée **« constructeur »** est présente dans la classe. Cette méthode sera automatiquement appelée lors de la création d’une instance. En C++, plusieurs syntaxes permettent d’initialiser les attributs d’un objet :

```cpp
CryptoMonster::CryptoMonster() : dna(generateRandom18DigitNumber())
{
}

// OU
CryptoMonster::CryptoMonster()
{
  this->dna = generateRandom18DigitNumber();
}

// OU encore
CryptoMonster::CryptoMonster() : dna {generateRandom18DigitNumber()}
{
}
```

_✍️ Cherchez les différences entre ces 3 syntaxes._


_🖥️ Utilisez la syntaxe qui vous semble la plus adaptée à notre cas._


Maintenant que notre classe `CryptoMonster` possède un attribut `dna`, il est nécessaire d’adapter les méthodes `getXXXType` pour utiliser le morceau d’ADN correspondant au membre. Elles deviendront alors des **propriétés dérivées** de l’attribut `dna`.


_🖥️ Complétez la méthode `int getDnaPart(int index, int size) const;`_.


> **Indice** : `dna` est de type `std::string`. Certaines méthodes de cette classe peuvent vous aider.


_🖥️ Modifiez les méthodes `getXXXType` pour utiliser la méthode privée `getDnaPart` avec le bon morceau d’ADN. **Vérifiez leur bon fonctionnement** à l’aide des informations fournies par la méthode `describe`._


Si la méthode `describe` vous affiche des informations correctes, mais que le monstre généré est toujours le même, **c’est normal**. En effet, le constructeur de la classe `PartManager` dans le fichier `part.cpp` possède un bug.


_🖥️ Identifiez ce bug et corrigez-le._


_✍️ Essayez de comprendre en quoi cette classe illustre le principe RAII._


> Si le bug est correctement corrigé, vous devriez avoir un monstre différent à chaque démarrage du programme.

## Générer des nouveaux monstres

Actuellement, la génération d'un monstre se fait au démarrage de l'application. Cela est dû au fait que la génération de l'ADN est faite au moment de la **construction** d'un objet `CryptoMonster` et que notre instance `my_monster` est créée au lancement du programme.

Afin de générer un nouveau monstre à chaque appuie sur la touche `Espace` deux adaptations sont possibles : 

- ajouter une méthode publique `void generateDNA();` dans `CryptoMonster` qui aurait pour effet de re-générer une nouvelle séquence d'ADN à chaque appel
- être capable de de créer une **instance** de `CryptoMonster` et l'affecter à `my_monster` lors de l'appuie sur `Espace` (en d'autres termes : tuer notre monstre et en faire naître un nouveau)

Dans notre cas, par soucis de cohérence avec le monde réel, nous allons utiliser la deuxième possibilité.

Lorsque l'on souhaite créer dynamiquement (pendant l'exécution du programme) des instances de classes, il est nécessaire de faire appel à **l'allocation dynamique**.

L'idée est de remplacer `my_monster` par un pointeur vers un espace mémoire sur le tas (en anglais "heap") et de le faire correspondre à un autre espace mémoire lors de l'appuie sur la touche `Espace` (sans oublier de supprimer l'ancien qui ne sera plus utile).

Avant de commencer les modifications, nous allons adapter la classe `CryptoMonster` pour identifier l'étape de construction et de destruction.

_✍️ Ajoutez un log dans le constructeur de la classe `CryptoMonster` (`CryptoMonster::CryptoMonster()`), ainsi q'un destructeur `CryptoMonster::~CryptoMonster()` lui aussi avec un log (via `std::cout << "Mon super log" << std:endl`)_

_✍️ Adaptez le code de création de `my_monster` pour utiliser les opérateurs `new` et `delete` (une modification du type et des appels de méthodes associés sera sûrement nécessaire)._

Maintenant que `my_monster` est une référence vers `CryptoMonster` il est possible de modifier l'instance correspondante.

_✍️ Trouvez où placer le code suivant et complétez les commentaires._

```cpp
if (IsKeyPressed(KEY_SPACE))
{
  // TODO Supprimer le monstre (ssi il existe)
  // TODO Créer un nouveau monstre et l'affecter à my_monster
}
```

### Un code plus robuste avec les smart pointers (à passez si vous n'êtes pas en avance)

Essayez de remplacer l'usage de `new` et `delete` avec un smart pointer comme `std::unique_ptr`.

L'objectif des smart pointer est de gérer la mémoire dynamiquement allouée à la place du développeur, notamment, en s'appuyant sur la mémoire automatique.

Dans notre cas, nous aimerions nous "débarasser" de la nécessité d'utiliser `delete` et s'assurer que la mémoire de `my_monster` soit automatiquement libérée.

__En vous appuyant sur [la référence C++ concernant `std::unique_ptr`](https://en.cppreference.com/w/cpp/memory/unique_ptr.html), adaptez le code pour ne plus utiliser `new` et `delete`._

> Il possible (et souhaité) de faire la même chose avec `RenderTexture2d target`, mais, en fournissant un "custom deleter" pour libérer la mémoire utilisée en appelant `UnloadRenderTexture`.

## Exporter un monstre

Dans cette partie, nous allons ajouter une fonctionnalité d'export du CryptoMonster dans une image.

Afin de correctement comprendre la suite, il est nécessaire de connaître la différence entre une texture et une image : 

- Texture : une texture est un espace mémoire contenant les pixels qui permettent de représenter l'image à l'écran. Une texture est stockée au niveau de la mémoire de la carte graphique (VRAM).

- Image : une image correspond aussi à un espace mémoire contenant des pixels, mais, présent au niveau de la mémoire du processeur (RAM). 

Le programme actuel utilise un mode de rendu dit "buffered", le principe est le suivant : 

![buffered_drawing.drawio.svg](/ciel2/s2-4_poo_cpp/buffered_drawing.drawio.svg)

1. les instructions de dessins sont envoyées dans un tampon ("buffer" ou "texture")
2. la texture est dessinée à l'écran

Dans la version actuelle, notre scène contenant le CryptoMonster est dessinée dans une texture puis dessinée à l'écran. Pour en faire un fichier image, il faut : 
- dessiner la texture dans une image via la fonction `LoadImageFromTexture` (transfert de la carte graphique vers le processeur)
- exporter l'image dans un fichier via `ExportImage` (transfert de la RAM vers le HDD)

_✍️ En vous appuyant sur la documentation de Raylib, adaptez le code suivant (dans main.cpp) pour exporter le CryptoMonster dans une image lors de l'appuie sur `Entrée`._

```cpp
// Export to image
if (drawn && IsKeyPressed(KEY_ENTER))
{
	// TODO
}
```

## Améliorations orientées objets

Afin de rendre le code **modulaire** et **adaptable**, nous allons recourir à la **programmation orientée objet**.

Actuellement, notre programme possède deux classes :

* `CryptoMonster`, qui **encapsule** l’ADN du monstre et expose des méthodes (propriétés dérivées) pour accéder à ses différents attributs ;
* `PartManager`, qui charge les différentes textures d'un monstre et fournit des méthodes pour récupérer la texture appropriée.

Nous souhaitons ajouter deux nouvelles classes :

* `Game`, une classe **abstraite** qui contiendra la logique dite **métier** de notre programme (actuellement située dans `main.cpp`) ;
* `RaylibGame`, une sous-classe de `Game` qui contiendra la logique spécifique à la bibliothèque **Raylib**.

### Classe Game

Voici le diagramme de classe de `Game` :

[![](https://mermaid.ink/img/pako:eNptkU1rwzAMhv-K0WljWcmX8-Hb1o2eCjvsNALF1GoaiO2gOFu70v325aMtgU0X-338SkLyCbZWIQjY1rJtXypZktSFYX2oinDrKmvY83thJja62EpqZKeJDPGojxttTeuQmGBLOjbOric9MzWS3EZLI8vR9tbL9aSu1Yd4GIrf3c_Az5XMWNco6XrIPm2lZlyR_LrRWe-9NKrG10NjyT2NQ_3JvXhWaJD62v-4zuBBSZUC4ahDDzSSloOEcRcFuD1qLED0V4U72dWugMIMaY00H9bqaybZrtyD2Mm67dU0zGX3N0poFNLSdsaBSOOxBogTHEBEPl_w1E_iLMijiOf94xFEmC3yIEg4j8PED3mUnz34Hpv6iyzNYh5mQZynceJHiQeoKmdpffn84Tj_AiOYnlE?type=png)](https://mermaid.live/edit#pako:eNptkU1rwzAMhv-K0WljWcmX8-Hb1o2eCjvsNALF1GoaiO2gOFu70v325aMtgU0X-338SkLyCbZWIQjY1rJtXypZktSFYX2oinDrKmvY83thJja62EpqZKeJDPGojxttTeuQmGBLOjbOric9MzWS3EZLI8vR9tbL9aSu1Yd4GIrf3c_Az5XMWNco6XrIPm2lZlyR_LrRWe-9NKrG10NjyT2NQ_3JvXhWaJD62v-4zuBBSZUC4ahDDzSSloOEcRcFuD1qLED0V4U72dWugMIMaY00H9bqaybZrtyD2Mm67dU0zGX3N0poFNLSdsaBSOOxBogTHEBEPl_w1E_iLMijiOf94xFEmC3yIEg4j8PED3mUnz34Hpv6iyzNYh5mQZynceJHiQeoKmdpffn84Tj_AiOYnlE)

_✍️ À partir du diagramme écrivez le fichier de déclaration de la classe `Game`._

_✍️ À partir du diagramme et du fichier `main.cpp` écrivez les déclarations des méthodes `Game::update` et `Game::draw`._

### Un peu d'abstraction

Afin de rendre le code indépendant de Raylib, nous allons utiliser les notions **d’héritage** et **d’abstraction** pour que le code de rendu (lié aux fonctions Raylib) soit exclusivement contenu dans la classe `RaylibGame`.

Pour cette adaptation, il est nécessaire d’ajouter des méthodes dîtes **virtuelles** dans la classe `Game`.

Voici le nouveau diagramme de classes des classes `Game` et `RaylibGame`:

[![](https://mermaid.ink/img/pako:eNqlk91PwjAQwP-V5XxBGWQbdBsNIVE0xAcSY3wyS8hBCyzZ2qXrFET8290HH0OiiXov7f3uq3dtNzCTjAOFWYRpehviQmEcCCMXFio-06EUxs1TICr2iOsonI4w5kar9T4wit3eVmYoibGpSCH9Pk5TrXCmB4MjbcXrSSxFqrkyqDFU60TLcaXXnBJUehKjwEXp9pCr40rb1yykWZRsXNbAx57UWJYw1Dk0XmTIapwpfD3QWu0lChbxu1Uilb4ux3AWu_MZccFVnvuL19HvovK7F0mmd-armrU4wckEGt9M5jyUl8f7ffD29M5qt1q7ueYRn073lP_Y59_b_E-XhybBhIUKGVCtMm5CzFWMhQplmwHoJc_fL9B8y_gcs0gHEIhtHpageJYy3kcqmS2WQOcYpblWvaXdZzlQxQXjaigzoYH2vDIH0A2sgHZct00s4vs9v-cQz7dNWAO1HbvddTrEsizXtjrEdrcmvJVVrbbX8YlDiNfreq5PbMcEzkIt1Xj3XYtl-wn3XirP?type=png)](https://mermaid.live/edit#pako:eNqlk91PwjAQwP-V5XxBGWQbdBsNIVE0xAcSY3wyS8hBCyzZ2qXrFET8290HH0OiiXov7f3uq3dtNzCTjAOFWYRpehviQmEcCCMXFio-06EUxs1TICr2iOsonI4w5kar9T4wit3eVmYoibGpSCH9Pk5TrXCmB4MjbcXrSSxFqrkyqDFU60TLcaXXnBJUehKjwEXp9pCr40rb1yykWZRsXNbAx57UWJYw1Dk0XmTIapwpfD3QWu0lChbxu1Uilb4ux3AWu_MZccFVnvuL19HvovK7F0mmd-armrU4wckEGt9M5jyUl8f7ffD29M5qt1q7ueYRn073lP_Y59_b_E-XhybBhIUKGVCtMm5CzFWMhQplmwHoJc_fL9B8y_gcs0gHEIhtHpageJYy3kcqmS2WQOcYpblWvaXdZzlQxQXjaigzoYH2vDIH0A2sgHZct00s4vs9v-cQz7dNWAO1HbvddTrEsizXtjrEdrcmvJVVrbbX8YlDiNfreq5PbMcEzkIt1Xj3XYtl-wn3XirP)

_✍️ Ajoutez les nouvelles méthodes dans la classe `Game` et ajoutez les fichiers nécessaires à la déclaration de la classe `RaylibGame`._