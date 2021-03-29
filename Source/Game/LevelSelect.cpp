#include "stdafx.h"
#include "LevelSelect.hpp"

#include "InputWrapper.h"
#include "AudioManager.h"

#include "GameWorld.h"
#include "Game.h"
#include "LevelManager.hpp"

#include "SpriteComponent.h"

LevelSelect::LevelSelect()
{
	myIsSelectingLevel = true;
	myLevelWasStarted = false;
	myLevelIndex = 0;
	myBackButton = nullptr;
	myInput = nullptr;
}

LevelSelect::~LevelSelect()
{

}

void LevelSelect::Load()
{
	myLevelButtons.clear();

	myInput = CGameWorld::GetInstance()->Input();

	myLevelWasStarted = false;
	myIsSelectingLevel = true;
	myLevelIndex = 0;

	InitiateButtons();

	GameObject* background = new GameObject(this);
	background->SetPosition(v2f(0.0f, 0.0f));
	background->SetPivot(v2f(0.0f, 0.0f));
	background->AddComponent<SpriteComponent>();
	background->GetComponent<SpriteComponent>()->SetSpritePath("Sprites/UI/startMenu/UI_startMenu_Background_320x180px.dds");
	background->SetZIndex(200);

	Scene::Load();
}

void LevelSelect::Update(const float& aDeltaTime)
{
	if (myLevelWasStarted)
	{
		CheckButtonPress();
	}
	
	myLevelWasStarted = true;

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
}

void LevelSelect::CheckButtonPress()
{
	if (myIsSelectingLevel)
	{
		if (myInput->GetInput()->GetKeyJustDown(Keys::LEFTARROWKey) || myInput->GetController()->IsButtonPressed(Controller::Button::DPadLeft))
		{
			myLevelButtons[myLevelIndex]->SetIsHighlightActive(false);
			myLevelIndex--;
			AudioManager::GetInstance()->PlayAudio(AudioList::MenuMove);
			if (myLevelIndex < 0)
			{
				myLevelIndex = myLevelButtons.size() - 1;
			}
			myLevelButtons[myLevelIndex]->SetIsHighlightActive(true);
		}
		else if (myInput->GetInput()->GetKeyJustDown(Keys::RIGHTARROWKey) || myInput->GetController()->IsButtonPressed(Controller::Button::DPadRight))
		{
			myLevelButtons[myLevelIndex]->SetIsHighlightActive(false);
			myLevelIndex++;
			AudioManager::GetInstance()->PlayAudio(AudioList::MenuMove);
			if (myLevelIndex > myLevelButtons.size() - 1)
			{
				myLevelIndex = 0;
			}
			myLevelButtons[myLevelIndex]->SetIsHighlightActive(true);
		}
	}
	
	if ((myInput->GetInput()->GetKeyJustDown(Keys::DOWNARROWKey) || myInput->GetController()->IsButtonPressed(Controller::Button::DPadDown)) ||
		myInput->GetInput()->GetKeyJustDown(Keys::UPARROWKey) || myInput->GetController()->IsButtonPressed(Controller::Button::DPadUp))
	{
		myIsSelectingLevel = !myIsSelectingLevel;
		AudioManager::GetInstance()->PlayAudio(AudioList::MenuMove);

		if (myIsSelectingLevel)
		{
			myBackButton->SetIsHighlightActive(false);
			myLevelButtons[myLevelIndex]->SetIsHighlightActive(true);
		}
		else
		{
			myLevelButtons[myLevelIndex]->SetIsHighlightActive(false);
			myBackButton->SetIsHighlightActive(true);
		}
	}

	if (myInput->GetInput()->GetKeyJustDown(Keys::ENTERKey) || myInput->GetController()->IsButtonPressed(Controller::Button::Cross))
	{
		if (myIsSelectingLevel)
		{
			CGameWorld::GetInstance()->GetLevelManager().SingleLoadScene(LevelManager::eScenes::LevelScene);
		}
		else
		{
			CGameWorld::GetInstance()->GetLevelManager().SingleLoadScene(LevelManager::eScenes::MainMenu);
		}
	}
}

void LevelSelect::InitiateButtons()
{
	for (int i = 0; i < 7; ++i)
	{
		UIButton* levelButton = new UIButton(this);
		myLevelButtons.push_back(levelButton);
	}

	myBackButton = new UIButton(this);
	myBackButton->Init("Sprites/UI/levelSelect/UnselectedLevel.dds", v2f(16.0f, 16.0f), v2f(16.0f, 160.0f), "Sprites/UI/levelSelect/SelectedLevel.dds", 16);
	myBackButton->SetPosition(v2f(16.0f, 160.0f));
	myBackButton->GetComponent<SpriteComponent>()->SetSize(v2f(16.0f, 16.0f));
	myBackButton->SetPivot(v2f(0.0f, 0.0f));
	myBackButton->SetActive(true);

	const float offsetX = 320.0f / static_cast<float>(myLevelButtons.size());

	for (int buttonIndex = 0; buttonIndex < static_cast<int>(myLevelButtons.size()); ++buttonIndex)
	{
		myLevelButtons[buttonIndex]->SetPositionX((buttonIndex + 1) * offsetX);
		myLevelButtons[buttonIndex]->SetPositionY(50.0f);
		myLevelButtons[buttonIndex]->Init("Sprites/UI/levelSelect/UnselectedLevel.dds", v2f(16.0f, 16.0f), v2f((buttonIndex) * offsetX + 16.0f, 50.0f), "Sprites/UI/levelSelect/SelectedLevel.dds", 16);
		myLevelButtons[buttonIndex]->GetComponent<SpriteComponent>()->SetSize(v2f(16.0f, 16.0f));
		myLevelButtons[buttonIndex]->SetPivot(v2f(0.0f, 0.0f));
		myLevelButtons[buttonIndex]->SetActive(true);
	}

	myLevelButtons[0]->SetIsHighlightActive(true);
}