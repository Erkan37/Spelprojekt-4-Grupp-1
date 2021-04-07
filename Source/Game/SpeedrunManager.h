#pragma once
#include <array>

class SpeedrunManager
{
public:

	void SetIsSpeedrun(const bool aIsSpeedrun);
	bool GetIsSpeedrun();

	float GetScore();
	void SetScore(const float aScore);
	void AddToScore(const float aScore);	
	void ReportScoreToHighscores();

private:
	bool myIsSpeedrun;
	float myCurrentScore;
	std::array<float, 10> myHighScores = { 1, 3, 4, 56, 99, 7, 8, 3, 3, 23444 };
};

