#pragma once
#include "Utils.h"
#include "GameInterface.h"
#include "EngineTypes.h"
#include "EngineInterface.h"
#include "ObstacleFactory.h"

#define HALF_SIZE 20
#define SCREEN_WIDTH 800

#define BLACK exColor(0, 0, 0)

class Obstacle
{
	friend class ObstacleFactory;
public:
	Obstacle() = delete;

	~Obstacle() {

	}

	void Update() {
		switch (mDirection)
		{
		case Direction::LEFT:
			mLocation = mLocation + exVector2(-2 * HALF_SIZE, 0);
			break;
		case Direction::RIGHT:
			mLocation = mLocation + exVector2(2 * HALF_SIZE, 0);
			break;
		}
	}

	void Render(exEngineInterface* engine) {
		exVector2 p1 = exVector2(mLocation.x - HALF_SIZE, mLocation.y - HALF_SIZE);
		exVector2 p2 = exVector2(mLocation.x + HALF_SIZE, mLocation.y + HALF_SIZE);
		engine->DrawBox(p1, p2, BLACK, 1);
	}

	bool IsOccupying(exVector2 loc) {
		return loc.x <= mLocation.x + HALF_SIZE && loc.x >= mLocation.x - HALF_SIZE;
	}

	bool IsOffScreen() {
		return mLocation.x >= SCREEN_WIDTH + HALF_SIZE || mLocation.x <= -HALF_SIZE;
	}

private:
	Obstacle(Direction direction, exVector2 location) {
		mDirection = direction;
		mLocation = location;
		mNumTiles = 1;
	}

	Direction mDirection;
	exVector2 mLocation;
	int mNumTiles;
};

