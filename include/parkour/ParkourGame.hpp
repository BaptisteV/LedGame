#pragma once
#include <memory>
#include "config/Hardware.hpp"
#include "Player.hpp"
#include "Parkour.hpp"

class ParkourGame
{
private:
    std::unique_ptr<Player> player;
    std::unique_ptr<Parkour> parkour;
    bool autoplay = true;

public:
    ParkourGame()
    {
        player = std::unique_ptr<Player>(new Player(BTN_LEFT_PIN, BTN_RIGHT_PIN));
        parkour = std::unique_ptr<Parkour>(new Parkour());
    }

    void tick()
    {
        player->tick();
    }

    int previousPosition = 0;
    void update()
    {
        previousPosition = player->headIndex();
        player->move();
        const int position = player->headIndex();

        if (autoplay)
        {
            player->direction = parkour->nextCompatibleDirection(position);
        }

        if (parkour->crashesObstacle(player))
        {
            player->restart();
            parkour->regenerate();
        }

        bool loopsBack = (position == 0) && (previousPosition == NUM_LEDS - 1);
        if (loopsBack)
        {
            player->speedup();
            parkour->startNextParkour();
        }
    }

    void show()
    {
        // Takes 4 to 5ms
        FastLED.clear();
        parkour->show(player->position);
        player->show();
        FastLED.show();
    }
};