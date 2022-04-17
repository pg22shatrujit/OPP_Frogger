//Copyright (C) 2022 Shatrujit Aditya Kumar & Andre Dupuis, All Rights Reserved
#pragma once
#include "Utils.h"
#include "ObstaclePool.h"
#define POOL_SIZE 5
#define ROW_HEIGHT 40

class RowManager
{
public:
	RowManager(int rowNum, Direction direction);
	~RowManager();

	void Update();

	const void Render(exEngineInterface* engine);

	exVector2 GetSpawnLocation();

	bool IsColliding(exVector2 playerPosition);

private:
	Direction mRowDir;
	exVector2 mSpawnLocation;
	ObstaclePool mObstaclePool;
};

