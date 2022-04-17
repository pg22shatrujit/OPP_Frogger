//Copyright (C) 2022 Shatrujit Aditya Kumar & Andre Dupuis, All Rights Reserved
#include "ObstacleFactory.h"

ObstacleFactory* ObstacleFactory::sInstance = nullptr;

//Delete instance if it exists
ObstacleFactory::~ObstacleFactory()
{
    if (sInstance != nullptr)
        delete sInstance;
}

//Get the factory instance (create if it doesn't exist)
ObstacleFactory* ObstacleFactory::GetFactoryInstance()
{
    if (sInstance == nullptr)// checking if we already have a Instance
    {
        sInstance = new ObstacleFactory();// create a new instance and store it in sInstance;
    }
    return sInstance;
}

//Generate a new obstacle with direction and location
Obstacle* ObstacleFactory::GetObstacle(Direction dir, exVector2 spawnLoc)
{
    return new Obstacle(dir, spawnLoc);
}

ObstacleFactory::ObstacleFactory() {}