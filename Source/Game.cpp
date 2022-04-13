#include "Game.h"

#include "Constants.h"
#include "EngineInterface.h"
#include "SDL.h"

#include <iostream>

#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 8
#define RESTART 16

#define BLACK exColor(0, 0, 0)

#define RIGHT_BOUND 800
#define BOTTOM_BOUND 600

Game* Game::sInstance = nullptr;

Game* Game::GetInstance()
{
    if (sInstance == nullptr)
    {
        sInstance = new Game();
    }
    return sInstance;
}

Game::Game() 
    : mEngine(nullptr)
    , mFontID(-1)
    , mWindowName("Game")
    , mSnake(Snake::GetInstance())
    , mJointSize(Snake::GetJointSize())
    , mFoodPosition(exVector2())
    , mTimeFromUpdate(0.0f)
    , mIsFoodDisplayed(false)
    , mIsGameOver(false)
    , mScore(0)
{
    srand(time(NULL));
}

Game::~Game()
{
}

void Game::Initialize(exEngineInterface* engine)
{
    mEngine = engine;

    mFontID = mEngine->LoadFont("resources/Urusans.ttf", 32);

    mScorePosition.x = 0.0f;
    mScorePosition.y = 0.0f;
}

const char* Game::GetWindowName() const
{
    return mWindowName;
}

void Game::GetClearColor(exColor& color) const
{
    color.r = 255;
    color.g = 255;
    color.b = 255;
}

void Game::OnEvent(SDL_Event* event)
{}

void Game::OnEventsConsumed()
{
    // Grab inputs
    mInput = 0;
    int nKeys = 0;
    const Uint8* pState = SDL_GetKeyboardState(&nKeys);

    mInput |= pState[SDL_SCANCODE_UP];
    mInput |= pState[SDL_SCANCODE_DOWN] << 1;
    mInput |= pState[SDL_SCANCODE_LEFT] << 2;
    mInput |= pState[SDL_SCANCODE_RIGHT] << 3;
    mInput |= pState[SDL_SCANCODE_R] << 4; //Check for restart
}

void Game::Run(float deltaTime)
{
    mTimeFromUpdate += deltaTime;

    ProcessInput(deltaTime);

    if (!mIsGameOver) {
        //If the game isn't over, update and render the snake
        if (mTimeFromUpdate > kUpdateTime) {
            Update(deltaTime);
            mTimeFromUpdate = 0.0f;
        }
        Render(deltaTime);
    } else {
        //Otherwise, print game over text
        mEngine->DrawText(mFontID, mScorePosition, (kGameOverText + std::to_string(mScore)).c_str(), exColor(0, 0, 0), 10);
        mEngine->DrawText(mFontID, mScorePosition + exVector2(0, 100), kRestartText.c_str(), exColor(0, 0, 0), 10);
    }


}

//Update the food location when it gets consumed
void Game::UpdateFood()
{
    //If the food is not displayed, generate random locations until we get a valid one
    while (!mIsFoodDisplayed) {
        float x = GetRandomCoordinate(RIGHT_BOUND);
        float y = GetRandomCoordinate(BOTTOM_BOUND);
        exVector2 position = exVector2(x, y);

        //If the position isn't contained by the snake, it's valid
        if (!mSnake->ContainsPosition(position)) {
            mFoodPosition = position;

            mIsFoodDisplayed = true;
        }
    }
}

//Reset params for game restart
void Game::RestartGame()
{
    mIsGameOver = false;
    Snake::mDelete();
    mSnake = Snake::GetInstance();
    mScore = 0;
}


void Game::ProcessInput(const float& deltaTime)
{
    //Snake movement input is only valid if game isn't over
    if (!mIsGameOver) {
        // Change scene based on input
        if (mInput & UP)
        {
            mSnake->SetDirection((Direction)UP);
        }
        else if (mInput & DOWN)
        {
            mSnake->SetDirection((Direction)DOWN);
        }

        if (mInput & LEFT)
        {
            mSnake->SetDirection((Direction)LEFT);
        }
        else if (mInput & RIGHT)
        {
            mSnake->SetDirection((Direction)RIGHT);
        }
    }

    //If the game is over, check for restart input
    else if (mInput & RESTART) {
        RestartGame();
    }
}

void Game::Update(const float& deltaTime) {

    //Update snake's position and direction
    mSnake->Update();

    //Check if it died
    mIsGameOver = mSnake->GetIsDead();

    //If it's at the food location -> consume, grow larger and increase score
    if (mSnake->GetHead()->GetPosition() == mFoodPosition) {
        mIsFoodDisplayed = false;
        mSnake->Eat();
        mScore++;
    }

    //Update food position
    UpdateFood();
}

//Get a random coordinate between 0 and bound
float Game::GetRandomCoordinate(const float& bound) const
{   
    //Divide bound by 2*jointsize to snap to a grid based of joint size, then generate a number from 2*jointsize to bound
    return (rand() % (int)(bound / (mJointSize * 2) - 1) + 1) * mJointSize * 2;
}

void Game::Render(const float& deltaTime) const
{
    //Iterate over the snake's joints and draw them
    SnakeJoint* temp = mSnake->GetHead();
    while (temp != nullptr) {

        exVector2 currentPosition = temp->GetPosition();
        exVector2 p1 = exVector2(currentPosition.x - mJointSize, currentPosition.y - mJointSize);
        exVector2 p2 = exVector2(currentPosition.x + mJointSize, currentPosition.y + mJointSize);

        mEngine->DrawBox(p1, p2, BLACK, 1);
        temp = temp->next;
    }

    mEngine->DrawCircle(mFoodPosition, mJointSize, BLACK, 1);

    mEngine->DrawText(mFontID, mScorePosition, std::to_string(mScore).c_str(), exColor(0, 0, 0), 10);
}