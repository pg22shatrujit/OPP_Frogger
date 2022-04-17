//Copyright (C) 2022 Shatrujit Aditya Kumar & Andre Dupuis, All Rights Reserved
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

	~Obstacle();

	void Update(); //Update position

	void Render(exEngineInterface* engine); //Render at current position

	bool IsOccupying(exVector2 loc); //Check if a vector is inside the  bounds

	bool IsOffScreen(); //Check is it's off screen

private:
	Obstacle(Direction direction, exVector2 location);

	const exColor colorArray[3] = {RED, GREEN, BLUE};

	Direction mDirection;
	exVector2 mLocation;
	exColor mColor;
	int mNumTiles;
};

