#pragma once
#include "config/Hardware.hpp"
#include "Hsv.hpp"

// Configurable parameters
struct RenderConfig
{
    double width = 3.0;      // "spread" in LEDs (1.0 = between 2 LEDs, >1 = smoother blob)
    double fadeCurve = 3;    // >1 = sharper center, <1 = flatter
    double brightness = 1.0; // global intensity [0.0 – 1.0]
};
RenderConfig cfg;
class PlayerRenderer
{
public:
    PlayerRenderer() {
    };
    void setup()
    {
        Serial.println("FastLED setup");
        FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
        leds[0] = CRGB::White;
        leds[143] = CRGB::Red;
        FastLED.show();
        Serial.println("PlayerRenderer setup done");
    };

    // Gaussian-ish falloff
    double falloff(double dist, const RenderConfig &c)
    {
        return pow(max(0.0, 1.0 - dist / c.width), c.fadeCurve);
    }

    void render(double position, HSV color)
    {
        // Wrap position
        position = fmod(position, NUM_LEDS);
        if (position < 0)
            position += NUM_LEDS;

        int center = floor(position);

        // affect neighbors within "width"
        int spread = ceil(cfg.width);
        for (int offset = -spread; offset <= spread; offset++)
        {
            int index = (center + offset + NUM_LEDS) % NUM_LEDS;

            double dist = fabs(position - (center + offset));
            double intensity = falloff(dist, cfg) * cfg.brightness;

            if (intensity > 0.0)
            {
                uint8_t v = static_cast<uint8_t>(color.value * intensity);
                leds[index] += CHSV(color.hue, color.saturation, v);
            }
        }
    }

    //    void render(double position, HSV color)
    //    {
    //        int ledIndex = static_cast<int>(round(position)) % NUM_LEDS;
    //        Serial.printf("Player at position: %f => LED index: %d\n", position, ledIndex);
    //
    //        leds[ledIndex] = CHSV(color.hue, color.saturation, color.value);
    //    };
};
