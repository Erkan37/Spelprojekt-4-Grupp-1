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

	SetPosition(platformPosition);
	SetPivot({ 0.0f, 1.0f });

	SpriteComponent* gsprite = AddComponent<SpriteComponent>();
	gsprite->SetSpritePath("Sprites/Temp/TempButton.dds");
	gsprite->SetSize(v2f(100.0f, 100.0f));

	PhysicsComponent* gphys = AddComponent<PhysicsComponent>();
	gphys->SetCanCollide(true);
	gphys->SetIsStatic(true);
	gphys->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this);

	GameObject::Init();
}

void Button::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);

	if (player != NULL && myHasCollided == false)
	{
		SpriteComponent* sprite = GetComponent<SpriteComponent>();
		sprite->SetSize({ sprite->GetSize().x, sprite->GetSize().y * 0.2f });
		myHasCollided = true;
	}
}

bool Button::GetActiveButton()
{
	return myButtonActive;
}
