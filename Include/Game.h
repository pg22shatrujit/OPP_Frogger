#pragma once

#include "GameInterface.h"
#include "EngineTypes.h"
#include "Player.h"
#include "../RowManager.h"
#include <time.h>
#include <string>

#define SCREEN_HEIGHT 600
#define ROW_HEIGHT 40
#define NUM_ROWS (int)(SCREEN_HEIGHT/ROW_HEIGHT - 2)

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
    void                Render(const float& deltaTime) const;
    void                Update(const float& deltaTime);
    void                RestartGame(); //Restart the game at the player's input
    
    static Game*        sInstance;
    
    exEngineInterface*  mEngine;

    int                 mFontID;
    const char*         mWindowName;

    exVector2           mScorePosition; //Location where the score gets printed
    int                 mInput; //Tracks last user input
    int                 mScore; //Tracks the game score
    Player*             mPlayer; //Reference to the player
    float               mJointSize; //Size of each joint of the snake (From the Snake's GetJointSize())
    float               mTimeFromUpdate; //Time since last update, so that we can update at intervals we define
    bool                mIsGameOver; //Whether the game is over or not
    bool                move; //Whether the player should move in the next update cycle

    RowManager*         mRows[NUM_ROWS]; //Manager for each row of the game
    static const int    kNumRows = NUM_ROWS; //Precalculate number of rows for easier updates
    const float         kUpdateTime = 0.35f; //Time after which the frames should update

    //Const text to display messages
    const std::string   kGameOverText = "Your final score is: ";
    const std::string   kRestartText = "Press R to restart.";

};