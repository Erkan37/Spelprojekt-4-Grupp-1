#pragma once
#include "GameObject.h"
#include "UIButton.h"
#include "UIBackground.h"

class SpriteComponent;
class InputWrapper;
class Scene;

class PauseMenu
{
public:
	PauseMenu(Scene* aLevelScene);

	void Init();

	void Update(const float& aDeltaTime);


private:
	Scene* myScene;
	Camera& myCamera;

	v2f myPosition;

	std::unique_ptr<UIBackground> myBackground;

	std::vector<UIButton*> myButtons;

	std::unique_ptr<UIButton> myContinueBtn;
	std::unique_ptr<UIButton> myLevelSelectBtn;
	std::unique_ptr<UIButton> myMainMenuBtn;

	std::shared_ptr<InputWrapper> myInput;

	int check = {};

};

