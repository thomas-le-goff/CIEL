#include <Arduino.h>
#include <M5GFX.h>

M5GFX display;
M5Canvas canvas[2];

bool flg_red = false;
bool flg_blue = false;

unsigned int ct_red = 0;
unsigned int ct_blue = 0;

void setup(void)
{
  display.begin();
  display.clear();
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

  // Draw

  display.startWrite();

  display.fillRect(50, 50, 50, 50, flg_red ? TFT_RED : TFT_BLACK);
  display.fillRect(150, 50, 50, 50, flg_blue ? TFT_BLUE : TFT_BLACK);

  display.display();
  display.endWrite();

  delay(1000);
}

bool handle_ct(unsigned int& ct, unsigned int goal)
{
  if (ct >= goal)
  {
    ct = 0;
    return true;
  }

  ct += 1;
  return false;
}