#pragma once
#include <memory>
#include <iostream>
#include "Player.hpp"

class Game
{
public:
    std::unique_ptr<Player> p1;
    std::unique_ptr<Player> p2;

    Game()
    {
    }

    void init()
    {
        p1 = std::unique_ptr<Player>(new Player(0.0, 34, 35, {0, 255, 128}));
        p2 = std::unique_ptr<Player>(new Player(25.00, 26, 27, {240, 255, 128}));
    }
    void update()
    {
        FastLED.clear();
        p1->move(0.05);
        p2->move(0.01);

        // Serial.println("Moved");
        FastLED.show();
    }
};
