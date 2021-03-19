#include "stdafx.h"
#include "PopUp.h"
#include "SpriteComponent.h"
#include "GameWorld.h"
#include "Scene.h"
#include "Game.h"




PopUp::PopUp(Scene* aLevelScene)
	: GameObject(aLevelScene)
{
	myScene = aLevelScene;
	myEasyActive = {};
	myCurrentTime = 0.0f;
	myMaxTime = 2.0f;
}

void PopUp::InitPopUp()
{
	v2f referenceSize = Config::ourReferenceSize;

	myBackground = std::make_unique<UIObject>(myScene);
	v2f backPos = { 265.0f, 15.0f };
	myFireEasy = std::make_unique<UIObject>(myScene);
	v2f fireEPos = { 280.0f, 30.0f };
	myFireMedium = std::make_unique<UIObject>(myScene);
	v2f fireMPos = { 280.0f, 30.0f };
	myFireHard = std::make_unique<UIObject>(myScene);
	v2f fireHPos = { 280.0f, 30.0f };

	myBackground->Init("Sprites/UI/popUp/UI_PopUp_84x32px.dds", { 84.0f, 32.0f }, backPos, 599);
	myFireEasy->InitAnimation("Sprites/UI/pauseMenu/UI_Collectible_Soul_Green_16x16px.dds", { 16.0f, 16.0f }, fireEPos, 600);
	myFireMedium->InitAnimation("Sprites/UI/pauseMenu/UI_Collectible_Soul_Yellow_16x16px.dds", { 16.0f, 16.0f }, fireMPos, 600);
	myFireHard->InitAnimation("Sprites/UI/pauseMenu/UI_Collectible_Soul_Red_16x16px.dds", { 16.0f, 16.0f }, fireHPos, 600);

}

void PopUp::Update(const float& aDeltaTime)
{
	//isEasyActive();
	if (myEasyActive == true)
	{
		myCurrentTime += aDeltaTime;
		myBackground->UpdateUIObjects(aDeltaTime);
		myFireEasy->UpdateUIObjects(aDeltaTime);
		Activate(ePopUpTypes::Easy);

	}
	if (myCurrentTime > myMaxTime)
	{
		myEasyActive = false;
		Deactivate(ePopUpTypes::Easy);
	}
	if (myMediumActive == true)
	{
		myCurrentTime += aDeltaTime;
		myBackground->UpdateUIObjects(aDeltaTime);
		myFireMedium->UpdateUIObjects(aDeltaTime);
		Activate(ePopUpTypes::Medium);

	}
	if (myCurrentTime > myMaxTime)
	{
		myMediumActive = false;
		Deactivate(ePopUpTypes::Medium);
	}
	if (myHardActive == true)
	{
		myCurrentTime += aDeltaTime;
		myBackground->UpdateUIObjects(aDeltaTime);
		myFireHard->UpdateUIObjects(aDeltaTime);
		Activate(ePopUpTypes::Hard);

	}
	if (myCurrentTime > myMaxTime)
	{
		myHardActive = false;
		Deactivate(ePopUpTypes::Hard);
	}

	GameObject::Update(aDeltaTime);
}

bool PopUp::isEasyActive()
{
	return myEasyActive;
}

bool PopUp::isMediumActive()
{
	return myMediumActive;
}

bool PopUp::isHardActive()
{
	return myHardActive;
}

void PopUp::SetEasyActive(const bool aBool)
{
	myEasyActive = aBool;
}

void PopUp::SetMediumActive(const bool aBool)
{
	myMediumActive = aBool;
}

void PopUp::SetHardActive(const bool aBool)
{
	myHardActive = aBool;
}

void PopUp::Deactivate(ePopUpTypes aType)
{
	myBackground->SetActive(false);
	myCurrentTime = 0.0f;

	switch (aType)
	{
	case ePopUpTypes::Easy:
		myFireEasy->SetActive(false);
		break;
	case ePopUpTypes::Medium:
		myFireMedium->SetActive(false);
		break;
	case ePopUpTypes::Hard:
		myFireHard->SetActive(false);
		break;
	}
}

void PopUp::Activate(ePopUpTypes aType)
{
	myBackground->SetActive(true);
	switch (aType)
	{
	case ePopUpTypes::Easy:
		myFireEasy->SetActive(true);
		break;
	case ePopUpTypes::Medium:
		myFireMedium->SetActive(true);
		break;
	case ePopUpTypes::Hard:
		myFireHard->SetActive(true);
		break;
	}

}
