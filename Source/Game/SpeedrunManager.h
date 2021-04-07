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
	std::array<float, 10> myHighScores;
};

