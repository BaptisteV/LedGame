#pragma once
#include <vector>
#include "Hsv.hpp"
#include "parkour/Obstacle.hpp"
#include "PlayerRenderer.hpp"

class Parkour
{
private:
    std::array<ObstacleStruct, NUM_LEDS> obstacles;
    std::array<ObstacleStruct, NUM_LEDS> nextObstacles;

    static const int spacing = 4;
    std::array<ObstacleStruct, NUM_LEDS> create()
    {
        std::array<ObstacleStruct, NUM_LEDS> result = {};

        int currentIndex = 0;
        // Start should not contain obstacles
        for (int iStart = 0; iStart < spacing * 2; iStart++)
        {
            result.at(iStart) = createObstacle(ObstacleType::None);
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
                result.at(currentIndex) = createObstacle(o.type);
                currentIndex++;
            }
            for (int s = 0; s < spacing; s++)
            {
                if (currentIndex >= NUM_LEDS)
                    break;
                result.at(currentIndex) = createObstacle(ObstacleType::None);
                currentIndex++;
            }
        }
        return result;
    }

public:
    Parkour()
    {
        obstacles = create();
        nextObstacles = create();
    }

    void startNextParkour()
    {
        obstacles = nextObstacles;
        nextObstacles = create();
    }

    void show(int playerPosition)
    {
        for (int i = 0; i < playerPosition - 1; i++)
        {
            HSV color = nextObstacles[i].color;
            leds[i] = CHSV(color.hue, color.saturation, color.value);
        }
        for (int j = playerPosition + 1; j < NUM_LEDS; j++)
        {
            HSV color = obstacles[j].color;
            leds[j] = CHSV(color.hue, color.saturation, color.value);
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