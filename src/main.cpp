#include <Arduino.h>
#include <memory>
#include <parkour/ParkourGame.hpp>

std::unique_ptr<ParkourGame> game;

void setup()
{
    Serial.begin(115200);
    Serial.println("setup...");
    game = std::unique_ptr<ParkourGame>(new ParkourGame());
    Serial.println("show...");
    game->update();
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
        Serial.printf("Unhandled exception: %s, Restarting...\n", e.what());
        game.reset(new ParkourGame());
    }
}