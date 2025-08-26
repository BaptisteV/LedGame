#include <Arduino.h>
#include <memory>
#include <parkour/ParkourGame.hpp>

std::unique_ptr<ParkourGame> game;
const bool autoplay = true;

void setup()
{
    Serial.begin(115200);
    Serial.println("Creating game...");
    game = std::unique_ptr<ParkourGame>(new ParkourGame(autoplay));
    Serial.println("show...");
    game->show();
}

void loop()
{
    try
    {
        game->tick();
        EVERY_N_MILLISECONDS(5)
        {
            game->update();
            game->show();
        }
    }
    catch (std::exception &e)
    {
        Serial.printf("Unhandled exception: %s\n", e.what());
        Serial.println("Restarting game...");
        game.reset(new ParkourGame(autoplay));
    }
}