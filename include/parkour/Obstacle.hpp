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

ObstacleStruct createObstacle(ObstacleType type)
{
    return obstaclePrototypes[static_cast<size_t>(type)];
}

ObstacleStruct createRandom()
{
    int randomValue = random(0, 4);
    return createObstacle((ObstacleType)randomValue);
}

/*
class Obstacle
{
private:
    void setFromType(ObstacleType type)
    {
        this->type = type;
        this->color = getObstacleColor(type);
        this->width = sizes.at(type);
    }

    ObstacleType randomObstacleType()
    {
        int randomValue = random(0, 4);

        switch (randomValue)
        {
        case 0:
            return ObstacleType::None;
        case 1:
            return ObstacleType::RightClick;
        case 2:
            return ObstacleType::LeftClick;
        case 3:
            return ObstacleType::DoubleClick;
        }
    }

public:
    Obstacle()
    {
        ObstacleType randType = randomObstacleType();
        setFromType(randType);
    }
    Obstacle(ObstacleType type)
    {
        setFromType(type);
    }

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
};*/