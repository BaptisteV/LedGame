#pragma once
#include <FastLED.h>
#define LED_PIN 12
#define BTN_LEFT_PIN 33
#define BTN_RIGHT_PIN 32

#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define NUM_LEDS 144

CRGB leds_plus_safety_pixel[NUM_LEDS + 1];
CRGB *const leds = leds_plus_safety_pixel + 1;