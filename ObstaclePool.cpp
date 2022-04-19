//Copyright (C) 2022 Shatrujit Aditya Kumar & Andre Dupuis, All Rights Reserved
#include "ObstaclePool.h"

ObstaclePool::ObstaclePool()
{
    srand(time(NULL));
    mPoolSize = 0;
}

//Deletes any stray pointers on destruction
ObstaclePool::~ObstaclePool()
{
    for (int i = 0; i < mPoolSize; i++) {
        if (mPool[i] != nullptr) {
            delete mPool[i];
            mPool[i] = nullptr;
        }
    }
}

//Caches size and resizes vector
void ObstaclePool::SetPoolSize(int poolSize)
{
    mPoolSize = poolSize;
    mPool.resize(poolSize);
}

//Updates object positions and spawns
void ObstaclePool::Update(exVector2 spawnLoc, Direction row)
{
    UpdatePositions();
    if (!IsOccupied(spawnLoc)) {
        Spawn(spawnLoc, row);
    }
}

//Renders all non-null obstacles
void ObstaclePool::Render(exEngineInterface* engine)
{
    for (int i = 0; i < mPoolSize; i++) {
        if (mPool[i] != nullptr) {
            mPool[i]->Render(engine);
        }
    }
}

//Spawns an obstacle with % chance if spawn location is unoccupied
void ObstaclePool::Spawn(exVector2 spawnLoc, Direction row)
{
    int i = rand() % 100;
    if (i > 100 - SPAWN_CHANCE) {
        for (int i = 0; i < mPoolSize; i++) {
            if (mPool[i] == nullptr) {
                mPool[i] = FACTORY->GetObstacle(row, spawnLoc);
                break;
            }
        }
    }
}

//Updated obstacle positons
void ObstaclePool::UpdatePositions()
{
    for (int i = 0; i < mPoolSize; i++) {
        if (mPool[i] != nullptr) {
            mPool[i]->Update();

            if (mPool[i]->IsOffScreen()) {
                delete mPool[i];
                mPool[i] = nullptr;
            }
        }
    }
}

//Check if a position is occupied
bool ObstaclePool::IsOccupied(exVector2 location)
{
    bool isOccupying = false;
    for (int i = 0; i < mPoolSize; i++) {
        if (mPool[i] != nullptr) {
            isOccupying = isOccupying || mPool[i]->IsOccupying(location);
        }
    }

    return isOccupying;
}
