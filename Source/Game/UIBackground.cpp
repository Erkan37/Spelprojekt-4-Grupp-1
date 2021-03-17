#include "stdafx.h"
#include "UIBackground.h"
#include "LevelScene.h"
#include "SpriteComponent.h"


UIBackground::UIBackground(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
{
	myCamera = &aLevelScene->GetCamera();
	myPosition = {};
}

void UIBackground::Init(const std::string aPathString, const v2f aSize, const v2f aPosition)
{
	SetPivot({0.f, 0.f});
	myPosition = aPosition;
	
	SpriteComponent* sprite = AddComponent<SpriteComponent>();
	sprite->SetSpritePath(aPathString);
	sprite->SetSize(aSize);

	GameObject::Init();
}

void UIBackground::Update(const float& aDeltaTime)
{
	SetPosition(myCamera->GetPosition() + myPosition);
}
