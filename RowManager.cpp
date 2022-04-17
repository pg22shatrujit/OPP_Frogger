//Copyright (C) 2022 Shatrujit Aditya Kumar & Andre Dupuis, All Rights Reserved
#include "RowManager.h"

//Init direction and row number
RowManager::RowManager(int rowNum, Direction direction) {
	mRowDir = direction;
	mSpawnLocation = exVector2((float)(mRowDir == Direction::RIGHT ? -HALF_SIZE : 800 + HALF_SIZE), (float)(ROW_HEIGHT * (rowNum + 1) + HALF_SIZE));
	mObstaclePool.SetPoolSize(POOL_SIZE);
}

RowManager::~RowManager() {}

//Updates pool
void RowManager::Update() {
	mObstaclePool.Update(mSpawnLocation, mRowDir);
}

//Renders pool
const void RowManager::Render(exEngineInterface* engine) {
	mObstaclePool.Render(engine);
}

//Getter for spawn location
exVector2 RowManager::GetSpawnLocation() {
	return mSpawnLocation;
}

//Checks if player position is occupied
bool RowManager::IsColliding(exVector2 playerPosition) {
	return mObstaclePool.IsOccupied(playerPosition);
}