#include "Player.h"
#include "Game.h"

#define SCREEN_CENTRE exVector2(400, 300)
#define SCREEN_SPAWN exVector2(400, 580)

#define BLACK exColor(0, 0, 0)


Player* Player::sInstance = nullptr;
float Player::kSnakeSpeed = 2 * Player::kHalfSize;

//Private constructor for the singleton
Player::Player() : mPosition(SCREEN_SPAWN), mCurrentDirection(Direction::RIGHT),  mIsDead(false)
{}

//Delete to clear the snake joint's and the singleton instance
void Player::mDelete()
{
	//If the instance exists, delete all it's joints and the instance after that
	if (sInstance != nullptr) {

		Player* temp = sInstance;
		sInstance = nullptr;
		delete temp;
	}
}

//Call mDelete on destruction
Player::~Player()
{
	Player::mDelete();
}

//Update the snake's position
void Player::Update()
{
	exVector2 newPosition;
	
	//Check direction and calculate new head position
	switch (mCurrentDirection)
	{
	case Direction::UP:
		mPosition = mPosition + exVector2(0, -1 * kSnakeSpeed);
		break;
	case Direction::DOWN:
		mPosition = mPosition + exVector2(0, kSnakeSpeed);
		break;
	case Direction::LEFT:
		mPosition = mPosition + exVector2(-1 * kSnakeSpeed, 0);
		break;
	case Direction::RIGHT:
		mPosition = mPosition + exVector2(kSnakeSpeed, 0);
		break;
	}

	//If the new position is outside the screen, move it to the other side
	if (mPosition.x < 0) mPosition.x += kSnakeSpeed;
	else if (mPosition.x > 800) mPosition.x -= kSnakeSpeed;

	if (mPosition.y < 0) mPosition.y += kSnakeSpeed;
	else if (mPosition.y > 600) mPosition.y -= kSnakeSpeed;
}

//Get a refernce to the snake instance
Player* Player::GetInstance()
{
	if (sInstance == nullptr) {
		sInstance = new Player();
	}

	return sInstance;
}

//Getter for constant joint size
float Player::GetHalfSize()
{
	return kHalfSize;
}


//Getter for mIsDead
bool Player::GetIsDead() const
{
	return mIsDead;
}

void Player::SetIsDead(bool isDead)
{
	mIsDead = isDead;
}

const void Player::Render(exEngineInterface* engine)
{
	exVector2 p1 = exVector2(mPosition.x - kHalfSize, mPosition.y - kHalfSize);
	exVector2 p2 = exVector2(mPosition.x + kHalfSize, mPosition.y + kHalfSize);
	engine->DrawBox(p1, p2, BLACK, 1);
}

//Getter for mCurrentDirection
Direction Player::GetDirection() const
{
	return mCurrentDirection;
}

//Setter for mCurrentDirection
void Player::SetDirection(Direction newDirection)
{
	mCurrentDirection = newDirection;
}

exVector2 Player::GetPosition() const
{
	return mPosition;
}