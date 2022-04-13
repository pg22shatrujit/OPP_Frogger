#pragma once
#include "Utils.h"
#include "ObstacleFactory.h"

class Obstacle
{
	friend class ObstacleFactory;
public:
	Obstacle() = delete;
private:
	Direction mDirection;
	int mNumTiles;
};

