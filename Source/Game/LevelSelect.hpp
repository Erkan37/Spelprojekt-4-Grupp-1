#pragma once
#include "Scene.h"

class InputWrapper;
class UIButton;

class LevelSelect : public Scene
{
public:
	LevelSelect();
	~LevelSelect();

	void Load() override;

	void Update(const float& aDeltaTime) override;

private:
	void CheckButtonPress();
	void InitiateButtons();

	std::vector<UIButton*> myLevelButtons;
	UIButton* myBackButton;

	std::shared_ptr<InputWrapper> myInput;

	int myLevelIndex;
	
	bool myIsSelectingLevel;
	bool myLevelWasStarted;

};

