#include "stdafx.h"
#include "OptionsMenu.h"

#include "GameWorld.h"
#include "InputWrapper.h"
#include "Scene.h"
#include "MainMenuScene.h"
#include "Camera.h"
#include "Game.h"

#include "AnimationComponent.hpp"

OptionsMenu::OptionsMenu(Scene* aLevelScene)
	: myCamera(aLevelScene->GetCamera())
{
	myScene = aLevelScene;
	myMovingIndex = {};
	myMenuAcitve = {};
}

void OptionsMenu::Init()
{
	v2f referenceSize = Config::ourReferenceSize;

	myInput = CGameWorld::GetInstance()->Input();

	myBackground = std::make_unique<UIObject>(myScene);
	myFireHighlight = std::make_unique<UIObject>(myScene);


	v2f backgroundPos = { 0.f, 0.f };


	myCreditsBtn = std::make_unique<UIButton>(myScene);
	v2f creditsPos = { 210.f, 100.f };
	myResetBtn = std::make_unique<UIButton>(myScene);
	v2f resetPos = { 210.f, 125.f };
	myBackBtn = std::make_unique<UIButton>(myScene);
	v2f backPos = { 210.f, 150.f };

	myBackground->Init("Sprites/UI/startMenu/UI_startMenu_Background_320x180px.dds", { 520.f, 265.f }, backgroundPos, 599);
	myFireHighlight->InitAnimation("Sprites/UI/pauseMenu/UI_PauseMenu_Flame_16x16px.dds", { 16.0f, 16.0f }, { 200.0f, 70.0f }, 600);
	myCreditsBtn->Init("Sprites/UI/optionsMenu/tempCredits.dds", { 56.f, 16.f }, creditsPos, "Sprites/UI/optionsMenu/tempCredits.dds", 56);
	myResetBtn->Init("Sprites/UI/optionsMenu/tempResetGame.dds", { 56.f, 16.f }, resetPos, "Sprites/UI/optionsMenu/tempResetGame.dds", 56);
	myBackBtn->Init("Sprites/UI/pauseMenu/UI_PauseMenu_Text_MainMenu_Unmarked_64x16px.dds", { 64.f,16.f }, backPos, "Sprites/UI/pauseMenu/UI_PauseMenu_Text_MainMenu_Marked_64x16px.dds", 64);

	myButtons.push_back(myCreditsBtn.get());
	myButtons.push_back(myResetBtn.get());
	myButtons.push_back(myBackBtn.get());

}

void OptionsMenu::Update(const float& aDeltaTime)
{
	if (myMenuAcitve)
	{
		ActivateMenu();
		SelectButton();
		UpdateUIElements(aDeltaTime);
		CheckActiveAnimations();
		CheckIndexPress();
	}
	else
		DeactivateMenu();
}

void OptionsMenu::SetActive(const bool aStatement)
{
	myMenuAcitve = aStatement;
}

bool OptionsMenu::IsOptionsActive()
{
	return myMenuAcitve;
}

void OptionsMenu::SelectButton()
{
	if (myInput->GetInput()->GetKeyJustDown(Keys::AKey))
	{
		SetActive(false);
		CGameWorld::GetInstance()->GetLevelManager().ReloadScene(LevelManager::eScenes::MainMenu);
	}
}

void OptionsMenu::CheckIndexPress()
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
		if (myMovingIndex == static_cast<int>(eOptionsMenu::Back))
		{
			CGameWorld::GetInstance()->GetLevelManager().ReloadScene(LevelManager::eScenes::MainMenu);
		}

	}
}

void OptionsMenu::ActivateMenu()
{
	for (auto button : myButtons)
		button->SetActive(true);

	myBackground->SetActive(true);
	myFireHighlight->SetActive(true);

}

void OptionsMenu::DeactivateMenu()
{
	myBackground->SetActive(false);
	myBackBtn->SetActive(false);
}

void OptionsMenu::InitTexts()
{
}

void OptionsMenu::UpdateUIElements(const float& aDeltaTime)
{
	myBackground->UpdateUIObjects(aDeltaTime);

	for (auto button : myButtons)
		button->UpdateButton(true);
}

void OptionsMenu::CheckActiveAnimations()
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


