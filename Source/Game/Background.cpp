#include "stdafx.h"
#include "Background.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include "LevelScene.h"
#include "Player.hpp"

Background::Background(LevelScene* aLevelScene) 
	:
	GameObject(aLevelScene)
{
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
	myPlayerStartingPosition = myPlayer->GetPosition();
}

void Background::UpdateBackground()
{
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
	backgroundSpeedOne = { (myPlayerStartingPosition.x - myPlayer->GetPosition().x) * myBackgroundSpeedOneX, 
						   (myPlayerStartingPosition.y - myPlayer->GetPosition().y) * myBackgroundSpeedOneY };

	v2f backgroundSpeedTwo;
	backgroundSpeedTwo = { (myPlayerStartingPosition.x - myPlayer->GetPosition().x) * myBackgroundSpeedTwoX, 
						   (myPlayerStartingPosition.y - myPlayer->GetPosition().y) * myBackgroundSpeedTwoY };

	v2f backgroundSpeedThree;
	backgroundSpeedThree = { (myPlayerStartingPosition.x - myPlayer->GetPosition().x) * myBackgroundSpeedThreeX, 
							 (myPlayerStartingPosition.y - myPlayer->GetPosition().y) * myBackgroundSpeedThreeY };

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
	myBackgroundSpeedTwoX = 0.02f;
	myBackgroundSpeedThreeX = 0.06f;
	myBackgroundSpeedOneY = 0.f;
	myBackgroundSpeedTwoY = 0.f;
	myBackgroundSpeedThreeY = 0.f;
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
}
