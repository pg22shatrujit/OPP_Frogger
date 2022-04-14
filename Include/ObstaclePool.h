#pragma once
#include <vector>
#include "Obstacle.h"
#include "ObstacleFactory.h"
#define FACTORY ObstacleFactory::GetFactoryInstance()

class ObstaclePool
{
public:

	ObstaclePool() {

	}

	void PopulatePool(int PoolSize) {
		mPool.reserve(PoolSize);
		for (int i = 0; i < PoolSize; ++i)
		{
			mPool.push_back(FACTORY->GetObstacle());
		}
	}

private:
	std::vector<Obstacle*> mPool;
};

