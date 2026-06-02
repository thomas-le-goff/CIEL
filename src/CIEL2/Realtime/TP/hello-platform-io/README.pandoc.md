# Découverte de PlatformIO et de M5Stack

![platformio.png](./img/platformIO.png){.align-center}

## Présentation des outils

Nous utilisons PlatformIO intégré à Visual Studio Code comme environnement de développement. PlatformIO facilite la programmation embarquée en gérant automatiquement la compilation, le téléversement du code et les bibliothèques nécessaires.

Le projet s’appuie sur le framework Arduino, qui simplifie l’accès au matériel grâce à une interface de programmation claire et des fonctions prêtes à l’emploi comme digitalWrite() ou delay(). Ce framework est ici adapté au microcontrôleur ESP32, un composant puissant et économe en énergie fabriqué par Espressif, intégrant le Wi-Fi et le Bluetooth.

La carte M5Stack, utilisée dans ce TP, repose sur un ESP32 et regroupe dans un boîtier compact un écran, des boutons et des connecteurs. La librairie M5Stack permet de contrôler facilement ces éléments depuis le code Arduino.

### Installation de PlatformIO

PlateformeIO est fourni sous forme d'extension à l'IDE Visual Studio Code. Cette formule permet, à l'équipe de développement de PlatformIO, de se concentrer sur  le développement d'outils pour l'embarqué et de laisser la partie édition de code à une équipe spécialisée (principe DRY).

![Installation de PlatformIO sur VSCode](./img/platform_io_install_1.png){.align-center}

Une fois l'extension installée, vous devez cliquer sur la tête d'alien sur la barre latérale gauche pour initialiser l'extension :

![Installation de PlatformIO sur VSCode](./img/platform_io_install_2.png){.align-center}

> la première fois l'initialisation peut prendre un peu de temps, elle se termine par un rédémarrage de VSCode. {.is-info}

## 1 - Hello World!

Avant de commencer à développer, vous devez créer un nouveau projet. Cliquez sur la tête d'alien sur la barre latérale gauche puis cliquez sur "Create New Project" et enfin "Create New Project" dans le menu "Projects" :

![Créer nouveau projet](./img/platform_io_step_2.png){.align-center}

![Créer nouveau projet deuxième étape](./img/platform_io_step_2_b.png){.align-center}


Utilisez la configuration suivante : 

- Nom du projet : `hello_m5stack`
- Board (carte) : `M5Stack Core 2`
- Framework : `Arduino`

![Paramétrage du projet](./img/platform_io_step_3.png){.align-center}

Une fois le projet créé il devrait s'ouvrir automatiquement dans l'espace de travail de VSCode (workspace, sur la gauche) : 

![Projet créé et ajouté dans le workspace VSCode](./img/platform_io_step_final.png){.align-center}

> Par défaut, PlatformIO créer les projets dans le dossier : `~/Documents/PlatformIO/` {.is-info}

### Structure d'un projet PlatformIO

**Arborescence d’un projet PlatformIO :**

- *src/*
    - Contient le code source principal du projet (ex. `main.cpp`).
    - C'est principalement dans ce dossier que vous interviendrez.
    - C’est ici que l’on écrit les fonctions setup() et loop() dans un projet Arduino.

- *include/*
    - Regroupe les fichiers d’en-tête (.h) pour déclarer fonctions, constantes ou classes partagées.

- *lib/*
    - Contient les bibliothèques locales propres au projet.
    - Chaque sous-dossier correspond à une librairie indépendante.

- *test/*
    - Dossier optionnel pour les tests unitaires.
    - Permet de valider automatiquement certaines parties du code.

- *.pio/*
    - Dossier généré et géré automatiquement par PlatformIO.
    - Contient les fichiers de build, binaires et dépendances.
    - Ne doit pas être modifié manuellement.

- *platformio.ini*
    - Fichier de configuration du projet.
    - Définit la carte, le framework, la plateforme matérielle et les options de compilation.
    - Exemple :

```ini
[env:m5stack-core2]
platform = espressif32
board = m5stack-core2
framework = arduino
```

> Pour le moment, ce fichier contient la configuration par défaut. En fonction de l'évolution de nos besoins, il sera nécessaire de modifier certains paramètres. {.is-info}

### Installation de la bibliothèque M5Unified

Pour utiliser des fonctions spécifiques à la carte M5Stack Core 2, il est nécessaire d'ajouter au projet la bibliothèque fournie par le fabricant : 

![Installation bibliothèque M5Unified](./img/platform_io_lib_step_1.png){.align-center}

Cherchez `M5` et installez `M5GFX` et `M5Unified` : 

![Installation bibliothèque M5Unified](./img/platform_io_lib_step_2.png){.align-center}

> M5 a regroupé les bibliothèques de ses différentes cartes dans une seule et même bibliothèque nommée `M5Unified` qui elle-même dépend de `M5GFX`. Faites attention de bien installer ces deux bibliothèques et non pas `M5Stack` ou `M5Core2` {.is-warning}

| Bibliothèque  | Statut                  | Rôle principal                                                                             | Cible                                               |
| ------------- | ----------------------- | ------------------------------------------------------------------------------------------ | --------------------------------------------------- |
| **M5Stack**   | Ancienne / remplacée | Support initial des premières cartes M5Stack (Basic, Gray, Fire)                           | ESP32 (anciens modèles)                             |
| **M5Core2**   | Ancienne / remplacée | Ajout du support spécifique du modèle Core2                                                | M5Stack Core2                                       |
| **M5GFX**     | Active               | Gestion graphique (affichage, polices, sprites, etc.) ultra-optimisée                      | Tous les appareils M5                               |
| **M5Unified** | Active               | Framework unifié qui gère automatiquement l’écran, les boutons, le son, les capteurs, etc. | Tous les modèles récents (Core, Core2, Tough, etc.) |


Recopiez le programme suivant dans le fichier `main.cpp` du dossier `src`:

```cpp
#include <M5Unified.h>

void setup() {
    auto cfg = M5.config();

    M5.begin(cfg);

    auto &disp = M5.Display;

    disp.setTextSize(2);
    disp.setTextColor(TFT_YELLOW);
    disp.setCursor(80, 0);
    disp.println("Hello World !");
}

void loop() {
    M5.update();
    
}
```

Pour compiler et téléverser le programme (le déposer sur la carte) utilisez les actions rapides en bas à gauche : 

![Installation bibliothèque M5Unified](./img/platform_io_launch_1.png){.align-center}

Lors du premier lancement, PlatformIO doit compiler les bibliothèques tiers, cela peut prendre un peu de temps : 

![Installation bibliothèque M5Unified](./img/platform_io_launch_2.png){.align-center}

### Spécification du M5Stack Core 2

![m5stack_core2.webp](./img/m5stack_core2.webp =280x){.align-center}

![m5stack_core2.webp](./img/m5stack_core2_plan.webp =280x){.align-center}

La carte M5 repose sur un microcontrôleur ESP32 (MCU) : 
- ESP32-D0WDQ6-V3 (Wi-Fi + Bluetooth/BLE)
- 16 MB Flash, 8 MB PSRAM

Elle propose en plus une liste de modules intégrés avec lesquels vous pouvez directement intéragir (sans nécéssiter de branchements/extensions supplémentaires).

**Liste des modules intégrés au M5Stack Core 2 :**
- Affichage & entrée utilisateur
	- Écran LCD IPS 2" 320×240
	- Contrôleur tactile capacitif FT6336U
	- 3 boutons tactiles virtuels en façade
	- Bouton POWER physique
	- Bouton RESET physique
- Capteurs & “périphériques intélligents”
	- IMU 6-axes MPU6886 (accel + gyro)
	- RTC BM8563 (horloge temps réel) + petite batterie de sauvegarde
	- Microphone PDM (SPM1423 ou similaire)
	- Audio, feedback & LED
	- Haut-parleur 1 W avec ampli I²S
	- Moteur de vibration (feedback haptique)
	- LED d’alimentation (power indicator)
- Alimentation & mesure
	- PMIC AXP192 (Core2) ou AXP2101 + INA3221 (Core2 v1.1) pour la gestion de l’alim et la mesure de courant (3-channels mA-meter) 
	- Batterie LiPo interne (390–500 mAh)
	- Port USB-C (alim + charge + debug/flash)
- Stockage & bus d’extension
	- Slot micro-SD (TF-card)
	- Connecteur M-Bus au dos (toutes les IO ESP32 et alimentations vers les modules/bases M5Stack)
	- Port Grove (I²C + IO/UART)

Spécification complète : https://docs.m5stack.com/en/core/core2

### Programme compteur

En utilisant la documentation en ligne concernant `M5Stack` `M5Unified` et `M5GFX` écrivez un programme "compteur" : 

- affichez l'état actuel du compteur à l'écran
- incrémentez le compteur lors de l'appuie sur le bouton A
- décrémentez le compteur lors de l'appuie sur le bouton B.


## 2 - Hello sensors ! *(en binôme)*

En plus des capteurs et actionneurs intégrés à la carte M5Stack Core 2 il est possible d'en ajouter d'autres en utilisant les GPIO (*G*eneral *P*urpose *I*nput *O*uput) ou le port Grove présent sur la carte.

Ces périphériques doivent alors "discuter" avec l'ESP32 en utilisant différents protocoles : 

- SPI
- I2C
- BUS CAN
- UART

*Recherchez de la documentation concernant chacun de ces protocoles : précisez les usages associés ainsi que leurs avantages et inconvénients.*

Voici la liste des capteurs  votre dispositions : 

- https://www.gotronic.fr/art-module-m5stickc-plus-k016-p-33740.htm
- https://www.gotronic.fr/art-module-core2-k010-32909.htm
- https://www.gotronic.fr/art-module-bus-m024-30355.htm
- https://www.gotronic.fr/art-module-crypto-authentication-u124-34036.htm
- https://www.gotronic.fr/art-module-iot-sim7080g-cat-m-nb-iot-u128-34408.htm
- https://www.gotronic.fr/art-capteur-de-temperature-ir-u028-34025.htm
- https://www.gotronic.fr/art-module-ethernet-rj45-u129-34407.htm
- https://www.gotronic.fr/art-module-lcd-1-14-u120-34037.htm
- https://www.gotronic.fr/art-capteur-de-mouvements-u127-34409.htm
- https://www.gotronic.fr/art-module-bouton-poussoir-u027-34024.htm

Parmis ces modules choisissez-en 1 et rédigez une fiche au format markdown à partir [de ce template](./img/fiche_identite_unite_m5stack_template.txt) incluant : 

- Le nom et la référence du module
- Son rôle / fonction principale
- Le branchement 
- Les protocoles utilisables
- Les bibliothèques nécessaires
- Un programme Hello World utilisant le framework Ardunion (C/C++)

(exemple [ici](./img/fiche_identite_m5stack_button_unit_exemple.txt))

## Troubleshooting

Me solliciter si vous avez l'erreur suivante lors de la compilation : 

![Installation bibliothèque M5Unified](./img/platform_io_launch_failed.png){.align-center}

## Liens 

- Documentation de PlatformIO [https://docs.platformio.org/en/latest/what-is-platformio.html](https://docs.platformio.org/en/latest/what-is-platformio.html)
- Setup M5Unified via PlatformIO https://docs.m5stack.com/en/arduino/m5unified/intro_vscode
- M5GFX (affichage) https://docs.m5stack.com/en/arduino/m5gfx/m5gfx
- Référence API M5Unified https://docs.m5stack.com/en/arduino/m5unified/button_class
- Exemple de programme "Button" https://docs.m5stack.com/en/arduino/m5core2/button
- Forum communautaire M5Stack https://community.m5stack.com/