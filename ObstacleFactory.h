#pragma once
#include "Obstacle.h"
#include "Utils.h"

class ObstacleFactory
{
public:

    ~ObstacleFactory() {
        if (sInstance != nullptr)
            delete sInstance;
    }

    static ObstacleFactory* GetFactoryInstance()
    {
        if (sInstance == nullptr)// checking if we already have a Instance
        {
            sInstance = new ObstacleFactory();// create a new instance and store it in sInstance;
        }
        return sInstance;

    }

    Obstacle* GetObstacle(Direction dir, exVector2 spawnLoc)// factory function to generate new instance of Cryptography class and return it
    {
        return new Obstacle(dir, spawnLoc);
    }

private:


    ObstacleFactory();// constructor

    static ObstacleFactory* sInstance;
};