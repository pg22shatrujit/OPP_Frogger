#pragma once
#include "SnakeJoint.h"
#include "Utils.h"

class Snake
{
public:
	~Snake();
	void Update(); //Update the position of the snake
	static Snake* GetInstance(); //Getter for the instance of the singleton
	static float GetJointSize(); //Getter for static joint size
	void Eat(); //Increase the snake's size when it eats
	bool GetIsDead() const; //Getter for mIsDead
	SnakeJoint* GetHead() const; //Get ref to the snake's head

	Direction GetDirection() const; //Getter for the snake's current direction
	void SetDirection(Direction newDirection); //Setter the snake's current direction
	void CheckForDeath(const exVector2& newHeadPos);  //Checks for death condition

	static void mDelete(); //Delete to clear the snake joint's and the singleton instance
	bool ContainsPosition(const exVector2& location) const; //Check if a position is contained by the snake

private:
	Snake(); //Private constructor for the singleton
	static Snake* sInstance; //Static reference to the singleton instance
	static const int kHalfSize = 50; //Static snake size
	static float kSnakeSpeed;//Constant snake speed
	bool mHasEaten; //If the snake has eaten and needs to grow
	bool mIsDead; //If the snake is dead
	SnakeJoint* mHead; //Reference to the snake's head
	Direction mCurrentDirection; //Current snake direction
};
