#pragma once
#include "Scene.h"

class UIObject;
class UIButton;
class InputWrapper;

class SpeedrunScene : public Scene
{
public:
	enum class eSpeedRunButton
	{
		StartGame,
		MainMenu
	};
	SpeedrunScene();
	~SpeedrunScene();
	
	void Load() override;
	void InitObjects();
	void Update(const float& aDeltaTime) override;


private:
	std::shared_ptr<InputWrapper> myInput;

	std::unique_ptr<UIObject> myTitle;
	std::unique_ptr<UIObject> myBackground;
	std::unique_ptr<UIObject> myBar;
	std::unique_ptr<UIObject> myBestTime;

	std::unique_ptr<UIButton> myStartGameBtn;
	std::unique_ptr<UIButton> myMainMenuBtn;

	std::vector<UIButton*> myButtons;

	bool myMovingIndex;

	void CheckButtonPress();
	void UpdateObjects(const float& aDeltaTime);
};

