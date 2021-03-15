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
		myButtonActive = true;
	}
}

void Button::InitButton(const v2f myStartingPosition, const v2f myPositionFromStart)
{
	v2f platformPosition = myStartingPosition + myPositionFromStart;
	mySize = { 32.f, 32.f };

	SetPosition(platformPosition);
	SetPivot({ 0.5f, 1.f });

	SpriteComponent* gsprite = AddComponent<SpriteComponent>();
	gsprite->SetSpritePath("Sprites/TempButton.dds");
	gsprite->SetSize(mySize);

	PhysicsComponent* gphys = AddComponent<PhysicsComponent>();
	gphys->SetCanCollide(true);
	gphys->SetIsStatic(true);

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetSize(mySize);
	collider->SetPosition({ mySize.x * 0.5f, -mySize.y * 0.5f });
	
	GameObject::Init();
}

void Button::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);

	if (player != NULL && myHasCollided == false)
	{
		v2f playerPos = player->GetPosition();
		v2f velo = player->GetComponent<PhysicsComponent>()->GetVelocity();
		v2f colliderPos = GetPosition();
		v2f buttonSize = GetComponent<SpriteComponent>()->GetSize();

		float spriteLeftPosX = (colliderPos.x + GetComponent<ColliderComponent>()->GetSize().x / 2.f) - buttonSize.x / 2.f;
		float spriteRightPosX = (colliderPos.x + GetComponent<ColliderComponent>()->GetSize().x / 2.f) + buttonSize.x / 2.f;

		if (velo.y > 50 && playerPos.x >= spriteLeftPosX + 2.f && playerPos.x <= spriteRightPosX - 2.f)
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
