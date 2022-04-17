//Copyright (C) 2022 Shatrujit Aditya Kumar & Andre Dupuis, All Rights Reserved
#include "HighScores.h"

HighScores* HighScores::sInstance = nullptr;

//Initialize head to null
HighScores::HighScores()
{
	mHead = nullptr;
}

//Iterate through the list and return the size
int HighScores::GetSize()
{
	int size = 0;
	HighScoreNode* currentNode = mHead;
	while (currentNode != nullptr) {
		++size;
		currentNode = currentNode->GetNext();
	}
	return size;
}

//Iterate through the list to get the lowest score
//Add happens in descending order so this should in theory always be the last node, but just incase
int HighScores::GetLowestScore()
{
	if (mHead == nullptr) return -1;

	HighScoreNode* currentNode = mHead;
	int lowest = mHead->GetScore();
	while (currentNode != nullptr) {
		if (lowest > currentNode->GetScore())
			lowest = currentNode->GetScore();

		currentNode = currentNode->GetNext();
	}

	return lowest;
}

//Remove the last node from the list, used when the list has reached max size and we need to add more nodes
void HighScores::Pop()
{
	if (mHead == nullptr) return;
	if (mHead->GetNext() == nullptr) {
		delete mHead;
		mHead = nullptr;
	}

	HighScoreNode* currentNode = mHead;
	while (currentNode != nullptr) {
		if (currentNode->GetNext()->GetNext() == nullptr) {
			delete currentNode->GetNext();
			currentNode->SetNext(nullptr);
			break;
		}
		currentNode = currentNode->GetNext();
	}
}

//Destructor checks if the instance exists, if it does delete all nodes on the list and then the instance
HighScores::~HighScores()
{
	if (sInstance != nullptr) {

		HighScoreNode* currentNode = mHead;

		while (currentNode != nullptr) {
			HighScoreNode* temp = currentNode->GetNext();
			delete currentNode;
			currentNode = temp;
		}

		delete sInstance;
		sInstance = nullptr;
	}
}

//Get a reference to the singleton instance
HighScores* HighScores::GetInstance()
{
	if (sInstance == nullptr) {
		sInstance = new HighScores();
	}
	return sInstance;
}

//Get reference to the list head
HighScoreNode* HighScores::GetHead()
{
	return mHead;
}

//Add a new node to the list
void HighScores::Add(std::string name, int score)
{
	//Check if we're at or greater than max size and pop if true
	if (GetSize() >= MAX_SIZE) {
		Pop();
	}

	//If empty list, new node is head
	if (mHead == nullptr) {
		mHead = new HighScoreNode(name, score);
		return;
	}

	//If score is greater than head's score, new node becomes new head
	if (score > mHead->GetScore()) {
		HighScoreNode* nodeToInsert = new HighScoreNode(name, score, mHead);
		mHead = nodeToInsert;
		return;
	}

	//Check scores at each postion to find where the node should go
	HighScoreNode* currentNode = mHead;
	while (currentNode != nullptr) {
		if (currentNode->GetNext() == nullptr) {
			HighScoreNode* nodeToInsert = new HighScoreNode(name, score);
			currentNode->SetNext(nodeToInsert);
			break;
		}
		else if (currentNode->GetNext()->GetScore() < score) {
			HighScoreNode* nodeToInsert = new HighScoreNode(name, score, currentNode->GetNext());
			currentNode->SetNext(nodeToInsert);
			break;
		}
		currentNode = currentNode->GetNext();
	}
}

//Should add a score if either the list is not full or the score is higher than the lowest score;
bool HighScores::ShouldAddScore(int score)
{
	return GetSize() < MAX_SIZE || score > GetLowestScore();
}
