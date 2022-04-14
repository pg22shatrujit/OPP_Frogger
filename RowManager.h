#pragma once
#include "Utils.h"
#include "ObstaclePool.h"
#include "EngineTypes.h"
#define POOL_SIZE 10
#define ROW_HEIGHT 40
#define HALF_SIZE ROW_HEIGHT/2

class RowManager
{
public:
	RowManager(int rowNum, Direction direction) {
		mRowDir = direction;
		mRowNumber = rowNum;
		mSpawnLocation = exVector2((float)(mRowDir == Direction::RIGHT ? -HALF_SIZE : 800 + HALF_SIZE), (float)(ROW_HEIGHT * (mRowNumber + 1) + HALF_SIZE));
		mObstaclePool.SetPoolSize(POOL_SIZE);
	}

	void Update() {
		mObstaclePool.Update(mSpawnLocation, mRowDir);
		if (mObstaclePool.IsOccupied(mSpawnLocation)) {
			mObstaclePool.Spawn(mSpawnLocation, mRowDir);
		};
	}

	const void Render(exEngineInterface* engine) {
		mObstaclePool.Render(engine);
	}

	exVector2 GetSpawnLocation() {
		return mSpawnLocation;
	}

	bool IsColliding(exVector2 playerPosition) {
		return mObstaclePool.IsOccupied(playerPosition);
	}

private:
	int mRowNumber;
	Direction mRowDir;
	exVector2 mSpawnLocation;
	ObstaclePool mObstaclePool;
};

