#pragma once
#include <map>
#include "constants/Hardware.hpp"
#include "Hsv.hpp"
#include "Direction.hpp"
#include "constants/Colors.hpp"

class PlayerRenderer
{
public:
    PlayerRenderer() {
    };
    void setup()
    {
        FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
        FastLED.setTemperature(ColorTemperature::WarmFluorescent);
        FastLED.clear();
        FastLED.show();
    };

    void render(int centerIndex, const Direction &direction)
    {
        std::vector<HSV> colors = getPlayerColors(direction);
        HSV headColor = colors[0];
        leds[centerIndex] = CHSV(headColor.hue, headColor.saturation, headColor.value);

        int indicatorIndex = (centerIndex - 1) % NUM_LEDS;
        HSV doubleColor = colors[1];
        leds[indicatorIndex] = CHSV(doubleColor.hue, doubleColor.saturation, doubleColor.value);
    }
};