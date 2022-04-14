#include "Snake.h"
#include "Game.h"

#define SCREEN_CENTRE exVector2(400, 300)
#define STARTING_POSITION exVector2(400, 600 - Snake::kHalfSize)


Snake* Snake::sInstance = nullptr;
float Snake::kSnakeSpeed = 2 * Snake::kHalfSize;

//Private constructor for the singleton
Snake::Snake() : mHead(new SnakeJoint(STARTING_POSITION)), mCurrentDirection(Direction::RIGHT), mHasEaten(false), mIsDead(false)
{}

//Delete to clear the snake joint's and the singleton instance
void Snake::mDelete()
{
	//If the instance exists, delete all it's joints and the instance after that
	if (sInstance != nullptr) {

		while (sInstance->mHead != nullptr) {
			SnakeJoint* temp = sInstance->mHead;
			sInstance->mHead = sInstance->mHead->next;
			delete temp;
		}

		Snake* temp = sInstance;
		sInstance = nullptr;
		delete temp;
	}
}

//Iterate through the snake's joints and check if any of them contain the location
bool Snake::ContainsPosition(const exVector2& location) const
{
	SnakeJoint* temp = mHead;

	while (temp != mHead) {
		if (temp->GetPosition() == location) {
			return true;
		}
	}

	return false;
}

//Call mDelete on destruction
Snake::~Snake()
{
	Snake::mDelete();
}

//Update the snake's position
void Snake::Update()
{
	exVector2 newPosition;

	//Check direction and calculate new head position
	switch (mCurrentDirection)
	{
	case Direction::UP:
		newPosition = mHead->GetPosition() + exVector2(0, -1 * kSnakeSpeed);
		break;
	case Direction::DOWN:
		newPosition = mHead->GetPosition() + exVector2(0, kSnakeSpeed);
		break;
	case Direction::LEFT:
		newPosition = mHead->GetPosition() + exVector2(-1 * kSnakeSpeed, 0);
		break;
	case Direction::RIGHT:
		newPosition = mHead->GetPosition() + exVector2(kSnakeSpeed, 0);
		break;
	}

	//If the new position is outside the screen, move it to the other side
	if (newPosition.x < 0) newPosition.x += 800;
	else if (newPosition.x > 800) newPosition.x -= 800;

	if (newPosition.y < 0) newPosition.y += 600;
	else if (newPosition.y > 600) newPosition.y -= 600;

	//Check if it dies at the new position
	CheckForDeath(newPosition);

	//If it's not dead, iterate through the joints and make each joints positions is the previous one's
	if (!mIsDead) {
		SnakeJoint* currentJoint = mHead;
		while (currentJoint != nullptr) {
			exVector2 tempPosition = currentJoint->GetPosition();
			currentJoint->SetPosition(newPosition);
			newPosition = tempPosition;

			//If we're at the last joint and the snake has eaten, create a new joint
			if (currentJoint->next == nullptr && mHasEaten) {
				currentJoint->next = new SnakeJoint(currentJoint->GetPosition());
				mHasEaten = false;
			}

			currentJoint = currentJoint->next;
		}
	}
}

//Get a refernce to the snake instance
Snake* Snake::GetInstance()
{
	if (sInstance == nullptr) {
		sInstance = new Snake();
	}

	return sInstance;
}

//Getter for constant joint size
float Snake::GetJointSize()
{
	return kHalfSize;
}

//Set has eaten
void Snake::Eat()
{
	mHasEaten = true;
}

//Getter for mIsDead
bool Snake::GetIsDead() const
{
	return mIsDead;
}

void Snake::SetIsDead(bool isDead)
{
	mIsDead = isDead;
}

//Getter for mHead
SnakeJoint* Snake::GetHead() const
{
	return mHead;
}

//Getter for mCurrentDirection
Direction Snake::GetDirection() const
{
	return mCurrentDirection;
}

//Setter for mCurrentDirection
void Snake::SetDirection(Direction newDirection)
{
	mCurrentDirection = newDirection;
}

//Check if the snake collides with itself
void Snake::CheckForDeath(const exVector2& newHeadPos)
{
	SnakeJoint* currentJoint = mHead->next;
	while (currentJoint != nullptr) {
		if (currentJoint->GetPosition() == newHeadPos) {
			mIsDead = true;
			return;
		}
		currentJoint = currentJoint->next;
	}
}
