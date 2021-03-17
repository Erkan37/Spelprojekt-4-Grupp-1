#include "stdafx.h"
#include "PauseMenu.h"
#include "SpriteComponent.h"
#include "UIButton.h"
#include "GameWorld.h"
#include "InputWrapper.h"
#include "Scene.h"
#include "Camera.h"
#include "Game.h"
#include "AnimationComponent.hpp"

PauseMenu::PauseMenu(Scene* aLevelScene)
	:
	myCamera(aLevelScene->GetCamera())
{
	myScene = aLevelScene;
	myMovingIndex = {};
	myMenuActive = {};
}

void PauseMenu::InitMenu()
{
	myInput = CGameWorld::GetInstance()->Input();

	myBackground = std::make_unique<UIObject>(myScene);
	v2f backgroundPos = {5.f, 5.f};
	myFire = std::make_unique<UIObject>(myScene);
	v2f firePos = {55.0f, 20.0f};

	myFireHighlight = std::make_unique<UIObject>(myScene);


	myContinueBtn = std::make_unique<UIButton>(myScene);
	v2f continuePos = { 220.f, 50.f };
	myLevelSelectBtn = std::make_unique<UIButton>(myScene);
	v2f levelSelectPos = { 220.f, 100.f };
	myMainMenuBtn = std::make_unique<UIButton>(myScene);
	v2f mainMenuPos = { 220.f, 150.f };

	
	myBackground->Init("Sprites/UI/pauseMenu/UI_PauseMenu_Bakground_304x164px.dds", {700.f, 340.f}, backgroundPos, 599);
	myFire->Init("Sprites/UI/pauseMenu/UI_PauseMenu_Flame_16x16px.dds", { 16.0f, 16.0f }, firePos, 600);
	myFireHighlight->InitAnimation("Sprites/UI/pauseMenu/UI_PauseMenu_Flame_16x16px.dds", { 16.0f, 16.0f }, { 200.0f, 70.0f }, 600);
	myContinueBtn->Init("Sprites/UI/pauseMenu/UI_PauseMenu_Text_Continue_Unmarked_64x16px.dds", { 64.f,16.f }, continuePos);
	myLevelSelectBtn->Init("Sprites/UI/pauseMenu/UI_PauseMenu_Text_LevelSelect_Unmarked_72x16px.dds", { 72.f,16.f }, levelSelectPos);
	myMainMenuBtn->Init("Sprites/UI/pauseMenu/UI_PauseMenu_Text_MainMenu_Unmarked_64x16px.dds", { 64.f,16.f }, mainMenuPos);
	
	myButtons.clear();

	myButtons.push_back(myContinueBtn.get());
	myButtons.push_back(myLevelSelectBtn.get());
	myButtons.push_back(myMainMenuBtn.get());
}

void PauseMenu::Update(const float& aDeltaTime)
{
	if (CGameWorld::GetInstance()->Input()->GetInput()->GetKeyJustDown(Keys::ESCKey))
		SetActiveMenu(!IsPauseActive());

	if (myMenuActive)
		ActivateMenu();
	else
		DeactivateMenu();

	if (myMenuActive)
	{
		myBackground->UpdateUIObjects(aDeltaTime);
		myFireHighlight->UpdateUIObjects(aDeltaTime);
		for (auto button : myButtons)
			button->UpdateButton(aDeltaTime);

		for (int i = 0; i < myButtons.size(); i++)
		{
			if (i == myMovingIndex)
			{
				myButtons[i]->SetIsHighlightActive(true);
				myFireHighlight->SetPositionX(myButtons[i]->GetPositionX() - 10.0f);
				myFireHighlight->SetPositionY(myButtons[i]->GetPositionY());
			}
			else
				myButtons[i]->SetIsHighlightActive(false);
		}

		CheckIndexPress();
	}
	
}


void PauseMenu::SetActiveMenu(const bool aStatement)
{
	myMenuActive = aStatement;
}

bool PauseMenu::IsPauseActive()
{
	return myMenuActive;
}


void PauseMenu::CheckIndexPress()
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
		//myButtons[myMovingIndex]->ActivateButton();
	}

}


void PauseMenu::ActivateMenu()
{
	for (auto button : myButtons)
		button->SetActive(true);

	myBackground->SetActive(true);
	myFire->SetActive(true);
	myFireHighlight->SetActive(true);
}


void PauseMenu::DeactivateMenu()
{
	for (auto button : myButtons)
		button->SetActive(false);

	myBackground->SetActive(false);
	myFire->SetActive(false);
	myFireHighlight->SetActive(false);
}


void PauseMenu::InitTexts()
{
	myTitleString = std::make_unique<TextWrapper>();
}