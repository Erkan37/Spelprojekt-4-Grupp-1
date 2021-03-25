#include "stdafx.h"
#include "Background.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include "LevelScene.h"
#include "Player.hpp"
#include "AudioManager.h"

#include "Game.h"


Background::Background(Scene* aLevelScene) 
	:
	GameObject(aLevelScene)
{
	SetZIndex(0);

	myOriginalSpeed = {};
	myBackgroundSpeedOneX = {};
	myBackgroundSpeedTwoX = {};
	myBackgroundSpeedThreeX = {};
	myBackgroundSpeedOneY = {};
	myBackgroundSpeedTwoY = {};
	myBackgroundSpeedThreeY = {};
	myAddedCameraPos = {};

	assert(&aLevelScene->GetCamera() != NULL);
	myCamera = &aLevelScene->GetCamera();
	LoadJson(aLevelScene);
	CreateBackgrounds(aLevelScene);
		
}

void Background::Init(int /*someLevelIndex*/)
{
}

void Background::Update(const float& /*aDeltaTime*/)
{
	UpdateBackground();
}

void Background::UpdateBackground()
{
	if (myCamera->GetActive() && myAddedCameraPos == false)
	{
		myStartingCameraPos = myCamera->GetPosition();
		myAddedCameraPos = true;
	}

	MoveBackground();
}

void Background::ResizeBackground()
{
	myCurrentRenderSize.x = Config::ourReferenceSize.x;
	myCurrentRenderSize.y = Config::ourReferenceSize.y;

	myBackground->SetPosition({ myCurrentRenderSize.x / 2, myCurrentRenderSize.y / 2 });
	myBackgroundSprite1->SetSize({ myCurrentRenderSize.x + 10, myCurrentRenderSize.y + 10 });
}

void Background::MoveBackground()
{
	v2f backgroundSpeedOne;
	backgroundSpeedOne = { (myStartingCameraPos.x - myCamera->GetPosition().x) * (myOriginalSpeed * myBackgroundSpeedOneX),
						   (myStartingCameraPos.y - myCamera->GetPosition().y) * (myOriginalSpeed * myBackgroundSpeedOneY) };

	myBackgroundSprite1->SetRelativePosition(myCamera->GetPosition() + backgroundSpeedOne);
}

void Background::LoadJson(Scene* /*aLevelScene*/)
{
	myBackgroundPath1 = "Sprites/Background.png";
	myBackgroundSpeedOneX = 0.f;
	myBackgroundSpeedOneY = 0.f;
	myOriginalSpeed = 0.2f;
}

void Background::CreateBackgrounds(Scene* aLevelScene)
{
	myBackground = std::make_unique<GameObject>(aLevelScene);
	
	myBackgroundSprite1 = myBackground->AddComponent<SpriteComponent>();
	myBackgroundSprite1->SetSpritePath(myBackgroundPath1);
	myBackgroundSprite1->SetSize(Config::ourReferenceSize);

	myBackground->Init();

	ResizeBackground();
}
