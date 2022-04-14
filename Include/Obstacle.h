#pragma once
#include "Utils.h"
#include "GameInterface.h"
#include "EngineTypes.h"
#include "EngineInterface.h"
#include "ObstacleFactory.h"

#include <stdlib.h>
#include <time.h>
#define HALF_SIZE 20
#define SCREEN_WIDTH 800

#define RED exColor(255, 0, 0)
#define BLUE exColor(0, 0, 255)
#define GREEN exColor(0, 255, 0)

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
		exVector2 center = exVector2(mLocation.x, mLocation.y);
		engine->DrawCircle(center, HALF_SIZE, mColor, 1);
	}

	bool IsOccupying(exVector2 loc) {
		return loc.x <= mLocation.x + HALF_SIZE && loc.x >= mLocation.x - HALF_SIZE;
	}

	bool IsOffScreen() {
		return mLocation.x >= SCREEN_WIDTH + HALF_SIZE || mLocation.x <= -HALF_SIZE;
	}

private:
	Obstacle(Direction direction, exVector2 location) {
		srand(time(NULL));
		mDirection = direction;
		mLocation = location;
		mNumTiles = 1;
		mColor = colorArray[rand() % 3];
	}

	const exColor colorArray[3] = {RED, GREEN, BLUE};

	Direction mDirection;
	exVector2 mLocation;
	exColor mColor;
	int mNumTiles;
};

