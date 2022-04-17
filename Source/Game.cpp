//Copyright (C) 2022 Shatrujit Aditya Kumar & Andre Dupuis, All Rights Reserved
#include "Game.h"

#include "Constants.h"
#include "EngineTypes.h"
#include "EngineInterface.h"
#include "SDL.h"

#include <iostream>

#define UP 1
#define DOWN 2
#define LEFT 4
#define RIGHT 8
#define RESTART 16

#define RIGHT_BOUND 800
#define BOTTOM_BOUND 600

Game* Game::sInstance = nullptr;
exVector2 Game::mScorePosition = exVector2(0, 0);
exVector2 Game::mHighScorePosition = exVector2(400, 0);
exVector2 Game::kLineHeight = exVector2(0, 50);
exVector2 Game::kColumnWidth = exVector2(200, 0);

//Get Singleton instance
Game* Game::GetInstance()
{
    if (sInstance == nullptr)
    {
        sInstance = new Game();
    }
    return sInstance;
}

//Initalize member variables and row managers
Game::Game() 
    : mEngine(nullptr)
    , mFontID(-1)
    , mWindowName("Game")
    , mPlayer(Player::GetInstance())
    , mJointSize(Player::GetHalfSize())
    , mTimeFromUpdate(0.0f)
    , mIsGameOver(false)
    , mScore(0)
    , move(false)
    , mHighScoreManager(HighScores::GetInstance())
    , mAddedHighScore(false)
    , mShouldAddHighScore(false)
    , mInput(0)
{

    for (int i = 0; i < kNumRows; i++) {
        mRows[i] = new RowManager(i, i % 2 == 0 ? (Direction)LEFT : (Direction)RIGHT);
    }
}

Game::~Game() {}

void Game::Initialize(exEngineInterface* engine)
{
    mEngine = engine;

    mFontID = mEngine->LoadFont("resources/Urusans.ttf", 32);
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

    Update(deltaTime);

    Render(deltaTime);

}

//Reset params for game restart
void Game::RestartGame()
{
    mIsGameOver = false;
    mInput = 0;
    Player::mDelete();
    mPlayer = Player::GetInstance();
    mScore = 0;
    move = false;
    GoingDown = false;
    mShouldAddHighScore = false;
    mAddedHighScore = false;
}

void Game::RenderScores()
{
    //Check if we should and have added the high score
    if (!mShouldAddHighScore && !mAddedHighScore) {
        mShouldAddHighScore = mHighScoreManager->ShouldAddScore(mScore);
    }

    //If we should but we haven't, get the player's name and truncate to three characters
    if (mShouldAddHighScore && !mAddedHighScore) {
        std::string name;
        std::cout << kEnterNameText;
        std::cin >> name;
        name = name.substr(0, 3);
        mHighScoreManager->Add(name, mScore);
        mAddedHighScore = true;
    }

    //Draw the text for high scores
    mEngine->DrawText(mFontID, mHighScorePosition, mHighScoreManager->kTitleText.c_str(), exColor(0, 0, 0), 10);
    mEngine->DrawText(mFontID, mHighScorePosition + kLineHeight, mHighScoreManager->kNameText.c_str(), exColor(0, 0, 0), 10);
    mEngine->DrawText(mFontID, mHighScorePosition + kLineHeight + kColumnWidth, mHighScoreManager->kPointText.c_str(), exColor(0, 0, 0), 10);

    //Iterate through the linked list and print every score
    HighScoreNode* currentScore = mHighScoreManager->GetHead();
    int i = 2; //Offset so lines don't overlap
    while (currentScore != nullptr) {
        mEngine->DrawText(mFontID, mHighScorePosition + kLineHeight * i, currentScore->GetName().c_str(), exColor(0, 0, 0), 10);
        mEngine->DrawText(mFontID, mHighScorePosition + kLineHeight * i + kColumnWidth, std::to_string(currentScore->GetScore()).c_str(), exColor(0, 0, 0), 10);
        i++;
        currentScore = currentScore->GetNext();
    }
}


void Game::ProcessInput(const float& deltaTime)
{
    //Movement input is only valid if game isn't over
    if (!mIsGameOver) {
        // If we've got input and it's not to restart, set move to true
        if (mInput && !(mInput & RESTART)) {
            move = true;
        }
        if (mInput & UP)
        {
            mPlayer->SetDirection((Direction)UP);
            
        }
        else if (mInput & DOWN)
        {
            mPlayer->SetDirection((Direction)DOWN);
        }

        if (mInput & LEFT)
        {
            mPlayer->SetDirection((Direction)LEFT);
        }
        else if (mInput & RIGHT)
        {
            mPlayer->SetDirection((Direction)RIGHT);
        }
    }

    //If the game is over, check for restart input
    else if (mInput & RESTART) {
        RestartGame();
    }
}

void Game::Update(const float& deltaTime) {

    //Check for death before updating locations so we don't lose a frame
    for (int i = 0; i < kNumRows; i++) {
        if (mRows[i]->GetSpawnLocation().y == mPlayer->GetPosition().y) {
            if (mRows[i]->IsColliding(mPlayer->GetPosition())) {
                mPlayer->SetIsDead(true);
            }
        }
    }

    if (mIsGameOver || mTimeFromUpdate < kUpdateTime) return;

    mTimeFromUpdate = 0.0f;

    if (move) {
        //Update player position and direction
        mPlayer->Update();
        move = false;
    }

    //Update positions
    for (int i = 0; i < kNumRows; i++) {
        mRows[i]->Update();
    }

    //Check if player has reached the top of the screen and increase score, score will only increase at the top once the player goes to the bottom and comes back up
    if (mPlayer->GetPosition().y == Player::GetHalfSize() && GoingDown == false) {
        mScore += 1;
        GoingDown = true;
    }

    //check if player has reached the bottom of the screen and increase score only if they have made it to the top first
    if (mPlayer->GetPosition().y == 600 - Player::GetHalfSize() && GoingDown == true) {
        mScore += 1;
        GoingDown = false;
    }

    //Check if it died
    mIsGameOver = mPlayer->GetIsDead();
}

void Game::Render(const float& deltaTime)
{
    //If game over, print restart message and high scores
    if (mIsGameOver) {

        mEngine->DrawText(mFontID, mScorePosition, (kGameOverText + std::to_string(mScore)).c_str(), exColor(0, 0, 0), 10);
        mEngine->DrawText(mFontID, mScorePosition + kLineHeight, kRestartText.c_str(), exColor(0, 0, 0), 10);

        RenderScores();
    }
    //Otherwise, render the game
    else {
        //Render each row
        for (int i = 0; i < kNumRows; i++) {
            mRows[i]->Render(mEngine);
        }

        //Render the player
        mPlayer->Render(mEngine);

        mEngine->DrawText(mFontID, mScorePosition, std::to_string(mScore).c_str(), exColor(0, 0, 0), 10);
    }
}