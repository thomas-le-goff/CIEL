#include <Arduino.h>
#include <M5GFX.h>
#include <M5Unified.h>

M5GFX display;

bool flg_red = false;
bool flg_blue = false;

unsigned long ct_red = 0;
unsigned long ct_blue = 0;

bool handle_ct(unsigned long &ct, unsigned int goal)
{
  unsigned long now = millis();

  if (now - ct >= (goal * 1000))
  {
    ct = now;
    return true;
  }
  return false;
}

void heavy_task()
{
  unsigned long d = random(5000, 15000);
  Serial.print("Heavy task will take: ");
  Serial.print(String(d / 1000));
  Serial.println("s.");
  delay(d);
}

void setup(void)
{
  auto cfg = M5.config();

  M5.begin(cfg);

  Serial.begin(9600);

  display = M5.Display;

  display.begin();
  display.clear();

  ct_blue = ct_red = millis();
}

void loop(void)
{
  // Update

  if (handle_ct(ct_red, 4))
  {
    flg_red = !flg_red;
    Serial.print("Red changes: ");
    Serial.println(String(flg_red));
  }

  if (handle_ct(ct_blue, 1))
  {
    flg_blue = !flg_blue;
    Serial.print("Blue changes: ");
    Serial.println(String(flg_blue));
  }

  if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed())
  {
    heavy_task();
  }

  // Draw

  display.startWrite();

  display.fillRect(50, 50, 50, 50, flg_red ? TFT_RED : TFT_BLACK);
  display.fillRect(150, 50, 50, 50, flg_blue ? TFT_BLUE : TFT_BLACK);

  display.display();
  display.endWrite();
}