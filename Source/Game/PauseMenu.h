#pragma once
#include "GameObject.h"
#include "UIButton.h"
#include "UIBackground.h"

class SpriteComponent;
class InputWrapper;
class Scene;

class PauseMenu : public GameObject
{
public:
	PauseMenu(Scene* aLevelScene);

	void InitMenu();

	void Update(const float& aDeltaTime) override;

	void SetActiveMenu(const bool aStatement);
	bool IsPauseActive();


private:
	Scene* myScene;
	Camera& myCamera;

	std::unique_ptr<UIBackground> myBackground;

	std::vector<UIButton*> myButtons;

	std::unique_ptr<UIButton> myContinueBtn;
	std::unique_ptr<UIButton> myLevelSelectBtn;
	std::unique_ptr<UIButton> myMainMenuBtn;

	std::shared_ptr<InputWrapper> myInput;

	int myMovingIndex;

	bool myMenuActive;


	void CheckIndexPress();
	void ActivateMenu();
	void DeactivateMenu();

};

