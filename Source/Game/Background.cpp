#include "stdafx.h"
#include "Background.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include "LevelScene.h"
#include "Player.hpp"
#include "AudioManager.h"

Background::Background(LevelScene* aLevelScene) 
	:
	GameObject(aLevelScene)
{
	myOrignalSpeed = {};
	myBackgroundSpeedOneX = {};
	myBackgroundSpeedTwoX = {};
	myBackgroundSpeedThreeX = {};
	myBackgroundSpeedOneY = {};
	myBackgroundSpeedTwoY = {};
	myBackgroundSpeedThreeY = {};
	myAddedCameraPos = {};
	myCamera = &aLevelScene->GetCamera();
	LoadJson(aLevelScene);
	CreateBackgrounds(aLevelScene);
}

void Background::Init(int someLevelIndex)
{
}

void Background::Update(const float& aDeltaTime)
{
	UpdateBackground();
}

void Background::AddPlayerRelation(GameObject* aPlayer)
{
	myPlayer = aPlayer;
}

void Background::UpdateBackground()
{
	if (myCamera->GetActive() && myAddedCameraPos == false)
	{
		myStartingCameraPos = myCamera->GetPosition();
		myAddedCameraPos = true;
	}

	float renderSizeX = Tga2D::CEngine::GetInstance()->GetRenderSize().x;
	float renderSizeY = Tga2D::CEngine::GetInstance()->GetRenderSize().y;

	if (myCurrentRenderSize.x != renderSizeX || myCurrentRenderSize.y != renderSizeY)
	{
		ResizeBackground();
	}

	MoveBackground();
}

void Background::ResizeBackground()
{
	float renderSizeX = Tga2D::CEngine::GetInstance()->GetRenderSize().x;
	float renderSizeY = Tga2D::CEngine::GetInstance()->GetRenderSize().y;

	myCurrentRenderSize.x = renderSizeX;
	myCurrentRenderSize.y = renderSizeY;

	myBackground->SetPosition({ myCurrentRenderSize.x / 2, myCurrentRenderSize.y / 2 });
	myBackgroundSprite1->SetSize({ myCurrentRenderSize.x + 10, myCurrentRenderSize.y + 10 });
	myBackgroundSprite2->SetSize({ myCurrentRenderSize.x + 10, myCurrentRenderSize.y + 10 });
	myBackgroundSprite3->SetSize({ myCurrentRenderSize.x + 10, myCurrentRenderSize.y + 10 });
}

void Background::MoveBackground()
{
	v2f backgroundSpeedOne;
	backgroundSpeedOne = { (myStartingCameraPos.x - myCamera->GetPosition().x) * (myOrignalSpeed * myBackgroundSpeedOneX),
						   (myStartingCameraPos.y - myCamera->GetPosition().y) * (myOrignalSpeed * myBackgroundSpeedOneY) };

	v2f backgroundSpeedTwo;
	backgroundSpeedTwo = { (myStartingCameraPos.x - myCamera->GetPosition().x) * (myOrignalSpeed * myBackgroundSpeedTwoX),
						   (myStartingCameraPos.y - myCamera->GetPosition().y) * (myOrignalSpeed * myBackgroundSpeedTwoY) };

	v2f backgroundSpeedThree;
	backgroundSpeedThree = { (myStartingCameraPos.x - myCamera->GetPosition().x) * (myOrignalSpeed * myBackgroundSpeedThreeX),
							 (myStartingCameraPos.y - myCamera->GetPosition().y) * (myOrignalSpeed * myBackgroundSpeedThreeY) };

	myBackgroundSprite1->SetRelativePosition(myCamera->GetPosition() + backgroundSpeedOne);
	myBackgroundSprite2->SetRelativePosition(myCamera->GetPosition() + backgroundSpeedTwo);
	myBackgroundSprite3->SetRelativePosition(myCamera->GetPosition() + backgroundSpeedThree);
}

void Background::LoadJson(LevelScene* aLevelScene)
{
	myBackgroundPath1 = "Sprites/Background.png";
	myBackgroundPath2 = "Sprites/tga_logo.dds";
	myBackgroundPath3 = "Sprites/Tommy.dds";
	myBackgroundSpeedOneX = 0.f;
	myBackgroundSpeedTwoX = 0.05f;
	myBackgroundSpeedThreeX = 0.3f;
	myBackgroundSpeedOneY = 0.f;
	myBackgroundSpeedTwoY = 0.f;
	myBackgroundSpeedThreeY = 0.f;
	myOrignalSpeed = 0.2f;
}

void Background::CreateBackgrounds(LevelScene* aLevelScene)
{
	myBackground = std::make_unique<GameObject>(aLevelScene);
	
	myBackgroundSprite1 = myBackground->AddComponent<SpriteComponent>();
	myBackgroundSprite1->SetSpritePath(myBackgroundPath1);

	myBackgroundSprite2 = myBackground->AddComponent<SpriteComponent>();
	myBackgroundSprite2->SetSpritePath(myBackgroundPath2);

	myBackgroundSprite3 = myBackground->AddComponent<SpriteComponent>();
	myBackgroundSprite3->SetSpritePath(myBackgroundPath3);

	ResizeBackground();

	AudioManager::GetInstance()->Play("lonely.mp3");
	AudioManager::GetInstance()->Play("dead.mp3");
}
