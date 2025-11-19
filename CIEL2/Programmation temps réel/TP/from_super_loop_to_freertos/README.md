# TP - From Super Loop to FreeRTOS

L'objectif de ce TP est de montrer l'intérêt d'un **RTOS** pour gérer plusieurs tâches sur un système embarqué.

## 1\. Gestion du temps sans RTOS

_1.1 - À partir du programme ci-dessous, faites en sorte que le carré **bleu** clignote toutes les **secondes** et le carré **rouge** toutes les **trois secondes**._

```c++
#include <Arduino.h>
#include <M5GFX.h>

M5GFX display;

bool flg_red = false;
bool flg_blue = false;

void setup(void) {
  display.begin();
  display.clear();
}

void loop(void) {
  flg_red = !flg_red;
  flg_blue = !flg_blue;

  display.startWrite();

  display.fillRect(50, 50, 50, 50, flg_red ? TFT_RED : TFT_BLACK);
  display.fillRect(100, 50, 50, 50, flg_blue ? TFT_BLUE : TFT_BLACK);

  display.display();
  display.endWrite();

  delay(1000);
}
```

Deux approches possibles :

- **Time slicing** : cadencer la superloop (ex. 100 ms) et compter le temps écoulé.
- **Non‑blocking timing** : utiliser `millis()` pour déclencher sans bloquer avec `delay()`.

_1.2 - Quels sont les inconvénients de cette méthode ? Donnez des cas où cette approche n'est pas possible._

_1.3 - Que se passe‑t‑il si on appelle la fonction suivante dans la boucle principale ?_

```c++
void http_task_with_delay() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://httpbin.org/delay/5");
    int code = http.GET();

    if (code > 0) {
      String payload = http.getString();
      Serial.printf("[HTTP] Code: %d, Réponse: %.50s...\n", code, payload.c_str());
    } else {
      Serial.printf("[HTTP] Erreur: %s\n", http.errorToString(code).c_str());
    }

    http.end();
  } else {
    Serial.println("[HTTP] WiFi non connecté");
  }
}
```

Si pas de WiFi disponible :

```c++
void http_task_with_delay_sadder() {
  unsigned long d = random(10, 10000);
  delay(d);
}
```

> **Observation :** tant qu'une fonction bloquante s'exécute, **tout** le programme est gelé. À mesure que le projet grandit, la logique devient difficile à maintenir et certains cas non‑triviaux peuvent mettre le système en défaut.

--------------------------------------------------------------------------------

## 2\. Passage au temps réel

Un RTOS répond précisément à ce besoin.

_2.1 - Avant de rendre le code compatible FreeRTOS, listez les tâches à accomplir par le système (3 attendues) :_

- ...
- ...
- ...

### Création d'une tâche FreeRTOS

Dans FreeRTOS, une tâche est une fonction avec une boucle infinie :

```c++
void TaskRed(void* pv) {
  // Initialisation
  for (;;) {
    // Code de la tâche
  }
}
```

> En fait il s'agit de l'architecture superloop, mais, dédiée à la tâche.

Une fois la tâche écrite, il faut demander à FreeRTOS de créer une instance de cette tâche (l'exécuter) à l'aide de la fonction `xTaskCreate`:

```c++
#include <Arduino.h>
#include <M5GFX.h>

M5GFX display;

void TaskRed(void* pv) {

  for (;;) {
  }
}

void setup(void) {
  display.begin();
  display.clear();

  xTaskCreate(TaskRed,  "RedTask",  8192, nullptr, 2, nullptr);
}

void loop(void) {
  // loop est aussi vu comme une "tâche" on peut l'ignorer pour le moment 
}
```

> Documentation utile : [xTaskCreate (FreeRTOS API Reference)](https://www.freertos.org/Documentation/02-Kernel/04-API-references/01-Task-creation/00-TaskHandle)

_2.2 - En partant du squelette ci-dessus, implémentez la logique pour faire clignoter **et** dessiner le carré rouge._

_2.3 - Ajoutez une seconde tâche pour faire clignoter **et** dessiner le carré bleu._

_2.4 - Qu'est‑ce qui vous semble problématique dans ce code ? Qu'est‑ce qui ne vous plaît pas ?_

> Piste : collisions d'accès à l'écran (I²C/SPI), besoin de sérialiser l'affichage, etc.

> Piste N°2 : <https://www.hackster.io/Niket/tasks-parametertotasks-freertos-tutorial-5-b8a7b7>

### Partage de ressource

Lorsque deux tâches partagent la même ressource (ici l'écran), des accès concurrents peuvent provoquer :

- artefacts (transactions SPI entremêlées),
- blocages si l'API n'est pas thread‑safe,
- tearing si des écritures se chevauchent.

Quand ce genre de cas se présente, on peut utiliser un mécanisme de **mutex** pour "privatiser" l'accès à la ressource ou, plus simple ici :

**Une unique tâche dédiée à l'affichage**.

On obtient, alors, la liste de tâches suivante :

1. une tâche qui change l'état du carré rouge
2. une tâche qui change l'état du carré bleue
3. une tâche qui fait la requête HTTP très lente
4. une tâche qui dessine les deux carrés

_2.5 - Adaptez les tâches 1 et 2 pour ne plus dessiner directement et écrivez une tâche 4 `TaskDraw` qui affiche les deux carrés en lisant leurs états._

--------------------------------------------------------------------------------

## 3\. Arrêt d'urgence

Les tâches que nous avons vu jusqu'a présent sont similaires :

- elles s'executent périodiquement ;
- elles ont la même priorité.

L'ajout d'un bouton d'arrêt d'urgence nécessiterait un autre type de tâche :

- non périodique (basé sur un evénement extérieur au système);
- hautement prioritaire.
