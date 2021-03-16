#include "stdafx.h"
#include "UIButton.h"
#include "SpriteComponent.h"
#include "Player.hpp"
#include "LevelScene.h"


UIButton::UIButton(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
{
	myScene = aLevelScene;
}

void UIButton::Init(const std::string aPathString, const v2f aSize)
{
	SpriteComponent* sprite = AddComponent<SpriteComponent>();
	sprite->SetSpritePath(aPathString);
	sprite->SetSize(aSize);

	LevelScene* scene = dynamic_cast<LevelScene*>(myScene);
	myPlayer = dynamic_cast<Player*>(scene->GetPlayer());
}

void UIButton::Update(const float& aDeltaTime)
{
	SetPosition(myPlayer->GetPosition());
}
