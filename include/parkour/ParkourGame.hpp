#pragma once
#include <memory>
#include "constants/Hardware.hpp"
#include "Player.hpp"
#include "Parkour.hpp"

class ParkourGame
{
private:
    std::unique_ptr<Player> player;
    std::unique_ptr<Parkour> parkour;
    bool autoplay;

public:
    ParkourGame(bool autoplay)
    {
        player = std::unique_ptr<Player>(new Player(BTN_LEFT_PIN, BTN_RIGHT_PIN));
        parkour = std::unique_ptr<Parkour>(new Parkour());
        this->autoplay = autoplay;
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
            Serial.println("Crashed");
            player.reset(new Player(BTN_LEFT_PIN, BTN_RIGHT_PIN));
        }

        bool loopsBack = (position == 0) && (previousPosition == NUM_LEDS - 1);
        if (loopsBack)
        {
            player->speedup();
            Serial.printf("Looped, speed is %f\n", player->speed);
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