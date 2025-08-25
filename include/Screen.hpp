#pragma once
#include <Wire.h>
#include <memory>
#include <Adafruit_SSD1306.h>

class Screen
{
private:
    std::unique_ptr<Adafruit_SSD1306> display;

    static const uint8_t SDA = 5;
    static const uint8_t SCL = 6;
    static const uint8_t I2CADDR = 0x3C;

public:
    static const int SCREEN_WIDTH = 64;
    static const int SCREEN_HEIGHT = 32;
    Screen()
    {
        display = std::unique_ptr<Adafruit_SSD1306>(new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire));
    };

    void setup()
    {
        if (!Wire.begin(SDA, SCL))
        {
            Serial.println("Échec Wire.begin");
        }

        // Initialiser l’écran OLED
        while (!display->begin(SSD1306_SWITCHCAPVCC, I2CADDR))
        {
            Serial.println("Échec allocation SSD1306");
        }

        display->ssd1306_command(SSD1306_DISPLAYON);
        display->setTextColor(SSD1306_WHITE);
        display->setTextSize(1);
        display->clearDisplay();
        display->display();
    };

    void drawText(const char *text, int x, int y)
    {
        display->clearDisplay();
        display->setCursor(x, y);

        display->println(text);

        display->display();
    };

    void clear()
    {
        display->clearDisplay();
        display->display();
    };
};