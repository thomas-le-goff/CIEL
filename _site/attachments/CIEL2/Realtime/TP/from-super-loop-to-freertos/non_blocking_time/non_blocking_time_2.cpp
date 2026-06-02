#include <Arduino.h>
#include <M5GFX.h>
#include <M5Unified.h>

M5GFX display;

bool flg_red = false;
bool flg_blue = false;

unsigned long ct_red = 0;
unsigned long ct_blue = 0;

void setup(void)
{
    auto cfg = M5.config();

    M5.begin(cfg);

    Serial.begin(9600);

    display = M5.Display;

    display.begin();
    display.clear();
}

void loop(void)
{
    // Update
    unsigned long now = millis();

    if (now - ct_red >= 3000)
    {
        ct_red = now;
        flg_red = !flg_red;
        Serial.print("Red changes: ");
        Serial.println(String(flg_red));
    }

    if (now - ct_blue >= 1000)
    {
        ct_blue = now;
        flg_blue = !flg_blue;
        Serial.print("Blue changes: ");
        Serial.println(String(flg_blue));
    }

    // Draw
    display.startWrite();

    display.fillRect(50, 50, 50, 50, flg_red ? TFT_RED : TFT_BLACK);
    display.fillRect(150, 50, 50, 50, flg_blue ? TFT_BLUE : TFT_BLACK);

    display.display();
    display.endWrite();
}