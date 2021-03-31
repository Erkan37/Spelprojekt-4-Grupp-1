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
	myBar = std::make_unique<UIObject>(this);
	myBestTime = std::make_unique<UIObject>(this);
	myTitle = std::make_unique<UIObject>(this);
	
	myStartGameBtn = std::make_unique<UIButton>(this);
	myMainMenuBtn = std::make_unique<UIButton>(this);

	v2f barPos = {};
	v2f bestTimePos = {};
	v2f titlePos = {};
	v2f startGamePos = {};
	v2f mainMenuPos = {};

	//myBar->Init("Sprites/UI/speedRun/", , barPos, 201);
	//myBestTime->Init("Sprites/UI/speedRun/", , bestTimePos, 201);
	//myTitle->Init("Sprites/UI/speedRun/", , titlePos, 201);

	/*myStartGameBtn->Init("Sprites/UI/speedRun/", , startGamePos, );
	myMainMenuBtn->Init("Sprites/UI/pauseMenu/UI_PauseMenu_Text_MainMenu_Unmarked_64x16px.dds", { 64.f, 16.f }, mainMenuPos, "Sprites/UI/pauseMenu/UI_PauseMenu_Text_MainMenu_Marked_64x16px.dds", 64);*/

	myButtons.push_back(myStartGameBtn.get());
	myButtons.push_back(myMainMenuBtn.get());
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
	myBar->UpdateUIObjects(aDeltaTime);
	myBestTime->UpdateUIObjects(aDeltaTime);
	myTitle->UpdateUIObjects(aDeltaTime);
}
