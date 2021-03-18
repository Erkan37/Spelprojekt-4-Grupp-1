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
}

void PopUp::InitPopUp()
{
	v2f referenceSize = Config::ourReferenceSize;

	myFiree = std::make_unique<UIObject>(myScene);
	v2f firePos = { 35.0f, 20.0f };

	myFiree->InitAnimation("Sprites/UI/pauseMenu/UI_Collectible_Soul_Red_16x16px.dds", { 16.0f, 16.0f }, firePos, 600);

}

void PopUp::Update(const float& aDeltaTime)
{
	//isEasyActive();

	if (myEasyActive == true)
	{
		myFiree->UpdateUIObjects(aDeltaTime);
		ActivateEasy();
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
	myFiree->SetActive(true);
}

void PopUp::DeactivateEasy()
{
}
