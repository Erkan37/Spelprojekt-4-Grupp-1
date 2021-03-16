#pragma once
#include "GameObject.h"
#include "UIButton.h"

class Scene;

class PauseMenu : public GameObject
{
public:
	PauseMenu(Scene* aLevelScene);


	void Init();

	


private:
	UIButton myContinueBtn;
	UIButton myLevelSelectBtn;
	UIButton myMainMenuBtn;

	Scene* myScene;

};

