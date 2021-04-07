#include "stdafx.h"
#include "SpeedrunManager.h"
#include "DataManager.h"

void SpeedrunManager::SetIsSpeedrun(const bool aIsSpeedrun)
{
	myIsSpeedrun = aIsSpeedrun;
	if (myIsSpeedrun == false)
	{
		myCurrentScore = 0;
	}
}
bool SpeedrunManager::GetIsSpeedrun()
{
	return myIsSpeedrun;
}

float SpeedrunManager::GetScore()
{
	return myCurrentScore;
}
void SpeedrunManager::SetScore(const float aScore)
{
	myCurrentScore = aScore;
}
void SpeedrunManager::AddToScore(const float aScore)
{
	myCurrentScore += aScore;
}

void SpeedrunManager::ReportScoreToHighscores()
{
	//Check if score is a highscore
	//If it is, add it to list (show to player)
	//reset current score

	// Call
	// DataManager::GetInstance().SaveHighScores(myHighScores);
	// When you have a new Highscore to change.
}