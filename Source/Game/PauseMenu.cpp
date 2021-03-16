#include "stdafx.h"
#include "PauseMenu.h"
#include "SpriteComponent.h"
#include "UIButton.h"



PauseMenu::PauseMenu(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
{
	myScene = aLevelScene;
}

void PauseMenu::Init()
{
	myContinueBtn.Init(myScene);
	myLevelSelectBtn.Init(myScene);
	myMainMenuBtn.Init(myScene);

}
