#include "stdafx.h"
#include "LevelSelect.hpp"

#include "InputWrapper.h"
#include "AudioManager.h"

#include "GameWorld.h"
#include "Game.h"
#include "LevelManager.hpp"

#include "SpriteComponent.h"

#include "UIButton.h"
#include "UIObject.h"

#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>

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

	SpriteComponent* sprite = background->AddComponent<SpriteComponent>();
	sprite->SetSpritePath("Sprites/UI/levelSelect/UI_levelSelect_Background_304x164px.dds");
	background->SetZIndex(200);

	background->SetPosition(v2f(0.0f, 0.0f));
	background->SetPivot(v2f(0.0f, 0.0f));

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
		if (static_cast<int>(myLevelButtons.size()) > 0)
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
	}
	
	if ((myInput->GetInput()->GetKeyJustDown(Keys::DOWNARROWKey) || myInput->GetController()->IsButtonPressed(Controller::Button::DPadDown)) ||
		myInput->GetInput()->GetKeyJustDown(Keys::UPARROWKey) || myInput->GetController()->IsButtonPressed(Controller::Button::DPadUp))
	{
		if (static_cast<int>(myLevelButtons.size()) > 0)
		{
			myIsSelectingLevel = !myIsSelectingLevel;
			AudioManager::GetInstance()->PlayAudio(AudioList::MenuMove);

			if (myIsSelectingLevel)
			{
				myBackButton->SetIsHighlightActive(false);
				myBackButtonFire->SetActive(false);

				if (static_cast<int>(myLevelButtons.size()) > 0)
				{
					myLevelButtons[myLevelIndex]->SetIsHighlightActive(true);
				}
			}
			else
			{
				if (static_cast<int>(myLevelButtons.size()) > 0)
				{
					myLevelButtons[myLevelIndex]->SetIsHighlightActive(false);
				}

				myBackButton->SetIsHighlightActive(true);
				myBackButtonFire->SetActive(true);
			}
		}
	}

	if (myInput->GetInput()->GetKeyJustDown(Keys::ENTERKey) || myInput->GetController()->IsButtonPressed(Controller::Button::Cross))
	{
		if (myIsSelectingLevel)
		{
			if (static_cast<int>(myLevelButtons.size()) <= 0)
			{
				return;
			}

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
	myBackButton = new UIButton(this);
	myBackButton->Init("Sprites/UI/levelSelect/UI_levelSelect_Text_MainMenu_Unmarked_64x16px.dds", v2f(64.0f, 16.0f), v2f(250.0f, 160.0f), "Sprites/UI/levelSelect/UI_levelSelect_Text_MainMenu_Marked_64x16px.dds", 64);
	myBackButton->SetPosition(v2f(250.0f, 160.0f));
	myBackButton->GetComponent<SpriteComponent>()->SetSize(v2f(64.0f, 16.0f));
	myBackButton->SetPivot(v2f(0.0f, 0.0f));
	myBackButton->SetActive(true);

	myBackButtonFire = new UIObject(this);
	myBackButtonFire->InitAnimation("Sprites/UI/levelSelect/UI_levelSelect_Flame_16x16px.dds", v2f(16.0f, 16.0f), v2f(232.0f, 156), 201);
	myBackButtonFire->SetPosition(v2f(232.0f, 156.0f));
	myBackButtonFire->SetPivot(v2f(0.0f, 0.0f));

	std::ifstream levelSelectFile("JSON/Menus/LevelSelect/LevelSelect.json");
	rapidjson::IStreamWrapper levelSelectStream(levelSelectFile);

	rapidjson::Document levelSelect;
	levelSelect.ParseStream(levelSelectStream);

	for (rapidjson::Value::ConstValueIterator iterator = levelSelect["Bonfires"].Begin(); iterator != levelSelect["Bonfires"].End(); ++iterator)
	{
		if ((*iterator)["Unlocked"].GetInt() == 1)
		{
			UIButton* levelButton = new UIButton(this);
			levelButton->SetPosition(v2f((*iterator)["X"].GetFloat(), (*iterator)["Y"].GetFloat()));
			levelButton->Init("Sprites/UI/levelSelect/UI_levelSelect_Stage_320x180px_Marked.dds", v2f(8.0f, 8.0f), v2f((*iterator)["X"].GetFloat(), (*iterator)["Y"].GetFloat()), "Sprites/UI/levelSelect/UI_levelSelect_Flame_16x16px.dds", 16);
			levelButton->GetComponent<SpriteComponent>()->SetSize(v2f(8.0f, 8.0f));
			levelButton->SetPivot(v2f(0.0f, 0.0f));
			levelButton->SetActive(true);
			levelButton->SetHighlightOffset(v2f(-2.0f, -3.0f));
			myLevelButtons.push_back(levelButton);
		}
	}

	if (static_cast<int>(myLevelButtons.size()) > 0)
	{
		myLevelButtons[0]->SetIsHighlightActive(true);
	}
	else
	{
		myBackButton->SetIsHighlightActive(true);
		myBackButtonFire->SetActive(true);
		myIsSelectingLevel = false;
	}
}