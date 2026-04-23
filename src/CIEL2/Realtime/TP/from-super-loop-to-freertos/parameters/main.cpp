#include <Arduino.h>
#include <M5Unified.h>

M5GFX &display = M5.Display;

typedef struct TaskColorParams
{
  unsigned int period;
  bool flg;
  int color;
} TaskColorParams_t;

typedef struct TaskDrawParams
{
  TaskColorParams_t *squares[2];
} TaskDrawParams_t;

void TaskColor(void *pvParameters)
{
  TaskColorParams_t *params = (TaskColorParams_t *)pvParameters;
  int periodInTicks = pdMS_TO_TICKS(params->period);

  for (;;)
  {
    params->flg = !params->flg;
    vTaskDelay(periodInTicks);
  }
}

void TaskDraw(void *pvParameters)
{
  TaskDrawParams_t *params = (TaskDrawParams_t *)pvParameters;
  const TickType_t delayTicks = pdMS_TO_TICKS(50);
  uint32_t counter = 0;

  for (;;)
  {
    M5.update();

    display.startWrite();

    for (size_t i = 0; i < 2; i++)
    {
      TaskColorParams_t *square = params->squares[i];
      Serial.println(square->color);
      Serial.println(square->flg);
      display.fillRect(100 + 50 * i, 50, 50, 50, square->flg ? square->color : TFT_BLACK);
    }

    display.endWrite();

    if ((counter++ % 20) == 0)
    {
      Serial.printf("Draw core=%d\n", xPortGetCoreID());
    }
    vTaskDelay(delayTicks);
  }
}

void setup()
{
  auto cfg = M5.config();
  M5.begin(cfg);

  Serial.begin(115200);

  display.setBrightness(255);
  display.clear();

  static TaskColorParams_t paramsBlue;
  static TaskColorParams_t paramsRed;
  static TaskDrawParams_t paramsDraw;

  paramsBlue.period = 1000;
  paramsBlue.flg = true;
  paramsBlue.color = TFT_BLUE;

  paramsRed.period = 3000;
  paramsRed.flg = true;
  paramsRed.color = TFT_RED;

  paramsDraw.squares[0] = &paramsBlue;
  paramsDraw.squares[1] = &paramsRed;

  xTaskCreatePinnedToCore(TaskColor, "La tâche bleue", 1024, &paramsBlue, 1, NULL, 0);
  xTaskCreatePinnedToCore(TaskColor, "La tâche rouge", 1024, &paramsRed, 1, NULL, 0);
  xTaskCreatePinnedToCore(TaskDraw, "La tâche draw", 8128, &paramsDraw, 1, NULL, 1);
}

void loop()
{
  vTaskDelay(1000);
}