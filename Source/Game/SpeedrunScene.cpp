#include "stdafx.h"
#include "SpeedrunScene.h"

#include "InputWrapper.h"

#include "GameWorld.h"
#include "Game.h"
#include "LevelManager.hpp"

#include "SpriteComponent.h"
#include "UIObject.h"
#include "UIButton.h"
#include "SpeedrunManager.h"

SpeedrunScene::SpeedrunScene()
{
	myMovingIndex = {};
	myIsInMenu = false;
}

void SpeedrunScene::Load()
{
	myButtons.clear();
	myInput = CGameWorld::GetInstance()->Input();

	InitObjects();
	myMovingIndex = {};
	myIsInMenu = false;

	Scene::Load();

}

void SpeedrunScene::InitObjects()
{
	myBackground = std::make_unique<UIObject>(this);
	myBackground2 = std::make_unique<UIObject>(this);
	myBar = std::make_unique<UIObject>(this);
	myBestTime = std::make_unique<UIObject>(this);
	myTitle = std::make_unique<UIObject>(this);
	myFireHighlight = std::make_unique<UIObject>(this);

	myStartGameBtn = std::make_unique<UIButton>(this);
	myMainMenuBtn = std::make_unique<UIButton>(this);

	v2f back2Pos = { 0.f, 0.f };
	v2f backgroundPos = { 5.f, 5.f };
	v2f barPos = { 60.f, 40.f };
	v2f bestTimePos = { 220.f, 50.f };
	v2f titlePos = { 125.f, 20.f };
	v2f startPos = { 120.f, 50.f };
	v2f mainMenuPos = { 120.f, 70.f };

	myBackground2->Init("Sprites/UI/startMenu/UI_startMenu_Background_320x180px.dds", { 520.f, 265.f }, back2Pos, 200);
	myBackground->Init("Sprites/UI/speedrunMenu/UI_speedrunMenu_304x164px.dds", { 520.f, 264.f }, backgroundPos, 201);
	myBar->Init("Sprites/UI/speedrunMenu/UI_speedrunMenu_MenuBar_241x3px.dds", { 241.f, 3.f }, barPos, 202);
	myBestTime->Init("Sprites/UI/speedrunMenu/UI_speedrunMenu_BestTime_54x10px.dds", { 60.f, 18.f }, bestTimePos, 202);
	myTitle->Init("Sprites/UI/speedrunMenu/UI_speedrunMenu_MenuTitle_166x20px.dds", { 220.f, 30.f }, titlePos, 202);
	myFireHighlight->InitAnimation("Sprites/UI/pauseMenu/UI_PauseMenu_Flame_16x16px.dds", { 16.0f, 16.0f }, { 200.0f, 70.0f }, 203);

	myStartGameBtn->Init("Sprites/UI/startMenu/UI_StartMenu_Text_NewGame_56x16px_unmarked.dds", { 56.f,16.f }, startPos, "Sprites/UI/startMenu/UI_StartMenu_Text_NewGame_56x16px_marked.dds", 56);
	myMainMenuBtn->Init("Sprites/UI/optionsMenu/UI_OptionsMenu_Text_MainMenu_Unmarked_64x16px.dds", { 64.f, 16.f }, mainMenuPos, "Sprites/UI/optionsMenu/UI_OptionsMenu_Text_MainMenu_Marked_64x16px.dds", 64);

	myButtons.push_back(myStartGameBtn.get());
	myButtons.push_back(myMainMenuBtn.get());

	SetActiveMenu(true);
}

void SpeedrunScene::Activate()
{
	Scene::Activate();
}

void SpeedrunScene::Deactivate()
{
	Scene::Deactivate();
}

void SpeedrunScene::Update(const float& aDeltaTime)
{

	const float zoomX = CGameWorld::GetInstance()->Game()->GetZoomX();
	const float zoomY = CGameWorld::GetInstance()->Game()->GetZoomY();

	float zoomFactor = 1.0f;
	if (zoomX / 16.0f < zoomY / 9.0f)
	{
		zoomFactor = zoomX / 1920.0f;
	}
	else
	{
		zoomFactor = zoomY / 1080.0f;
	}

	const float zoom = 6.0f * zoomFactor;

	GetCamera().SetZoom(zoom);

	GetCamera().SetBounds(v2f(0.0f, 0.0f), v2f(1920.0f, 1080.0f));

	Scene::Update(aDeltaTime);

	UpdateObjects(aDeltaTime);
	if (myIsInMenu)
	{
		CheckButtonPress();
	}
	myIsInMenu = true;

}


void SpeedrunScene::CheckButtonPress()
{
	if (myIsInMenu)
	{
		if (myInput->GetInput()->GetKeyJustDown(Keys::UPARROWKey) || myInput->GetController()->IsButtonPressed(Controller::Button::DPadUp))
		{
			myMovingIndex--;
			if (myMovingIndex < 0)
				myMovingIndex = myButtons.size() - 1;
		}
		else if (myInput->GetInput()->GetKeyJustDown(Keys::DOWNARROWKey) || myInput->GetController()->IsButtonPressed(Controller::Button::DPadDown))
		{
			myMovingIndex++;
			if (myMovingIndex > myButtons.size() - 1)
				myMovingIndex = 0;
		}


		if (myInput->GetInput()->GetKeyJustDown(Keys::ENTERKey) || myInput->GetController()->IsButtonPressed(Controller::Button::Cross))
		{


			if (myMovingIndex == static_cast<int>(eSpeedRunButton::StartGame))
			{
				CGameWorld::GetInstance()->GetLevelManager().GetSpeedrunManager()->SetIsSpeedrun(true);
				CGameWorld::GetInstance()->GetLevelManager().SetLevelIndex(0);
				CGameWorld::GetInstance()->GetLevelManager().SingleLoadScene(LevelManager::eScenes::LevelScene);
				myIsInMenu = false;

			}
			else if (myMovingIndex == static_cast<int>(eSpeedRunButton::MainMenu))
			{
				CGameWorld::GetInstance()->GetLevelManager().SingleLoadScene(LevelManager::eScenes::MainMenu);
				myIsInMenu = false;
			}


		}
	}
}

void SpeedrunScene::UpdateObjects(const float& aDeltaTime)
{
	myBackground2->UpdateUIObjects(aDeltaTime);
	myBackground->UpdateUIObjects(aDeltaTime);
	myBar->UpdateUIObjects(aDeltaTime);
	myBestTime->UpdateUIObjects(aDeltaTime);
	myTitle->UpdateUIObjects(aDeltaTime);

	CheckActiveanimations();
}

void SpeedrunScene::SetActiveMenu(const bool aStateBool)
{
	myBackground2->SetActive(aStateBool);
	myBackground->SetActive(aStateBool);
	myBar->SetActive(aStateBool);
	myBestTime->SetActive(aStateBool);
	myTitle->SetActive(aStateBool);
	myStartGameBtn->SetActive(aStateBool);
	myMainMenuBtn->SetActive(aStateBool);
	myFireHighlight->SetActive(aStateBool);

}

void SpeedrunScene::CheckActiveanimations()
{
	for (int i = 0; i < myButtons.size(); i++)
	{
		if (i == myMovingIndex)
		{
			myButtons[i]->SetIsHighlightActive(true);
			myFireHighlight->SetPositionX(myButtons[i]->GetPositionX() - 11.0f);
			myFireHighlight->SetPositionY(myButtons[i]->GetPositionY() + 4.f);
		}
		else
		{
			myButtons[i]->SetIsHighlightActive(false);
		}
	}
}
