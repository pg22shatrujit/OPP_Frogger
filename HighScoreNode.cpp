//Copyright (C) 2022 Shatrujit Aditya Kumar & Andre Dupuis, All Rights Reserved
#include "HighScoreNode.h"

HighScoreNode::~HighScoreNode() {}

//Constructor defaults mNext to nullptr if not specified
HighScoreNode::HighScoreNode(std::string name, int score, HighScoreNode* next)
{
	mScore = score;
	mName = name;
	mNext = next;
}

//Get next node
HighScoreNode* HighScoreNode::GetNext()
{
	return mNext;
}

//Set next node
void HighScoreNode::SetNext(HighScoreNode* next)
{
	mNext = next;
}

//Get score
int HighScoreNode::GetScore()
{
	return mScore;
}

//Get name
std::string HighScoreNode::GetName()
{
	return mName;
}