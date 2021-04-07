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

	// Call
	// DataManager::GetInstance().SaveHighScores(myHighScores);
	// When you have a new Highscore to change.
}

