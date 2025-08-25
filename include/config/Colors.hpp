#pragma once
#include <vector>
#include <exception>
#include "Hsv.hpp"
#include "Direction.hpp"
#include "parkour/ObstacleType.hpp"
#define SATURATION 255
#define BRIGHTNESS 150

#define OBSTACLE_BRIGHTNESS BRIGHTNESS / 2
#define OBSTACLE_SATURATION 200

HSV blue = HSV{240, SATURATION, BRIGHTNESS};
HSV pink = HSV{170, SATURATION, BRIGHTNESS};
HSV red = HSV{0, SATURATION, BRIGHTNESS};

HSV obstacleBlue = HSV{240, OBSTACLE_SATURATION, OBSTACLE_BRIGHTNESS};
HSV obstaclePink = HSV{170, OBSTACLE_SATURATION, OBSTACLE_BRIGHTNESS};
HSV obstacleRed = HSV{0, OBSTACLE_SATURATION, OBSTACLE_BRIGHTNESS};

HSV none = HSV{0, OBSTACLE_SATURATION, 0};

std::vector<HSV> getPlayerColors(Direction dir)
{
    switch (dir)
    {
    case Direction::Left:
        return {blue, obstacleBlue};
    case Direction::DoubleLeft:
        return {blue, pink};
    case Direction::Right:
        return {red, obstacleRed};
    case Direction::DoubleRight:
        return {red, pink};
    default:
        throw std::runtime_error("Unexpected Direction");
    }
}
/*
HSV getObstacleColor(ObstacleType type)
{
    HSV left = setSatBri(getPlayerColors(Direction::Left).at(0));
    HSV right = setSatBri(getPlayerColors(Direction::Right).at(0));
    HSV doubleIndicator = setSatBri(getPlayerColors(Direction::DoubleRight).at(1));

    switch (type)
    {
    case ObstacleType::None:
        return none;
    case ObstacleType::RightClick:
        return right;
    case ObstacleType::LeftClick:
        return left;
    case ObstacleType::DoubleClick:
        return doubleIndicator;
    default:
        throw std::runtime_error("Unknown ObstacleType");
    }
}
*/