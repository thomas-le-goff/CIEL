# TP - De magnifiques interfaces avec LVGL
[LVGL](https://lvgl.io/) (**L**ight and **V**ersatile **G**raphics **L**ibrary) est une bibliothèque open-source pour créer des interfaces graphiques modernes sur des systèmes embarqués.

Voici quelques exemples d'**IHM** utilisant **LVGL** :

![lvgl_canvas.png](/ciel2/s2-2_system_temps_reel/lvgl_canvas.png)
![lvgl_canvas_2.png](/ciel2/s2-2_system_temps_reel/lvgl_canvas_2.png)

Vous pouvez voir d'autres exemples intéractifs ici : https://lvgl.io/demos

L'un des principal avantages de **LVGL** est qu'elle est écrite en C et utilisable sur une grande variété de cartes (dont M5Stack Core 2) : https://lvgl.io/demos. Il est même possible de faire des interfaces web native via WebAssembly.

# 1. Hello World

## Création du projet

> Ce TP se réalise en utilisant l'outil PlatformIO (si vous ne savez plus créer un projet : [TP - Hello M5Stack](/CIEL2/S2-1_LangageC/s2-1-1_TP_hello_m5stack)) {.is-info}

Créez un nouveau projet M5Stack Core 2 via PlatformIO. Une fois le projet créé il est **nécessaire d'ajouter des dépendances** : 

- M5GFX
- M5Unified
- LVGL

Votre fichier `platformio.ini` doit ressembler à celui-ci : 

```ini
[platformio]
default_envs = m5stack-core2 ; adaptez cette variable en fonction de votre carte

[env:m5stack-core2]
platform = espressif32
board = m5stack-core2
framework = arduino
monitor_speed = 115200
build_flags = 
	-DLV_CONF_PATH=\"${PROJECT_DIR}/include/lv_conf.h\"
lib_deps = 
	lvgl/lvgl@^9.4.0
	m5stack/M5GFX@^0.2.17
	m5stack/M5Unified@^0.2.11

[env:m5stack-cores3]
platform = espressif32
board = m5stack-cores3
framework = arduino
monitor_speed = 115200
build_flags = 
	-DLV_CONF_PATH=\"${PROJECT_DIR}/include/lv_conf.h\"
lib_deps = 
	lvgl/lvgl@^9.4.0
	m5stack/M5GFX@^0.2.17
	m5stack/M5Unified@^0.2.11
```

**LVGL** est paramétrable par le biais d'un fichier source (lv_conf.h). Il est nécessaire de fournir ce fichier dans la liste des sources. 

Assurez-vous d'avoir la ligne suivante dans votre fichier `platformio.ini` :

```ini
build_flags = 
	-DLV_CONF_PATH=\"${PROJECT_DIR}/include/lv_conf.h\"
```

Et ajoutez le fichier `lv_conf.h` ([récupérable ici](/ciel2/s2-2_system_temps_reel/lv_conf.h)) dans le dossier `include`.

Une fois le projet configuré, il est **nécessaire d'ajouter deux fichiers** dans le dossier `lib/lvgl_freertos_glue`: 
- `lvgl_freertos_glue.cpp` ([récupérable ici](/ciel2/s2-2_system_temps_reel/lvgl_freertos_glue.cpp))
- `lvgl_freertos_glue.hpp` ([récupérable ici](/ciel2/s2-2_system_temps_reel/lvgl_freertos_glue.hpp))

Ces fichiers permettent de faire la "colle" entre LVGL et FreeRTOS sur M5Stack.

Vous devriez avoir l'arborescence suivante :

```txt
|--lib
|  |--lvgl_freertos_glue
|  |  |- lvgl_freertos_glue.cpp
|  |  |- lvgl_freertos_glue.hpp
|--include
|  |--lv_conf.h
|--src
|  |--main.cpp
```

## Programme "Hello World!"

Copier le code suivant dans le fichier `src/main.cpp` afin d'afficher un texte "Hello World!" à l'aide d'un widget label :

```cpp
#include <Arduino.h>
#include <M5Unified.h>
#include <lvgl_freertos_glue.hpp>
#include <esp_timer.h>

#define LV_CONF_INCLUDE_SIMPLE
#include <lvgl.h>
#include <array>

void setup()
{
  M5.begin();
  lfg_m5::init();
  Serial.begin(115200);

  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);

  lv_obj_t *label = lv_label_create(lv_screen_active());
  lv_label_set_text(label, "Hello world!");
  lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void loop()
{
  lfg_m5::update();
  vTaskDelay(pdMS_TO_TICKS(1));
}
```

# 2. Carousel d'écrans

![screen_light.jpg](/ciel2/s2-2_system_temps_reel/screen_light.jpg =250x)

![screen_temp.jpg](/ciel2/s2-2_system_temps_reel/screen_temp.jpg =250x)

![screen_settings.jpg](/ciel2/s2-2_system_temps_reel/screen_settings.jpg =250x)

## Liens
- Documentation LVGL [https://docs.lvgl.io/master/](https://docs.lvgl.io/master/)
- Cheatsheet C++ [https://learnxinyminutes.com/fr/c++/](https://learnxinyminutes.com/fr/c++/)
- Référence C++ [https://cppreference.com/](https://cppreference.com/)
