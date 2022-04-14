#pragma once
#include <vector>
#include <time.h>
#include "ObstacleFactory.h"
#define FACTORY ObstacleFactory::GetFactoryInstance()

class ObstaclePool
{
public:
    ObstaclePool() {
        srand(time(NULL));
        mPoolSize = 0;
    }

    void SetPoolSize(int poolSize) {
        mPoolSize = poolSize;
        mPool.resize(poolSize);
    }

    void Update(exVector2 spawnLoc, Direction row) {
        UpdatePositions();
        if (!IsOccupied(spawnLoc)) {
            Spawn(spawnLoc, row);
        }
    }

    void Render(exEngineInterface* engine) {
        for (int i = 0; i < mPoolSize; i++) {
            if (mPool[i] != nullptr) {
                mPool[i]->Render(engine);
            }
        }
    }

    void Spawn(exVector2 spawnLoc, Direction row) {
        if (rand() % 100 < 80) {
            for (int i = 0; i < mPoolSize; i++) {
                if (mPool[i] == nullptr)
                   mPool[i] = FACTORY->GetObstacle(row, spawnLoc);
            }
        }
    }

    void UpdatePositions() {
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

    Obstacle* GetObstacle(int index) const
    {
        return mPool[index];
    }

    bool IsOccupied(exVector2 SpawnLocation) {
        bool isOccupying = false;
        for (int i = 0; i < mPoolSize; i++) {
            if (mPool[i] != nullptr) {
                isOccupying |= mPool[i]->IsOccupying(SpawnLocation);
            }
        }

        return isOccupying;
    }

private:

    std::vector<Obstacle*> mPool;
    int mPoolSize;
};

