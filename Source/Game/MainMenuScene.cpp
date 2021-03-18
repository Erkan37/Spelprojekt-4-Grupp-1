#include "stdafx.h"
#include "MainMenuScene.h"

#include "UIObject.h"
#include "UIButton.h"

#include "LevelManager.hpp"
#include "InputWrapper.h"

#include "Game.h"


MainMenuScene::MainMenuScene()
{
	myMovingIndex = {};
}

void MainMenuScene::Load()
{
	myButtons.clear();
	myMovingIndex = {};

	myInput = CGameWorld::GetInstance()->Input();

	InitObjects();

	Scene::Load();
}

void MainMenuScene::Activate()
{
	Scene::Activate();
}

void MainMenuScene::Deactivate()
{
	Scene::Deactivate();
}

void MainMenuScene::Update(const float& aDeltaTime)
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
	CheckButtonsPress();
	
}

void MainMenuScene::InitObjects()
{
	myBackground = std::make_unique<UIObject>(this);
	myTitleSprite = std::make_unique<UIObject>(this);
	myFireHighlight = std::make_unique<UIObject>(this);
	myNewGameBtn = std::make_unique<UIButton>(this);
	myLevelSelectBtn = std::make_unique<UIButton>(this);
	myOptionsBtn = std::make_unique<UIButton>(this);
	myExitGameBtn = std::make_unique<UIButton>(this);

	v2f backgroundPos = { 0.f, 0.f };
	v2f titleSpritePos = { 105.f, 25.f };
	
	v2f newGameBtnPos = {210.f, 80.f};
	v2f levelSelectBtnPos = { 210.f, 100.f };
	v2f optionsBtnPos = {210.f, 120.f};
	v2f exitGameBtnPos = {210.f, 140.f};
	
	myBackground->Init("Sprites/UI/startMenu/UI_startMenu_Background_320x180px.dds", { 520.f, 265.f }, backgroundPos, 599);
	myTitleSprite->Init("Sprites/UI/startMenu/UI_startMenu_Title_171x32px.dds", { 270.f, 32.f }, titleSpritePos, 600);
	myFireHighlight->InitAnimation("Sprites/UI/pauseMenu/UI_PauseMenu_Flame_16x16px.dds", { 16.0f, 16.0f }, { 200.0f, 70.0f }, 600);
	myNewGameBtn->Init("Sprites/UI/startMenu/UI_StartMenu_Text_NewGame_56x16px_unmarked.dds", { 56.f,16.f }, newGameBtnPos, "Sprites/UI/startMenu/UI_StartMenu_Text_NewGame_56x16px_marked.dds", 56);
	myLevelSelectBtn->Init("Sprites/UI/startMenu/UI_StartMenu_Text_LevelSelect_Unmarked_72x16px.dds", { 72.f,16.f }, levelSelectBtnPos, "Sprites/UI/startMenu/UI_StartMenu_Text_LevelSelect_Marked_72x16px.dds", 72);
	myOptionsBtn->Init("Sprites/UI/startMenu/UI_StartMenu_Text_Option_38x16px_unmarked.dds", { 38.f,16.f }, optionsBtnPos, "Sprites/UI/startMenu/UI_StartMenu_Text_Option_38x16px_marked.dds", 38);
	myExitGameBtn->Init("Sprites/UI/startMenu/UI_StartMenu_Text_QuitGame_56x16px_Unmarked.dds", { 56.f,16.f }, exitGameBtnPos, "Sprites/UI/startMenu/UI_StartMenu_Text_QuitGame_56x16px_Marked.dds", 56);
	
	SetActiveMenu(true);
	
	myButtons.push_back(myNewGameBtn.get());
	myButtons.push_back(myLevelSelectBtn.get());
	myButtons.push_back(myOptionsBtn.get());
	myButtons.push_back(myExitGameBtn.get());
}

void MainMenuScene::UpdateObjects(const float& aDeltaTime)
{
	myBackground->UpdateUIObjects(aDeltaTime);
	myTitleSprite->UpdateUIObjects(aDeltaTime);

	for (auto button : myButtons)
		button->UpdateButton(aDeltaTime);

	CheckActiveAnimations();
}

void MainMenuScene::CheckButtonsPress()
{
	if (myInput->GetInput()->GetKeyJustDown(Keys::UPARROWKey))
	{
		myMovingIndex--;
		if (myMovingIndex < 0)
			myMovingIndex = myButtons.size() - 1;
	}
	else if (myInput->GetInput()->GetKeyJustDown(Keys::DOWNARROWKey))
	{
		myMovingIndex++;
		if (myMovingIndex > myButtons.size() - 1)
			myMovingIndex = 0;
	}

	if (myInput->GetInput()->GetKeyJustDown(Keys::ENTERKey))
	{
		if (myMovingIndex == static_cast<int>(eMainMenuButton::StartGame))
			CGameWorld::GetInstance()->GetLevelManager().AdditiveLoadScene(LevelManager::eScenes::LevelScene);
		else if (myMovingIndex == static_cast<int>(eMainMenuButton::ExitGame))
			PostQuitMessage(0);
	}
}

void MainMenuScene::SetActiveMenu(const bool aStateBool)
{
	myBackground->SetActive(aStateBool);
	myTitleSprite->SetActive(aStateBool);
	myNewGameBtn->SetActive(aStateBool);
	myLevelSelectBtn->SetActive(aStateBool);
	myOptionsBtn->SetActive(aStateBool);
	myExitGameBtn->SetActive(aStateBool);
	myFireHighlight->SetActive(aStateBool);
}

void MainMenuScene::CheckActiveAnimations()
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
			myButtons[i]->SetIsHighlightActive(false);

	}
}
