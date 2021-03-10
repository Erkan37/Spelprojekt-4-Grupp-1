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

}

void Button::InitButton(v2f aButtonPosition)
{
	SpriteComponent* sprite = AddComponent<SpriteComponent>();
	sprite->SetRelativePosition(aButtonPosition);
	sprite->SetSpritePath("Sprites/Collectible.dds");
	sprite->SetSize(v2f(100.0f, 100.0f));


	SpriteComponent* sprite2 = AddComponent<SpriteComponent>();
	sprite2->SetRelativePosition(aButtonPosition);
	sprite2->SetSpritePath("Sprites/Collectible.dds");
	sprite2->SetSize(v2f(100.0f, 50.0f));

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(true);
	physics->SetIsStatic(true);
	physics->SetApplyGravity(false);
	physics->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this); //Get collision size from data manager

	myAnimations[0] = Animation(false, false, false, 0, 3, 3, 0.15f, sprite, 512, 512);
	myAnimations[1] = Animation(false, false, false, 0, 4, 4, 0.15f, sprite2, 512, 512);

	AnimationComponent* animation = AddComponent<AnimationComponent>();
	animation->SetSprite(sprite);
	animation->SetAnimation(&myAnimations[0]);

	GameObject::Init();
}

void Button::OnCollision(GameObject* myGameObject)
{
	GameObject* player = myGameObject;

	if (player != NULL)
	{
		GetComponent<AnimationComponent>()->SetAnimation(&myAnimations[1]);;
	}

}
