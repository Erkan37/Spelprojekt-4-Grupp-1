#include "stdafx.h"
#include "Background.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include "LevelScene.h"
#include "Player.hpp"
#include "AudioManager.h"

Background::Background(Scene* aLevelScene) 
	:
	GameObject(aLevelScene)
{
	SetZIndex(0);

	myOrignalSpeed = {};
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

	int renderSizeX = Tga2D::CEngine::GetInstance()->GetRenderSize().x;
	int renderSizeY = Tga2D::CEngine::GetInstance()->GetRenderSize().y;

	if (myCurrentRenderSize.x != renderSizeX || myCurrentRenderSize.y != renderSizeY)
	{
		ResizeBackground();
	}

	MoveBackground();
}

void Background::ResizeBackground()
{
	//int renderSizeX = Tga2D::CEngine::GetInstance()->GetRenderSize().x;
	//int renderSizeY = Tga2D::CEngine::GetInstance()->GetRenderSize().y;

	int targetSizeX = 640;
	int targetSizeY = 360;

	myCurrentRenderSize.x = static_cast<float>(targetSizeX);
	myCurrentRenderSize.y = static_cast<float>(targetSizeY);

	myBackground->SetPosition({ myCurrentRenderSize.x / 2, myCurrentRenderSize.y / 2 });
	myBackgroundSprite1->SetSize({ myCurrentRenderSize.x + 10, myCurrentRenderSize.y + 10 });
}

void Background::MoveBackground()
{
	v2f backgroundSpeedOne;
	backgroundSpeedOne = { (myStartingCameraPos.x - myCamera->GetPosition().x) * (myOrignalSpeed * myBackgroundSpeedOneX),
						   (myStartingCameraPos.y - myCamera->GetPosition().y) * (myOrignalSpeed * myBackgroundSpeedOneY) };

	myBackgroundSprite1->SetRelativePosition(myCamera->GetPosition() + backgroundSpeedOne);
}

void Background::LoadJson(Scene* /*aLevelScene*/)
{
	myBackgroundPath1 = "Sprites/Background.png";
	myBackgroundSpeedOneX = 0.f;
	myBackgroundSpeedOneY = 0.f;
	myOrignalSpeed = 0.2f;
}

void Background::CreateBackgrounds(Scene* aLevelScene)
{
	myBackground = std::make_unique<GameObject>(aLevelScene);
	
	myBackgroundSprite1 = myBackground->AddComponent<SpriteComponent>();
	myBackgroundSprite1->SetSpritePath(myBackgroundPath1);

	myBackground->Init();

	ResizeBackground();
}
