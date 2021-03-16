#pragma once
#include "GameObject.h"
#include "UIButton.h"

class InputWrapper;
class Scene;

class PauseMenu : public GameObject
{
public:
	PauseMenu(Scene* aLevelScene);


	void Init();

	void Update(const float& aDeltaTime) override;


private:
	Scene* myScene;

	std::vector<UIButton*> myButtons;

	std::unique_ptr<UIButton> myContinueBtn;
	std::unique_ptr<UIButton> myLevelSelectBtn;
	std::unique_ptr<UIButton> myMainMenuBtn;

	std::shared_ptr<InputWrapper> myInput;

};

