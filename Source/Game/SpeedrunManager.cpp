#include "stdafx.h"
#include "SpeedrunManager.h"

void SpeedrunManager::SetIsSpeedrun(const bool aIsSpeedrun)
{
	myIsSpeedrun = aIsSpeedrun;
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
}
