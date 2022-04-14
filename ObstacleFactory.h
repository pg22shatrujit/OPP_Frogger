#pragma once
#include "Obstacle.h"
#include "Utils.h"

class ObstacleFactory
{
public:

    //Delete instance if it exists
    ~ObstacleFactory();

    //Get the factory instance (create if it doesn't exist)
    static ObstacleFactory* GetFactoryInstance();

    //Generate a new obstacle with direction and location
    Obstacle* GetObstacle(Direction dir, exVector2 spawnLoc);

private:

    ObstacleFactory();

    static ObstacleFactory* sInstance;
};