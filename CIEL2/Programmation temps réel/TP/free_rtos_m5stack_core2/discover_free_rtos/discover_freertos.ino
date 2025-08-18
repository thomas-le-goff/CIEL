#include <M5Unified.h>

// FreeRTOS Guide https://www.freertos.org/media/2018/161204_Mastering_the_FreeRTOS_Real_Time_Kernel-A_Hands-On_Tutorial_Guide.pdf

// 1 - Passing parameters to a task
// Q: Initialize a HelloTaskParameters to get a task with "Hello World" and another with "Bonjour le monde".
// Q: Draw time diagram of scheduled task.

typedef struct {
  char *text;
  int period;  // period in MS
} HelloTaskParameters;

void helloTask(void *parameters) {
  // Good practice here is to copy parameters to a task owned memory space.
  HelloTaskParameters *taskParameters = (HelloTaskParameters *)parameters;

  for (;;) {
    M5.Log(ESP_LOG_INFO, taskParameters->text);
    vTaskDelay(pdMS_TO_TICKS(taskParameters->period));
  }
}

// 2 - Task priority

// 3 - Producer / consumer

void producer(void *) {
}

void consumer(void *) {
}

// Entrypoint

HelloTaskParameters parametersA = { "Hello world", 2000 };
HelloTaskParameters parametersB = { "Bonjour le monde", 1000 };

void setup() {
  Serial.begin(115200);

  auto cfg = M5.config();
  M5.begin(cfg);

  M5.Log.setLogLevel(m5::log_target_serial, ESP_LOG_VERBOSE);
  M5.Log.setSuffix(m5::log_target_serial, "\n");

  // 1
  // First trap: parameters to task need to be in a scope that live as long as the task
  // otherwise parameters will be freed and the pointer is dangling to and empty memory space (or use for something else).
  // HelloTaskParameters parametersA = {"Hello World", 2000};

  // xTaskCreate(
  //   helloTask,             // Pointer to task function
  //   "hello world task",    // Task name
  //   4096,                  // Task stack depth
  //   (void *)&parametersA,  // Pointer to task paramaters
  //   1,                     // Task priority
  //   NULL                   // Pointer to task handle
  // );

  // xTaskCreate(
  //   helloTask,                // Pointer to task function
  //   "bonjour le monde task",  // Task name
  //   4096,                     // Task stack depth
  //   (void *)&parametersB,     // Pointer to task paramaters
  //   1,                        // Task priority
  //   NULL                      // Pointer to task handle
  // );
}

void loop() {
  M5.update();
}