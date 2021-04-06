#include "stdafx.h"
#include "SpeedrunScene.h"

#include "UIObject.h"
#include "UIButton.h"

#include "InputWrapper.h"
#include "GameWorld.h"

SpeedrunScene::SpeedrunScene()
{
	myMovingIndex = {};
}

SpeedrunScene::~SpeedrunScene()
{
}

void SpeedrunScene::Load()
{
	myButtons.clear();

}

void SpeedrunScene::InitObjects()
{
	myBackground = std::make_unique<UIObject>(this);
	myBar = std::make_unique<UIObject>(this);
	myBestTime = std::make_unique<UIObject>(this);
	myTitle = std::make_unique<UIObject>(this);
	
	myStartGameBtn = std::make_unique<UIButton>(this);
	myMainMenuBtn = std::make_unique<UIButton>(this);

	v2f backgroundPos = {};
	v2f barPos = {};
	v2f bestTimePos = {};
	v2f titlePos = {};
	v2f startGamePos = {};
	v2f mainMenuPos = {};

	myBackground->Init("Sprites/UI/speedrunMenu/UI_speedrunMenu_304x164px.dds", { 304.f, 164.f }, backgroundPos, 201);
	myBar->Init("Sprites/UI/speedrunMenu/UI_speedrunMenu_MenuBar_241x3px.dds", { 241.f, 3.f }, barPos, 202);
	myBestTime->Init("Sprites/UI/speedrunMenu/UI_speedrunMenu_BestTime_54x10px.dds", { 54.f, 10.f }, bestTimePos, 202);
	myTitle->Init("Sprites/UI/speedrunMenu/UI_speedrunMenu_MenuTitle_166x20px.dds", { 166.f, 20.f }, titlePos, 202);

	/*myStartGameBtn->Init("Sprites/UI/speedRun/", , startGamePos, );
	myMainMenuBtn->Init("Sprites/UI/pauseMenu/UI_PauseMenu_Text_MainMenu_Unmarked_64x16px.dds", { 64.f, 16.f }, mainMenuPos, "Sprites/UI/pauseMenu/UI_PauseMenu_Text_MainMenu_Marked_64x16px.dds", 64);*/

	//myButtons.push_back(myStartGameBtn.get());
	//myButtons.push_back(myMainMenuBtn.get());
}

void SpeedrunScene::Update(const float& aDeltaTime)
{
}

void SpeedrunScene::CheckButtonPress()
{
	if (myInput->GetInput()->GetKeyJustDown(Keys::ENTERKey))
	{
		if (myMovingIndex == static_cast<int>(eSpeedRunButton::StartGame))
		{
			/*CGameWorld::GetInstance()->GetLevelManager().SingleLoadScene()*/
		}
		else
			CGameWorld::GetInstance()->GetLevelManager().SingleLoadScene(LevelManager::eScenes::MainMenu);
	}
}

void SpeedrunScene::UpdateObjects(const float& aDeltaTime)
{
	myBackground->UpdateUIObjects(aDeltaTime);
	myBar->UpdateUIObjects(aDeltaTime);
	myBestTime->UpdateUIObjects(aDeltaTime);
	myTitle->UpdateUIObjects(aDeltaTime);
}
