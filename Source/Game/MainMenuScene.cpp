#include "stdafx.h"
#include "MainMenuScene.h"
#include "UIObject.h"
#include "UIButton.h"
#include "Game.h"


MainMenuScene::MainMenuScene()
{
}

void MainMenuScene::Load()
{
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
	
}

void MainMenuScene::InitObjects()
{
	myBackground = std::make_unique<UIObject>(this);
	myNewGameBtn = std::make_unique<UIButton>(this);
	myLevelSelectBtn = std::make_unique<UIButton>(this);
	myOptionsBtn = std::make_unique<UIButton>(this);
	myExitGameBtn = std::make_unique<UIButton>(this);

	v2f backgroundPos = { 0.f, 0.f };
	
	v2f newGameBtnPos = {200.f, 50.f};
	v2f levelSelectBtnPos = { 200.f, 75.f };
	v2f optionsBtnPos = {200.f, 100.f};
	v2f exitGameBtnPos = {200.f, 125.f};
	
	myBackground->Init("Sprites/UI/startMenu/UI_startMenu_Background_320x180px.dds", { 520.f, 265.f }, backgroundPos, 599);
	myNewGameBtn->Init("Sprites/UI/pauseMenu/UI_PauseMenu_Text_Continue_Unmarked_64x16px.dds", { 64.f,16.f }, newGameBtnPos, "Sprites/UI/pauseMenu/UI_PauseMenu_Text_Continue_Marked_64x16px.dds", 64);
	myLevelSelectBtn->Init("Sprites/UI/pauseMenu/UI_PauseMenu_Text_LevelSelect_Unmarked_72x16px.dds", { 72.f,16.f }, levelSelectBtnPos, "Sprites/UI/pauseMenu/UI_PauseMenu_Text_LevelSelect_Marked_72x16px.dds", 72);
	myOptionsBtn->Init("Sprites/UI/pauseMenu/UI_PauseMenu_Text_MainMenu_Unmarked_64x16px.dds", { 64.f,16.f }, optionsBtnPos, "Sprites/UI/pauseMenu/UI_PauseMenu_Text_MainMenu_Marked_64x16px.dds", 64);
	myExitGameBtn->Init("Sprites/UI/pauseMenu/UI_PauseMenu_Text_MainMenu_Unmarked_64x16px.dds", { 64.f,16.f }, exitGameBtnPos, "Sprites/UI/pauseMenu/UI_PauseMenu_Text_MainMenu_Marked_64x16px.dds", 64);
	
	myBackground->SetActive(true);
	myNewGameBtn->SetActive(true);
	myLevelSelectBtn->SetActive(true);
	myOptionsBtn->SetActive(true);
	myExitGameBtn->SetActive(true);

	myButtons.push_back(myNewGameBtn.get());
	myButtons.push_back(myLevelSelectBtn.get());
	myButtons.push_back(myOptionsBtn.get());
	myButtons.push_back(myExitGameBtn.get());
}

void MainMenuScene::UpdateObjects(const float& aDeltaTime)
{
	myBackground->UpdateUIObjects(aDeltaTime);

	for (auto button : myButtons)
		button->UpdateButton(aDeltaTime);
}
