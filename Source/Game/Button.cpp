#include "stdafx.h"
#include "Button.h"
#include "LevelScene.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "AnimationComponent.hpp"
#include "Player.hpp"
#include "Camera.h"



Button::Button(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
{
	myHasCollided = {};
	myButtonActive = {};
	mySize = {};

	SetZIndex(95);
}

Button::~Button()
{
}

void Button::Init(const v2f myStartingPosition, const v2f myPositionFromStart)
{
	InitButton(myStartingPosition, myPositionFromStart);
}

void Button::Update(const float& aDeltaTime)
{
	GameObject::Update(aDeltaTime);

	if (myHasCollided && myButtonActive == false)
	{
		GetComponent<ColliderComponent>()->SetSize({ 0.f,0.f });
		myButtonActive = true;
	}
}

void Button::InitButton(const v2f myStartingPosition, const v2f myPositionFromStart)
{
	v2f platformPosition = myPositionFromStart;
	mySize = { 8.f, 16.f };

	SetPosition(platformPosition);
	SetPivot({ 0.f, 1.f });

	SpriteComponent* gsprite = AddComponent<SpriteComponent>();
	gsprite->SetSpritePath("Sprites/Objects/Button.dds");
	gsprite->SetSize(mySize);

	PhysicsComponent* gphys = AddComponent<PhysicsComponent>();
	gphys->SetCanCollide(true);
	gphys->SetIsStatic(true);

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetSize({mySize.x, mySize.y * 0.05f});
	collider->SetPosition({ mySize.x * 0.5f, -mySize.y * 0.1f });

	GameObject::Init();
}

void Button::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);

	if (player != NULL)
	{
		v2f velo = player->GetComponent<PhysicsComponent>()->GetVelocity();

		if (myHasCollided == false)
		{
			SpriteComponent* sprite = GetComponent<SpriteComponent>();
			v2f smashedSize = { sprite->GetSize().x, sprite->GetSize().y * 0.2f };
			sprite->SetSize(smashedSize);
			myHasCollided = true;
		}
	}

}

bool Button::GetActiveButton()
{
	return myButtonActive;
}
