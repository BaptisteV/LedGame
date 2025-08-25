#pragma once
#include <vector>
#include "Hsv.hpp"
#include "parkour/Obstacle.hpp"
#include "PlayerBrickRenderer.hpp"

class Parkour
{
private:
    std::array<ObstacleStruct, NUM_LEDS> obstacles;
    std::array<ObstacleStruct, NUM_LEDS> nextObstacles;

    void render(int position, HSV color)
    {
        int ledIndex = position % NUM_LEDS;
        leds[ledIndex] = CHSV(color.hue, color.saturation, color.value);
    };

    static const int spacing = 4;
    static void generate(std::array<ObstacleStruct, NUM_LEDS> &tofill)
    {
        int currentIndex = 0;
        // Start should not contain obstacles
        for (int iStart = 0; iStart < spacing * 2; iStart++)
        {
            tofill.at(iStart) = createObstacle(ObstacleType::None);
            currentIndex++;
        }

        while (currentIndex < NUM_LEDS)
        {
            // Create random obstacle (includes None)
            ObstacleStruct o = createRandom();
            // Duplicate width times
            for (int i = 0; i < o.width; i++)
            {
                if (currentIndex >= NUM_LEDS)
                    break;
                tofill.at(currentIndex) = createObstacle(o.type);
                currentIndex++;
            }
            for (int s = 0; s < spacing; s++)
            {
                if (currentIndex >= NUM_LEDS)
                    break;
                tofill.at(currentIndex) = createObstacle(ObstacleType::None);
                currentIndex++;
            }
        }
    }

public:
    Parkour()
    {
        obstacles = {};
        nextObstacles = {};

        regenerate();
    }

    void regenerate()
    {
        generate(obstacles);
        generate(nextObstacles);
    }

    void startNextParkour()
    {
        obstacles = nextObstacles;
        generate(nextObstacles);
    }

    void show(int playerPosition)
    {
        for (int i = 0; i < playerPosition - 1; i++)
        {
            render(i, nextObstacles[i].color);
        }
        for (int j = playerPosition + 1; j < obstacles.size(); j++)
        {
            render(j, obstacles[j].color);
        }
    }

    bool crashesObstacle(const std::unique_ptr<Player> &player)
    {
        int position = player->headIndex();
        return !obstacles.at(position).canGoThrough(player);
    }

    Direction nextCompatibleDirection(int headIndex)
    {
        auto nextType = obstacles.at(headIndex).type;
        switch (nextType)
        {
        case ObstacleType::DoubleClick:
            return Direction::DoubleLeft;
        case ObstacleType::LeftClick:
            return Direction::Left;
        case ObstacleType::RightClick:
            return Direction::Right;
        default:
            return Direction::Right;
        }
    }
};