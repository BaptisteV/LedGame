#pragma once
#include <Arduino.h>
#include <map>
#include <exception>
#include "Direction.hpp"
#include "Player.hpp"
#include "ObstacleType.hpp"
#include "config/Colors.hpp"

struct ObstacleStruct
{
    ObstacleType type;
    HSV color;
    int width;

    bool canGoThrough(const std::unique_ptr<Player> &player)
    {
        switch (type)
        {
        case ObstacleType::None:
            return true;
        case ObstacleType::RightClick:
            return player->direction == Direction::Right;
        case ObstacleType::LeftClick:
            return player->direction == Direction::Left;
        case ObstacleType::DoubleClick:
            return player->direction == Direction::DoubleRight ||
                   player->direction == Direction::DoubleLeft;
        default:
            throw std::runtime_error("Unexpected ObstacleType");
        }
    }
};

static const std::array<ObstacleStruct, 4> obstaclePrototypes = {
    ObstacleStruct{ObstacleType::None, none, 1},
    ObstacleStruct{ObstacleType::RightClick, obstacleRed, 3},
    ObstacleStruct{ObstacleType::LeftClick, obstacleBlue, 3},
    ObstacleStruct{ObstacleType::DoubleClick, obstaclePink, 4},
};

constexpr ObstacleStruct createObstacle(const ObstacleType &type)
{
    return obstaclePrototypes[static_cast<size_t>(type)];
}

ObstacleStruct createRandom()
{
    int randomValue = random(0, 4);
    return createObstacle((ObstacleType)randomValue);
}