#include "stdafx.h"
#include "Button.h"
#include "LevelScene.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "AnimationComponent.hpp"
#include "Camera.h"



Button::Button(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
{
	myHasCollided = {};
	myButtonActive = {};
	InitButton(aLevelScene->GetCamera().GetPosition());
}

Button::~Button()
{
}

void Button::Init()
{
}

void Button::Update(const float& aDeltaTime)
{
	GameObject::Update(aDeltaTime);
	
	if (myHasCollided && myButtonActive == false)
	{
		myButtonActive = true;
		GetComponent<AnimationComponent>()->ContinueToNextAnimation();
	}
}

void Button::InitButton(v2f aButtonPosition)
{
	SpriteComponent* sprite = AddComponent<SpriteComponent>();
	sprite->SetRelativePosition(aButtonPosition);
	sprite->SetSpritePath("Sprites/Collectible.dds");
	sprite->SetSize(v2f(100.0f, 100.0f));


	SpriteComponent* sprite2 = AddComponent<SpriteComponent>();
	sprite2->SetRelativePosition(aButtonPosition);
	sprite2->SetSpritePath("Sprites/TommyIdle.dds");
	sprite2->SetSize(v2f(100.0f, 50.0f));

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(true);
	physics->SetIsStatic(true);
	physics->SetApplyGravity(false);
	physics->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this); //Get collision size from data manager

	myAnimation[0] = Animation(false, false, true, 0, 1, 1, 1.f, sprite, 512, 512);
	myAnimation[1] = Animation(false, false, true, 0, 3, 3, 1.f, sprite2, 512, 512);

	AnimationComponent* animation = AddComponent<AnimationComponent>();
	animation->SetSprite(sprite);
	animation->SetAnimation(&myAnimation[0]);

	animation->SetNextAnimation(&myAnimation[1]);

	GameObject::Init();
}

void Button::OnCollision(GameObject* myGameObject)
{
	GameObject* player = myGameObject;

	if (player != NULL)
	{
		myHasCollided = true;
	}
}

bool Button::GetActiveButton()
{
	return myButtonActive;
}
