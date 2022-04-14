#pragma once

#include "GameInterface.h"
#include "EngineTypes.h"
#include "Snake.h"
#include <time.h>
#include <string>

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
    float               GetRandomCoordinate(const float& bound) const; //Get a random coordinate between 0 and bound
   // void                UpdateFood(); //Update the food location when it gets consumed
    void                RestartGame(); //Restart the game at the player's input
    
    static Game*        sInstance;
    
    exEngineInterface*  mEngine;

    int                 mFontID;
    const char*         mWindowName;

    exVector2           mScorePosition; //Location where the score gets printed
    int                 mInput; //Tracks last user input
    int                 mScore; //Tracks the game score
    Snake*              mSnake; //Reference to the snake
    float               mJointSize; //Size of each joint of the snake (From the Snake's GetJointSize())
    exVector2           mFoodPosition; //Current location of food for the snake
    float               mTimeFromUpdate; //Time since last update, so that we can update at intervals we define
    bool                mIsFoodDisplayed; //Whether the food is being displayed
    bool                mIsGameOver; //Whether the game is over or not
    const float         kUpdateTime = 0.35f; //Time after which we update

    //Const text to display messages
    const std::string   kGameOverText = "Your final score is: ";
    const std::string   kRestartText = "Press R to restart.";

    bool move = false;

};

