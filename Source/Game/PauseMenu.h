#pragma once
#include "GameObject.h"
#include "UIButton.h"

#include "UIObject.h"
#include "Animation.hpp"

#include "UIText.h"
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
	void SelectButton();

private:
	Scene* myScene;
	Camera& myCamera;
	Animation myAnimation[1];

	std::unique_ptr<UIObject> myBackground;
	std::unique_ptr<UIObject> myBar;
	std::unique_ptr<UIObject> myFire;
	std::unique_ptr<UIObject> myFire2;
	std::unique_ptr<UIObject> myFire3;
	std::unique_ptr<UIObject> myFireHighlight;
	
	std::unique_ptr<UIObject> myContinueHighlight;
	std::unique_ptr<UIObject> myLevelSelectHighlight;
	std::unique_ptr<UIObject> myMainMenuHighlight;

	std::vector<UIObject*> myHighlights;


	std::vector<UIButton*> myButtons;

	std::unique_ptr<UIButton> myContinueBtn;
	std::unique_ptr<UIButton> myLevelSelectBtn;
	std::unique_ptr<UIButton> myMainMenuBtn;

	std::unique_ptr<UIText> myTitleString;
	std::unique_ptr<UIText> myCollectibleString;
	std::unique_ptr<UIText> myCollectibleString2;
	std::unique_ptr<UIText> myCollectibleString3;

	std::shared_ptr<InputWrapper> myInput;

	int myMovingIndex;

	bool myMenuActive;
	bool myIsSpeedrun;

	void CheckIndexPress();
	void ActivateMenu();
	void DeactivateMenu();
	void InitTexts();
	void UpdateUIElements(const float& aDeltaTime);
	void CheckActiveAnimations();
};

