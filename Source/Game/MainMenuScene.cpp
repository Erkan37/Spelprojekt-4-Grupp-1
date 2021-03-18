#include "stdafx.h"
#include "MainMenuScene.h"
#include "UIObject.h"

MainMenuScene::MainMenuScene()
{
}

void MainMenuScene::Load()
{
	myBackground = std::make_unique<UIObject>();
	myBackground->Init();
}

void MainMenuScene::Activate()
{
}

void MainMenuScene::Deactivate()
{
}

void MainMenuScene::Update(const float& aDeltaTime)
{
}
