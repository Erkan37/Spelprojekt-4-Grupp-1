#include "stdafx.h"
#include "MainMenuScene.h"
#include "UIObject.h"


MainMenuScene::MainMenuScene()
{
}

void MainMenuScene::Load()
{
	myBackground = std::make_unique<UIObject>(this);
	v2f backgroundPos = { 5.f, 5.f };

	myBackground->Init("Sprites/UI/pauseMenu/UI_PauseMenu_Bakground_304x164px.dds", { 520.f, 265.f }, backgroundPos, 599);

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
	myBackground->UpdateUIObjects(aDeltaTime);
}
