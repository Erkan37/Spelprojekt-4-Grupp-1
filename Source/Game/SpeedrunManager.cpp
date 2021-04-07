#include "stdafx.h"
#include "SpeedrunManager.h"

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
	//Should the player be able to get their name in the list too?
	for (int i = 0; i < myHighScores.size(); ++i)
	{
		if (myCurrentScore > myHighScores[i])
		{
			float temp = myHighScores[i];
			myHighScores[i] = myCurrentScore;
			myCurrentScore = temp;
		}
	}
	myCurrentScore = 0;
}
