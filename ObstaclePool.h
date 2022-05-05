//Copyright (C) 2022 Shatrujit Aditya Kumar & Andre Dupuis, All Rights Reserved
#pragma once
#include <vector>
#include "ObstacleFactory.h"
#define FACTORY ObstacleFactory::GetFactoryInstance()
#define SPAWN_CHANCE 25

class ObstaclePool
{
public:
    ObstaclePool();

    ~ObstaclePool();

    void SetPoolSize(int poolSize); //Reserves memory and cache size

    void Update(exVector2 spawnLoc, Direction row); //Update every obstacle in the pool

    void Render(exEngineInterface* engine); //Render every obstacle

    void Spawn(exVector2 spawnLoc, Direction row); //Spawn a new obstacle (Randomized chance)

    void UpdatePositions(); //Update obstacle positions

    void ResetPool(); //Empty the pool

    bool IsOccupied(exVector2 location); //Check if an obstacle occupies a location

private:

    std::vector<Obstacle*> mPool;
    int mPoolSize;
};

