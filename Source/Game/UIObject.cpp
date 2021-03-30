#include "stdafx.h"
#include "UIObject.h"
#include "LevelScene.h"
#include "SpriteComponent.h"
#include "AnimationComponent.hpp"


UIObject::UIObject(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
{
	myCamera = &aLevelScene->GetCamera();
	//myPosition = {};
	myIsActive = {};
}

void UIObject::Init(const std::string aPathString, const v2f aSize, const v2f aPosition, int aZIndex)
{
	SetZIndex(aZIndex);
	SetPivot({0.f, 0.f});
	myTransform.myPosition = aPosition;
	
	SpriteComponent* sprite = AddComponent<SpriteComponent>();
	sprite->SetSpritePath(aPathString);
	sprite->SetSize(aSize);

	GameObject::Init();
}

void UIObject::InitAnimation(const std::string aPathString, const v2f aSize, const v2f aPosition, int aZIndex)
{
	SetZIndex(aZIndex);
	SetPivot({ 0.5f, 0.5f });
	myTransform.myPosition = aPosition;

	SpriteComponent* sprite = AddComponent<SpriteComponent>();
	sprite->SetSpritePath(aPathString);
	sprite->SetSize(aSize);
	AnimationComponent* animation = AddComponent<AnimationComponent>();
	animation->SetSprite(sprite);
	Animation idleAnimation = Animation(false, false, false, 0, 8, 8, 0.10f, sprite, 16, 16);
	animation->SetAnimation(&idleAnimation);

	GameObject::Init();
}

void UIObject::UpdateUIObjects(const float& aDeltaTime)
{
	
	SetPosition(myCamera->GetPosition() + myTransform.myPosition);

	GameObject::Update(aDeltaTime);
}

void UIObject::Render()
{
	if (myIsActive)
		GameObject::Render();
}

void UIObject::SetActive(const bool aActiveState)
{
	myIsActive = aActiveState;
}
