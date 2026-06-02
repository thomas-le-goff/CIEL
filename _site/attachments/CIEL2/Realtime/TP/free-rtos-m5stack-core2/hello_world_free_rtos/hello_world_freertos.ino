#include <M5Unified.h>

void task1(void*) {
  for (;;) {
    M5_LOGI("Hello World");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void task2(void*) {
  M5.Display.setTextDatum(middle_center);
  M5.Display.setTextColor(TFT_BLACK);
  M5.Display.setTextFont(&fonts::Orbitron_Light_24);
  M5.Display.setTextSize(1);

  for (;;) {
    M5.Display.clear(TFT_WHITE);

    bool isCharging = M5.Power.isCharging();
    if (isCharging) {
      M5.Power.setLed(255);
    } else {
      M5.Power.setLed(0);
    }
    int vol_per = M5.Power.getBatteryLevel();
    int vol = M5.Power.getBatteryVoltage();
    int cur = M5.Power.getBatteryCurrent();

    M5.Display.setCursor(0, 30);
    M5.Display.printf("Charging: %s \n\n", isCharging ? "Yes" : "No");
    M5.Display.setCursor(0, 60);
    M5.Display.printf("Bat_level: %d%%", vol_per);
    M5.Display.setCursor(0, 90);
    M5.Display.printf("Bat_voltage: %d%mV", vol);
    M5.Display.setCursor(0, 120);
    M5.Display.printf("Bat_current: %d%mA", cur);

    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);

  M5.Log.setLogLevel(m5::log_target_serial, ESP_LOG_VERBOSE);
  M5.Log.setSuffix(m5::log_target_serial, "\n");

  xTaskCreate(task1, "t1", 4096, NULL, 1, NULL);
  xTaskCreate(task2, "t2", 4096, NULL, 1, NULL);
}

void loop() {
  M5.update();
}
