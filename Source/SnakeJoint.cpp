#include "SnakeJoint.h"

//Empty destructor since we're not using heap memory
SnakeJoint::~SnakeJoint()
{
}

//Initialize joint with position and next = nullptr
SnakeJoint::SnakeJoint(exVector2 position): position(position),  next(nullptr)
{}

//Getter for position
exVector2 SnakeJoint::GetPosition() const
{
	return position;
}

//Setter for position
void SnakeJoint::SetPosition(exVector2 newPosition)
{
	position = newPosition;
}
