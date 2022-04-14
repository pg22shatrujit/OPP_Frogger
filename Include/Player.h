#pragma once
#include "Utils.h"
#include "GameInterface.h"
#include "EngineTypes.h"
#include "EngineInterface.h"

class Player
{
public:
	~Player();
	void Update(); //Update the position of the snake
	static Player* GetInstance(); //Getter for the instance of the singleton
	static float GetHalfSize(); //Getter for static joint size
	bool GetIsDead() const; //Getter for mIsDead
	void SetIsDead(bool isDead); //Getter for mIsDead

	const void Render(exEngineInterface* engine); //Render the player

	Direction GetDirection() const; //Getter for the snake's current direction
	void SetDirection(Direction newDirection); //Setter the snake's current direction

	exVector2 GetPosition() const; //Getter for mPosition

	static void mDelete(); //Delete to clear the snake joint's and the singleton instance
	

private:
	Player(); //Private constructor for the singleton
	static Player* sInstance; //Static reference to the singleton instance
	static const int kHalfSize = 20; //Static snake size
	static float kSnakeSpeed; //Constant snake speed
	bool mIsDead; //If the snake is dead
	Direction mCurrentDirection; //Current snake direction
	exVector2 mPosition; //Stores current position
};

