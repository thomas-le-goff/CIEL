#include <M5Unified.h>
#include <lvgl_freertos_glue.hpp>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LV_CONF_INCLUDE_SIMPLE
#include <lvgl.h>

const uint NUMBER_OF_TRACK = 5;

const lv_color_t SNCF_BLUE = lv_color_hex(0x053c99);
const lv_color_t SNCF_BLUE_2 = lv_color_hex(0x0b1f5e);
const lv_color_t SNCF_YELLOW = lv_color_hex(0xe3ff72);
const lv_color_t SNCF_WHITE = lv_color_hex(0xffffff);

SemaphoreHandle_t lvgl_mutex = NULL;

typedef struct
{
  int id;
  char train_id[16];
  char destination[32];
  time_t time;
} Departure;

typedef struct
{
  QueueHandle_t departure_queue;
} TaskDeparturesParams;

static void table_draw_event_cb(lv_event_t *e)
{
  lv_draw_task_t *draw_task = lv_event_get_draw_task(e);
  lv_draw_dsc_base_t *base_dsc = (lv_draw_dsc_base_t *)lv_draw_task_get_draw_dsc(draw_task);

  if (base_dsc->part == LV_PART_ITEMS)
  {
    uint32_t row = base_dsc->id1;
    uint32_t col = base_dsc->id2;

    lv_color_t background_color = SNCF_BLUE;
    if (row % 2 == 0)
    {
      background_color = SNCF_BLUE_2;
    }

    lv_draw_fill_dsc_t *fill_draw_dsc = lv_draw_task_get_fill_dsc(draw_task);
    if (fill_draw_dsc)
    {
      fill_draw_dsc->color = background_color;
    }

    lv_color_t text_color = SNCF_WHITE;
    if (col == 2)
    {
      text_color = SNCF_YELLOW;
    }

    lv_draw_label_dsc_t *label_draw_dsc = lv_draw_task_get_label_dsc(draw_task);
    if (label_draw_dsc)
    {
      label_draw_dsc->color = text_color;
    }
  }
}

static lv_obj_t *create_departure_table(void)
{
  lv_obj_t *table = lv_table_create(lv_screen_active());

  lv_table_set_column_width(table, 1, 100);
  lv_table_set_column_width(table, 2, 80);

  lv_obj_set_height(table, lv_pct(100));
  lv_obj_set_width(table, lv_pct(100));

  lv_obj_center(table);

  // Styles
  lv_obj_add_event_cb(table, table_draw_event_cb, LV_EVENT_DRAW_TASK_ADDED, NULL);
  lv_obj_add_flag(table, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);
  lv_obj_set_style_bg_color(table, SNCF_BLUE, LV_PART_MAIN);
  lv_obj_set_style_bg_color(table, SNCF_BLUE, LV_PART_ITEMS);

  lv_obj_set_style_border_color(table, SNCF_BLUE, LV_PART_MAIN);
  lv_obj_set_style_border_color(table, SNCF_BLUE, LV_PART_ITEMS);

  return table;
}

static lv_obj_t *create_alert_msgbox(void)
{
  lv_obj_t *msgbox = lv_msgbox_create(lv_screen_active());

  lv_obj_set_size(msgbox, lv_pct(50), lv_pct(50));
  lv_obj_set_pos(msgbox, 0, 0);

  lv_msgbox_add_text(msgbox, "Attention au passage d'un train.");

  // Styles
  lv_obj_set_style_bg_color(msgbox, lv_color_hex(0xB00020), LV_PART_MAIN);
  lv_obj_set_style_bg_opa(msgbox, LV_OPA_COVER, LV_PART_MAIN);
  lv_obj_set_style_border_color(msgbox, lv_color_hex(0xFF5252), LV_PART_MAIN);
  lv_obj_set_style_border_width(msgbox, 0, LV_PART_MAIN);

  lv_obj_t *label = lv_msgbox_get_content(msgbox);
  lv_obj_set_size(label, lv_pct(80), lv_pct(80));
  lv_obj_set_style_text_color(label, lv_color_white(), 0);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
  lv_obj_center(label);

  return msgbox;
}

static void format_time(time_t t, char *buffer, size_t buffer_size)
{
  uint16_t hours = t / 3600;
  uint8_t minutes = (t % 3600) / 60;
  snprintf(buffer, buffer_size, "%02uH%02u", hours, minutes);
}

static lv_obj_t *alertbox = NULL;

static void ui_show_alert_cb(void *param)
{
  if (alertbox == NULL)
  {
    alertbox = create_alert_msgbox();
  }
}

static void ui_close_alert_cb(void *param)
{
  if (alertbox != NULL)
  {
    lv_msgbox_close(alertbox);
    alertbox = NULL;
  }
}

void taskLvglUpdate(void *pvParameters)
{
  const TickType_t delay = pdMS_TO_TICKS(50);
  TickType_t last_wake_time = xTaskGetTickCount();

  for (;;)
  {
    if (xSemaphoreTake(lvgl_mutex, portMAX_DELAY) == pdTRUE)
    {
      lfg_m5::update();
      xSemaphoreGive(lvgl_mutex);
    }
    xTaskDelayUntil(&last_wake_time, delay);
  }
}

void taskDeparturesRender(void *pvParameters)
{
  TaskDeparturesParams *params = (TaskDeparturesParams *)pvParameters;
  const TickType_t delay = pdMS_TO_TICKS(100);

  lv_obj_t *table = create_departure_table();
  Departure *departures = NULL;
  size_t departures_count = 0;

  for (;;)
  {
    Departure d;
    if (xQueueReceive(params->departure_queue, &d, portMAX_DELAY) == pdTRUE)
    {
      if (d.id >= departures_count)
      {
        departures_count = d.id + 1;
        departures = (Departure *)realloc(departures, departures_count * sizeof(Departure));
      }
      departures[d.id] = d;
    }

    if (xSemaphoreTake(lvgl_mutex, portMAX_DELAY) == pdTRUE)
    {
      for (size_t row = 0; row < departures_count; row++)
      {
        char time_str[6];
        format_time(departures[row].time, time_str, sizeof(time_str));

        lv_table_set_cell_value(table, row, 0, departures[row].train_id);
        lv_table_set_cell_value(table, row, 1, departures[row].destination);
        lv_table_set_cell_value(table, row, 2, time_str);
      }
      xSemaphoreGive(lvgl_mutex);
    }
    vTaskDelay(delay);
  }
}

// DEBUT DU CODE A COMPLETER

QueueHandle_t track_alert_queue;

// TODO 1. Simulation des départs (taskDeparturesUpdateMock)
// Tâche de mise à jour des départs (mock)
// Objectif : Envoyer des données de départs (simulées) dans la queue `departure_queue`
// - Initialiser un tableau de 5 départs (ex: TER 89569, TER 52631, etc.)
// - Envoyer chaque départ dans la queue au démarrage
// - Toutes les 10 secondes, mettre à jour l'heure d'un départ aléatoire (+10 minutes)
//   et envoyer la mise à jour dans la queue
void taskDeparturesUpdateMock(void *pvParameters)
{
  TaskDeparturesParams *params = (TaskDeparturesParams *)pvParameters;

  const TickType_t delay = pdMS_TO_TICKS(10000);

  bool initial_update_sent = false;

  // TODO: Déclarer et initialiser un tableau de 5 départs
  // Exemple : Departure departures[5] = {
  //     {0, "TER 89569", "Rennes", (15 * 3600) + (15 * 60)},
  //     {1, "TER 52631", "Paris", (16 * 3600) + (45 * 60)},
  //     ...
  // };

  for (;;)
  {
    // TODO: Envoyer tous les départs dans la queue au démarrage (une seule fois, astuce : utiliser la variable initial_update_sent, astuce 2 : comment traiter tout les éléments d'un tableau ?)

    // TODO: Toutes les 10 secondes, choisir un départ aléatoire (dans la liste des départs),
    //       mettre à jour son heure (+10 minutes) et envoyer la mise à jour dans la queue
    // L'idée est de "simuler" la mise à jour d'un départ (retard) et d'envoyer cette modification dans la queue pour mettre à jour l'affichage.
    // astuce : prenez le temps de lire taskDeparturesRender pour comprendre ce dont elle a besoin pour mettre à jour l'affichage.

    vTaskDelay(delay);
  }
}

// 2. Gestion des alertes (taskTrackRender)

// Tâche de mise à jour des alertes voies
void taskTrackUpdateMock(void *pvParameters)
{
  // Fonctionnelle, mais peut être améliorée ...
  const TickType_t period = pdMS_TO_TICKS(60000);

  for (;;)
  {
    int track_number = rand() % (NUMBER_OF_TRACK - 1) + 1;
    xQueueSend(track_alert_queue, &track_number, 0);
    vTaskDelay(period);
  }
}

// TODO Tâche d'affichage des alertes
// Objectif :
// - Afficher une popup à chaque reception d'une alerte correspondant à la voie actuelle
void taskTrackRender(void *pvParameters)
{
  const TickType_t display_time = pdMS_TO_TICKS(10000);

  for (;;)
  {
    // TODO: Recevoir un numéro de voie depuis la queue
    // TODO: Vérifier que le numéro correspond à la voie actuelle
    // TODO: Afficher l'alerte avec lv_async_call(ui_show_alert_cb, NULL)
    // TODO: Attendre 10 secondes
    // TODO: Masquer l'alerte avec lv_async_call(ui_close_alert_cb, NULL)
  }
}

void setup()
{
  lvgl_mutex = xSemaphoreCreateMutex();

  // Cette variable contient le numéro de la voie ou est présent l'affichage
  static const int track_number = 1;

  static QueueHandle_t departure_queue = xQueueCreate(10, sizeof(Departure));
  track_alert_queue = xQueueCreate(10, sizeof(int));

  static TaskDeparturesParams task_departures_params = {.departure_queue = departure_queue};

  Serial.begin(115200);

  M5.begin();
  lfg_m5::init();

  lv_obj_set_style_bg_color(lv_screen_active(), SNCF_BLUE, LV_PART_MAIN);

  xTaskCreatePinnedToCore(taskLvglUpdate, "LVGL", 8128, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(taskDeparturesRender, "DEP_RENDER", 8128, &task_departures_params, 1, NULL, 0);
  xTaskCreatePinnedToCore(taskTrackUpdateMock, "TRACK_UPDATE", 8128, nullptr, 1, NULL, 0);

  // TODO: penser à créer des instances des tâches ajoutées.
  // à vous de trouver les paramètres les mieux adaptés...
}

// FIN DU CODE A COMPLETER

void loop()
{
  static const TickType_t period = pdMS_TO_TICKS(1000);
  vTaskDelay(period);
}
