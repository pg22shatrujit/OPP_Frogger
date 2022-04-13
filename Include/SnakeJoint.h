#pragma once
#include "EngineTypes.h"

class SnakeJoint
{
public:
	SnakeJoint() = delete;
	~SnakeJoint();
	SnakeJoint(exVector2 position); //Constructor with current position
	SnakeJoint* next; //Reference to the next joint

	exVector2 GetPosition() const; //Getter for current position
	void SetPosition(exVector2 position); //Setter for current position

private:
	exVector2 position; //Stores current position
};

