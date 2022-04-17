//Copyright (C) 2022 Shatrujit Aditya Kumar & Andre Dupuis, All Rights Reserved
#pragma once
#include "HighScoreNode.h"
#define TITLE_TEXT "HI SCORES" //Text to print to screen
#define NAME_TEXT "NAME"
#define POINT_TEXT "POINTS"
#define MAX_SIZE 10 //Max list size

class HighScores
{
public:
	~HighScores();

	static HighScores* GetInstance(); //Get singleton instance
	HighScoreNode* GetHead(); //Get the head of the linked list

	void Add(std::string name, int score);  //Add a new node to the list
	bool ShouldAddScore(int score); //Check if the score should be added
	const std::string kTitleText = TITLE_TEXT; //References to text to print
	const std::string kNameText = NAME_TEXT;
	const std::string kPointText = POINT_TEXT;

private:
	HighScores(); //Private constructor
	int GetSize(); //Get the list size
	int GetLowestScore(); //Get the lowest score on the list
	void Pop(); //Pop the last element
	HighScoreNode* mHead; //Head of the linked list
	static HighScores* sInstance; //Singleton instance
};

