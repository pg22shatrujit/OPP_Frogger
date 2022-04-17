//Copyright (C) 2022 Shatrujit Aditya Kumar & Andre Dupuis, All Rights Reserved
#pragma once
#include "Utils.h"
class HighScoreNode
{
public:
	HighScoreNode() = delete; //Remove default constructor
	~HighScoreNode(); 
	HighScoreNode(std::string name, int score, HighScoreNode* next = nullptr);
	HighScoreNode* GetNext(); //Get the next node
	void SetNext(HighScoreNode* next); //Set the next node
	int GetScore(); //Get the score
	std::string GetName(); //Get the name
private:
	std::string mName;
	int mScore;
	HighScoreNode* mNext;
};