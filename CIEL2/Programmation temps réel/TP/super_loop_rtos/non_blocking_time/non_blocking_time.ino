#include <Arduino.h>
#include <M5GFX.h>

M5GFX display;
M5Canvas canvas[2];

bool flg_red = false;
bool flg_blue = false;

unsigned long ct_red = 0;
unsigned long ct_blue = 0;

void setup(void)
{
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
  }

  if (handle_ct(ct_blue, 1))
  {
    flg_blue = !flg_blue;
  }

  heavy_task();

  // Draw

  display.startWrite();

  display.fillRect(50, 50, 50, 50, flg_red ? TFT_RED : TFT_BLACK);
  display.fillRect(150, 50, 50, 50, flg_blue ? TFT_BLUE : TFT_BLACK);

  display.display();
  display.endWrite();
}

bool handle_ct(unsigned long& ct, unsigned int goal)
{
  unsigned long now = millis();

  if (now - ct >= (goal * 1000))
  {
    ct = now;
    return true;
  }
  return false;
}

void heavy_task() {
  unsigned long d = random(10, 10000);
  delay(d);
}