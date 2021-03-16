#include "stdafx.h"
#include "UIButton.h"
#include "SpriteComponent.h"
#include "Player.hpp"
#include "LevelScene.h"
#include "Camera.h"
#include <iostream>


UIButton::UIButton(Scene* aLevelScene)
	:
	GameObject(aLevelScene),
	myCamera(aLevelScene->GetCamera())
{
}

UIButton::~UIButton()
{
}

void UIButton::Init(const std::string aPathString, const v2f aSize, const v2f aPosition)
{
	myPosition = aPosition;

	SpriteComponent* sprite = AddComponent<SpriteComponent>();
	sprite->SetSpritePath(aPathString);
	sprite->SetSize(aSize);

	GameObject::Init();
}

void UIButton::Update(const float& aDeltaTime)
{
	SetPosition(myCamera.GetPosition() + myPosition);
}
