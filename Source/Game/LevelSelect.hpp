#pragma once
#include "Scene.h"

class InputWrapper;
class UIButton;
class UIObject;
class UIText;

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

	void ShowArea(const int& aIndex);

	void InitCollectibles();
	void InitTexts();

	std::vector<UIObject*> myAreaTexts;
	std::vector<UIText*> myLevelCollectibles;
	std::vector<UIButton*> myLevelButtons;
	std::vector<int> myAreaIndexes;
	std::vector<int> myLevelIndexes;

	UIButton* myBackButton;
	UIObject* myBackButtonFire;

	std::shared_ptr<InputWrapper> myInput;

	int myLevelIndex;
	
	bool myIsSelectingLevel;
	bool myLevelWasStarted;

};

