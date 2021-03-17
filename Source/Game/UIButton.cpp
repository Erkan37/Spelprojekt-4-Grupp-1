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
	myBtnHighlighted = {};
	myIsActive = {};
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

	myOriginalColor = sprite->GetColor();
	myHighlightedColor = myOriginalColor;
	myHighlightedColor.w = 0.5f;

	SetPivot({0.f, 0.f});

	GameObject::Init();
}

void UIButton::Update(const float& aDeltaTime)
{
	SetPosition(myCamera.GetPosition() + myPosition);

	if (myBtnHighlighted)
		SetLightedColor(myHighlightedColor);
	else
		SetLightedColor(myOriginalColor);
}

void UIButton::Render()
{
	if (myIsActive)
		GameObject::Render();
}

void UIButton::SetIsHighlightActive(const bool aHighlightBool)
{
	myBtnHighlighted = aHighlightBool;
}

void UIButton::SetLightedColor(const v4f aColor)
{
	GetComponent<SpriteComponent>()->SetColor(aColor);
}

void UIButton::SetActive(const bool aActiveState)
{
	myIsActive = aActiveState;
}
