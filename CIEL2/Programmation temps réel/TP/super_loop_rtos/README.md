## Gestion du temps sans RTOS

Mettre en oeuvre deux tâches bloquantes sur Arduino et explorer des moyens simples de les rendre compatibles : 

- Time slicing : mise en place d'un delay de 100 ms pour cadencer la boucle principale (superloop) et ainsi être capable de compter le temps écoulé. Inconvénients : comment gérer d'autre type de traitement bloquant que l'attente d'un délais.

- Non-blocking time : utiliser des prémitive Arduino permettant de récupérer le temps écoulé depuis le début du programme et ainsi être capable d'attendre un certain temps sans utiliser l'instruction `delay` : comment faire avec d'autres tâches bloquantes (appel réseau etc.) (mise en avant de la nécessité d'utiliser une event loop)

Une fois ces deux programmes réalisés => faire la même chose en utilisant un système temps réel et ce rendre compte du gain.

1 - À partir du programme suivant faites en sorte que le carré bleu clignote toute les seconde et le rouge toute les deux secondes.

```cpp
#include <Arduino.h>
#include <M5GFX.h>

M5GFX display;
M5Canvas canvas[2];

bool flg_red = false;
bool flg_blue = false;

void setup(void)
{
  display.begin();
  display.clear();
}

void loop(void)
{
  // Update
  flg_red = !flg_red;
  flg_blue = !flg_blue;

  // Draw
  display.startWrite();

  display.fillRect(50, 50, 50, 50, flg_red ? TFT_RED : TFT_BLACK);
  display.fillRect(100, 50, 50, 50, flg_blue ? TFT_BLUE : TFT_BLACK);

  display.display();
  display.endWrite();

  delay(2000);
}
```

2 - Quels sont les inconvénients de cette solution ? Donnez des cas ou ce n'est pas possible de procéder ainsi.

> Le processeur ne fait rien (il attend) la plus part du temps. Cela devient problématique si des capteurs / module comme BLE / Wifi doivent être scruté en plus.

3 - Proposer une autre solution qui n'utilise pas la fonction `delay`

> Mise en place d'un compteur non bloquant en utilisant la fonction `millis`

4 - Que ce passe-t-il si on appel la méthode suivante dans la boucle principale ? 

```cpp
heavy_taskvoid heavy_task() {
  unsigned long d = random(10, 10000);
  delay(d);
}
```

Imaginez que cette `heavy_task` correspond à l'attente suite à un appel réseau et que le clignotement d'un carré correspond à la récupération des données d'un capteur (surveillance d'une température etc.). Est-ce que le comportement actuel vous semble envisageable ?

> L'objectif est de mettre en avant le fait que le côté deterministe d'un RTOS et la priorisation des tâches est nécessaire dans ce type de système.