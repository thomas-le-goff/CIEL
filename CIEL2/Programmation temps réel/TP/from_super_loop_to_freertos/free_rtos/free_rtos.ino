#include <Arduino.h>
#include <M5GFX.h>
#include <M5Unified.h>

M5GFX display;

volatile bool flg_red = false;
volatile bool flg_blue = false;

void TaskRed(void *pvParameters)
{
  const TickType_t delayTicks = pdMS_TO_TICKS(1000);

  for (;;)
  {
    flg_red = !flg_red;

    Serial.printf("%s: %d\n", "TaskRed", xPortGetCoreID());
    vTaskDelay(delayTicks);
  }
}

void TaskBlue(void *pvParameters)
{
  const TickType_t delayTicks = pdMS_TO_TICKS(3000);

  for (;;)
  {
    flg_blue = !flg_blue;

    Serial.printf("%s: %d\n", "TaskBlue", xPortGetCoreID());
    vTaskDelay(delayTicks);
  }
}

void TaskDraw(void *pvParameters)
{

  const TickType_t delayTicks = pdMS_TO_TICKS(50);
  uint32_t counter = 0;

  for (;;)
  {
    display.startWrite();

    display.fillRect(100, 50, 50, 50, flg_blue ? TFT_BLUE : TFT_BLACK);
    display.fillRect(50, 50, 50, 50, flg_red ? TFT_RED : TFT_BLACK);

    display.display();
    display.endWrite();

    if ((counter++ % 20) == 0)
    {
      Serial.printf("Draw core=%d\n", xPortGetCoreID());
    }

    vTaskDelay(delayTicks);
  }
}

void setup(void)
{
  auto cfg = M5.config();

  M5.begin(cfg);

  Serial.begin(115200);

  display = M5.Display;

  display.begin();
  display.clear();

  xTaskCreatePinnedToCore(TaskRed, "RedTask", 8192, nullptr, 2, nullptr, 0);
  xTaskCreatePinnedToCore(TaskBlue, "BlueTask", 8192, nullptr, 2, nullptr, 0);
  xTaskCreatePinnedToCore(TaskDraw, "TaskDraw", 8192, nullptr, 2, nullptr, 1);
}

void loop(void)
{
  static const TickType_t delayTicks = pdMS_TO_TICKS(50);

  M5.update();
  vTaskDelay(delayTicks);
}