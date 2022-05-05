//Copyright (C) 2022 Shatrujit Aditya Kumar & Andre Dupuis, All Rights Reserved
#pragma once

#include "GameInterface.h"
#include "EngineTypes.h"
#include "Player.h"
#include "../RowManager.h"
#include "../HighScores.h"
#include <time.h>
#include <string>

#define SCREEN_HEIGHT 600
#define ROW_HEIGHT 40
#define NUM_ROWS (int)(SCREEN_HEIGHT/ROW_HEIGHT - 2)
#define MAX_NAME_LENGTH 3

class Game : public exGameInterface
{
public:
    static Game*        GetInstance();
        
    virtual             ~Game();

    virtual void        Initialize(exEngineInterface* engine);
    virtual const char* GetWindowName() const;
    virtual void        GetClearColor(exColor& color) const;

    virtual void        OnEvent(SDL_Event* event);
    virtual void        OnEventsConsumed();

    virtual void        Run(float deltaTime);

    bool GoingDown = false;

private:
    Game();
    
    void                ProcessInput(const float& deltaTime);
    void                Render(const float& deltaTime);
    void                Update(const float& deltaTime);
    void                RestartGame(); //Restart the game at the player's input
    void                RenderScores(const float& deltaTime);
    void                ResetRowManagers(); //Delete row managers
    
    static Game*        sInstance;
    
    exEngineInterface*  mEngine;

    int                 mFontID;
    const char*         mWindowName;

    static exVector2    mScorePosition; //Location where the score gets printed
    static exVector2    mHighScorePosition; //Location where the score gets printed
    static exVector2    kLineHeight; //Line offset when drawing text
    static exVector2    kColumnWidth; //Column offset when drawing high scores
    int                 mInput; //Tracks last user input
    int                 mScore; //Tracks the game score
    Player*             mPlayer; //Reference to the player
    float               mJointSize; //Size of each joint of the snake (From the Snake's GetJointSize())
    float               mTimeFromUpdate; //Time since last update, so that we can update at intervals we define
    bool                mIsGameOver; //Whether the game is over or not
    bool                mShouldAddHighScore; //Whether the player should be added to the high scores
    bool                mAddedHighScore; //Whether the player has been added to the high scores
    bool                move; //Whether the player should move in the next update cycle

    RowManager*         mRows[NUM_ROWS]; //Manager for each row of the game
    static const int    kNumRows = NUM_ROWS; //Precalculate number of rows for easier updates
    const float         kUpdateTime = 0.35f; //Time after which the frames should update

    HighScores*         mHighScoreManager; //Maintain a linked list of high scores
    char*               mNextCharacter; //Cache the last single character entered by the user
    std::string         mHighScoreName; //Cache a three character name to set in the highscore list

    //Const text to display messages
    const std::string   kGameOverText = "Your final score is: ";
    const std::string   kRestartText = "Press Esc to restart.";
    const std::string   kEnterNameText = "Enter your name: ";

};