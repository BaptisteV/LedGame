# Parkour Game

This is a 1D "Parkour" game displaying on a LED strip. You controle an LED moving along the LED strip faster and faster.
Set you own color using the buttons.

- Left button: 🟥
- Right button: 🟦
- Double click: 🦩

Your color must match the obstable's to be able to go through and survive.

## Dependencies

The following libraries are required:

*   `[fastled/FastLED](https://github.com/FastLED/FastLED)` -  Used for controlling the LED display
*   `[mathertel/OneButton](https://github.com/mathertel/OneButton)` -  Used for button input

The project uses [PlateformIO](https://docs.platformio.org/en/latest/).

## Hardware

*   ESP32-Dev board
*   LED strip (WS2812B, 144 LEDs)
*   Button

## Getting Started

1.  **Clone the repository**
2.  **Install PlatformIO**  If you don't have it already, install the PlatformIO IDE.
3.  **Open the project** Open the project in PlatformIO