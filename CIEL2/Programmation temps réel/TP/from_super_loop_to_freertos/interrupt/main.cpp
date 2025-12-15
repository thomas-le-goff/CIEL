#include <Arduino.h>
#include <M5GFX.h>
#include <M5Unified.h>

#define TOUCH_PANEL_INTERRUPT_PIN 39

QueueHandle_t controlSemaphore = nullptr;
bool flg_red = false;
bool flg_blue = false;

LGFX_Button button;

static void TaskRed(void *pvParameters)
{
  const TickType_t delayTicks = pdMS_TO_TICKS(1000);

  for (;;)
  {
    flg_red = !flg_red;

    Serial.printf("%s: %d\n", "TaskRed", xPortGetCoreID());
    vTaskDelay(delayTicks);
  }
}

static void TaskBlue(void *pvParameters)
{
  const TickType_t delayTicks = pdMS_TO_TICKS(3000);

  for (;;)
  {
    flg_blue = !flg_blue;

    Serial.printf("%s: %d\n", "TaskBlue", xPortGetCoreID());
    vTaskDelay(delayTicks);
  }
}

static void InterruptHandler(void)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  xSemaphoreGiveFromISR(controlSemaphore, &xHigherPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

typedef struct TaskControlParams
{
  TaskHandle_t controlledTask;
  LGFX_Button button;
  bool softMode;
} TaskControlParams_t;

static void TaskControl(void *pvParameters)
{
  TaskControlParams_t *params = (TaskControlParams_t *)pvParameters;

  m5::touch_detail_t touchDetail;
  bool isEnabled = true;

  for (;;)
  {
    bool newState = isEnabled;

    if (params->softMode)
    {
      touchDetail = M5.Touch.getDetail();

      if (touchDetail.wasPressed())
      {
        Serial.printf("Touch button pressed on core=%d\n", xPortGetCoreID());
        newState = !newState;
      }
    }
    else
    {
      xSemaphoreTake(controlSemaphore, portMAX_DELAY);
      Serial.printf("Touch interrupt handled on core=%d\n", xPortGetCoreID());
      // Todo control if button is clicked.
      newState = !newState;
    }

    if (isEnabled != newState && params->controlledTask != nullptr)
    {
      isEnabled = newState;

      if (!isEnabled)
      {
        Serial.printf("Controlled task suspended\n");
        vTaskSuspend(params->controlledTask);
      }
      else
      {
        Serial.printf("Controlled task resumed\n");
        vTaskResume(params->controlledTask);
      }
    }

    if (params->softMode)
    {
      vTaskDelay(pdMS_TO_TICKS(50));
    }
  }
}

static void TaskDraw(void *pvParameters)
{
  const TickType_t delayTicks = pdMS_TO_TICKS(50);
  uint32_t counter = 0;

  M5GFX display;

  display.begin();
  display.clear();

  for (;;)
  {
    M5.update();

    display.startWrite();
    {
      display.fillRect(100, 50, 50, 50, flg_blue ? TFT_BLUE : TFT_BLACK);
      display.fillRect(50, 50, 50, 50, flg_red ? TFT_RED : TFT_BLACK);

      display.display();
    }
    display.endWrite();

    button.drawButton();

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

  int w = M5.Lcd.width();
  int h = M5.Lcd.height();

  button.initButton(&M5.Lcd, w / 2, h / 2, 200, 50, TFT_BLUE, TFT_YELLOW, TFT_BLACK, "BTN", 4, 4);

  controlSemaphore = xSemaphoreCreateBinary();

  if (controlSemaphore != NULL)
  {
    TaskHandle_t blueTaskHandle = nullptr;
    TaskHandle_t redTaskHandle = nullptr;

    xTaskCreatePinnedToCore(TaskDraw, "TaskDraw", 8192, nullptr, 1, nullptr, 1);

    xTaskCreate(TaskRed, "RedTask", 8192, nullptr, 1, &redTaskHandle);
    xTaskCreate(TaskBlue, "BlueTask", 8192, nullptr, 1, &blueTaskHandle);

    static TaskControlParams_t taskControlParams;

    taskControlParams.controlledTask = blueTaskHandle;
    taskControlParams.button = button;
    taskControlParams.softMode = false;

    xTaskCreate(TaskControl, "ControlTask", 8192, &taskControlParams, 3, nullptr);

    pinMode(TOUCH_PANEL_INTERRUPT_PIN, INPUT_PULLUP);
    attachInterrupt(TOUCH_PANEL_INTERRUPT_PIN, InterruptHandler, FALLING);
  }
}

void loop(void)
{
  static const TickType_t delayTicks = pdMS_TO_TICKS(50);
  vTaskDelay(delayTicks);
}