#include "stdafx.h"
#include "../External/Headers/CU/Utilities.h"
#include "GameWorld.h"

#include "LevelScene.h"

#include "Player.hpp"

#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"

Player::Player(LevelScene* aLevelScene)
	:
	GameObject(aLevelScene)
{
	SetPosition({ 960.0f, 540.0f });

	SpriteComponent* sprite = AddComponent<SpriteComponent>();
	sprite->SetSpritePath("Sprites/Tommy.dds");
	sprite->SetSize({ 70.0f, 70.0f });
	sprite->SetZIndex(500);

	AnimationComponent* animation = AddComponent<AnimationComponent>();
	animation->SetSprite(sprite);
	animation->SetAnimation(&Animation(false, false, false, 0, 8, 8, 0.15f, "Sprites/TommyAnim.dds", 512, 512));
	sprite->SetSize({ 70.0f, 70.0f });

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(true);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(true);

	physics->CreateColliderFromSprite(sprite, this);

	CGameWorld* world = CGameWorld::GetInstance();
	myInputHandler = world->Input();

	myMaxSpeed = 400.0f;

	myAcceleration = 4.0f;
	myRetardation = 20.0f;

	myHasLanded = true;
	myHasDoubleJumped = false;

	myJumpVelocity = 450.0f;
	myDoubleJumpVelocity = 300.0f;
}

Player::~Player()
{

}

void Player::Update(const float& aDeltaTime)
{
	PhysicsComponent* physics = GetComponent<PhysicsComponent>();

	if (physics)
	{
		CheckMove(aDeltaTime);
		CheckJump(aDeltaTime);
	}

	GameObject::Update(aDeltaTime);
}

void Player::CheckJump(const float& aDeltaTime)
{
	if (myInputHandler->GetKeyJustDown(Keys::WKey))
	{
		if (myHasLanded && GetComponent<PhysicsComponent>()->GetVelocityY() == 0.0f)
		{
			GetComponent<PhysicsComponent>()->SetVelocityY(-myJumpVelocity);
			myHasLanded = false;
		}
		else if (!myHasDoubleJumped)
		{
			GetComponent<PhysicsComponent>()->SetVelocityY(Utils::Min(GetComponent<PhysicsComponent>()->GetVelocityY() - myDoubleJumpVelocity, -myDoubleJumpVelocity));
			myHasDoubleJumped = true;
		}
	}
}

void Player::CheckMove(const float& aDeltaTime)
{
	PhysicsComponent* physics = GetComponent<PhysicsComponent>();
	if (myInputHandler->GetKeyDown(Keys::DKey))
	{
		GetComponent<PhysicsComponent>()->SetVelocityX(Utils::Lerp(physics->GetVelocityX(), myMaxSpeed, myAcceleration * aDeltaTime));
	}
	else if (myInputHandler->GetKeyDown(Keys::AKey))
	{
		GetComponent<PhysicsComponent>()->SetVelocityX(Utils::Lerp(physics->GetVelocityX(), -myMaxSpeed, myAcceleration * aDeltaTime));
	}
	else
	{
		GetComponent<PhysicsComponent>()->SetVelocityX(Utils::Lerp(physics->GetVelocityX(), 0.0f, myRetardation * aDeltaTime));
	}
}

void Player::Landed()
{
	myHasLanded = true;
	myHasDoubleJumped = false;
}