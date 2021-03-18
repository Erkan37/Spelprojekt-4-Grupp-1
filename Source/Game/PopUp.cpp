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
	myFire = std::make_unique<UIObject>(myScene);
	v2f firePos = { 280.0f, 30.0f };

	myBackground->Init("Sprites/UI/popUp/UI_PopUp_84x32px.dds", { 84.0f, 32.0f }, backPos, 599);
	myFire->InitAnimation("Sprites/UI/pauseMenu/UI_Collectible_Soul_Green_16x16px.dds", { 16.0f, 16.0f }, firePos, 600);

}

void PopUp::Update(const float& aDeltaTime)
{
	//isEasyActive();
	if (myEasyActive == true)
	{
		myCurrentTime += aDeltaTime;
		myBackground->UpdateUIObjects(aDeltaTime);
		myFire->UpdateUIObjects(aDeltaTime);
		ActivateEasy();

	}
	if (myCurrentTime > myMaxTime)
	{
		myEasyActive = false;
		DeactivateEasy();
	}

	GameObject::Update(aDeltaTime);
}

bool PopUp::isEasyActive()
{
	return myEasyActive;
}

void PopUp::SetEasyActive(const bool aBool)
{
	myEasyActive = aBool;
}

void PopUp::ActivateEasy()
{
	myBackground->SetActive(true);
	myFire->SetActive(true);
}

void PopUp::DeactivateEasy()
{
	myBackground->SetActive(false);
	myFire->SetActive(false);
	myCurrentTime = 0.0f;
}
