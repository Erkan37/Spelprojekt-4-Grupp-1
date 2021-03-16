#include "stdafx.h"
#include "PauseMenu.h"
#include "SpriteComponent.h"
#include "UIButton.h"
#include "GameWorld.h"
#include "InputWrapper.h"
#include "Scene.h"

PauseMenu::PauseMenu(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
{
	myScene = aLevelScene;
}

void PauseMenu::Init()
{
	myInput = CGameWorld::GetInstance()->Input();

	myContinueBtn = std::make_unique<UIButton>(myScene);
	myLevelSelectBtn = std::make_unique<UIButton>(myScene);
	myMainMenuBtn = std::make_unique<UIButton>(myScene);

	myContinueBtn->Init("Sprites/UI/UI_PauseMenu_Text_Continue_Unmarked_64x16px.dds", { 64.f,16.f });
	myLevelSelectBtn->Init("Sprites/UI/UI_PauseMenu_Text_LevelSelect_Unmarked_72x16px.dds", { 72.f,16.f });
	myMainMenuBtn->Init("Sprites/UI/UI_PauseMenu_Text_MainMenu_Unmarked_64x16px.dds", { 64.f,16.f });

	myButtons.push_back(myContinueBtn.get());
	myButtons.push_back(myLevelSelectBtn.get());
	myButtons.push_back(myMainMenuBtn.get());

}

void PauseMenu::Update(const float& aDeltaTime)
{
	if (myInput->GetInput()->GetKeyJustDown(Keys::RKey))
		std::cout << "R KEY PUSHED" << std::endl;
}
