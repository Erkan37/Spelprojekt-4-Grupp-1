#pragma once
#include "GameObject.h"
#include "UIButton.h"

#include "UIObject.h"
#include "Animation.hpp"
#include "TextWrapper.h"

class SpriteComponent;
class InputWrapper;
class Scene;
class Animation;

class PauseMenu
{
public:
	PauseMenu(Scene* aLevelScene);

	void InitMenu();

	void Update(const float& aDeltaTime);

	void SetActiveMenu(const bool aStatement);
	bool IsPauseActive();


private:
	Scene* myScene;
	Camera& myCamera;
	Animation myAnimation[1];

	std::unique_ptr<UIObject> myBackground;
	std::unique_ptr<UIObject> myFire;
	std::unique_ptr<UIObject> myFire2;
	std::unique_ptr<UIObject> myFire3;
	std::unique_ptr<UIObject> myFireHighlight;


	std::vector<UIButton*> myButtons;

	std::unique_ptr<UIButton> myContinueBtn;
	std::unique_ptr<UIButton> myLevelSelectBtn;
	std::unique_ptr<UIButton> myMainMenuBtn;




	std::unique_ptr<TextWrapper> myTitleString;

	std::shared_ptr<InputWrapper> myInput;

	int myMovingIndex;

	bool myMenuActive;


	void CheckIndexPress();
	void ActivateMenu();
	void DeactivateMenu();
	void InitTexts();

};

