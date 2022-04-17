//Copyright (C) 2022 Shatrujit Aditya Kumar & Andre Dupuis, All Rights Reserved
#include "..\Include\Obstacle.h"

Obstacle::~Obstacle() {}

//Check current direction and move by it's size in that direction
void Obstacle::Update()
{
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

//Draw the obstacle at the current position
void Obstacle::Render(exEngineInterface* engine)
{
	exVector2 center = exVector2(mLocation.x, mLocation.y);
	engine->DrawCircle(center, HALF_SIZE, mColor, 1);
}

//Check if a vector is inside it's bounds
bool Obstacle::IsOccupying(exVector2 loc)
{
	return loc.x <= mLocation.x + HALF_SIZE && loc.x >= mLocation.x - HALF_SIZE;
}

//Check if it's left the screen
bool Obstacle::IsOffScreen()
{
	return mLocation.x >= SCREEN_WIDTH + HALF_SIZE || mLocation.x <= -HALF_SIZE;
}

//Init with random color
Obstacle::Obstacle(Direction direction, exVector2 location)
{
	srand(time(NULL));
	mDirection = direction;
	mLocation = location;
	mNumTiles = 1;
	mColor = colorArray[rand() % 3];
}
