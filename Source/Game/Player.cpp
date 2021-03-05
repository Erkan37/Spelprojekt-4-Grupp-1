#include "stdafx.h"
#include "../External/Headers/CU/Utilities.h"
#include "GameWorld.h"
#include "InputWrapper.h"
#include "Controller.h"

#include "LevelScene.h"

#include "Player.hpp"

#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"

#include "imgui.h"

Player::Player(LevelScene* aLevelScene)
	:
	GameObject(aLevelScene)
{
	SetPosition({ 960.0f, 540.0f });

	InitAnimations();

	InitCollider();

	CGameWorld* world = CGameWorld::GetInstance();
	myInputHandler = world->Input();

	myMaxSpeed = 400.0f;

	myAcceleration = 4.0f;
	myRetardation = 20.0f;

	myHasLanded = true;
	myHasDoubleJumped = false;

	myAirCoyoteTime = 0.2f;
	myAirCoyoteTimer = 0.2f;

	myJumpVelocity = 450.0f;
	myDoubleJumpVelocity = 300.0f;

	myCurrentAnimationIndex = 0;

	myBashAbility = std::make_unique<BashAbility>(aLevelScene);
	myBashAbility->AddPlayerPhysics(std::shared_ptr<PhysicsComponent>(GetComponent<PhysicsComponent>()));
	myBashAbility->AddInputWrapper(myInputHandler);
	myBashAbility->AddTimer(world->GetTimer());
}

void Player::InitAnimations()
{
	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/TommyIdle.dds");
	spriteIdle->SetSize({ 70.0f, 70.0f });
	spriteIdle->SetZIndex(500);

	SpriteComponent* spriteRun = AddComponent<SpriteComponent>();
	spriteRun->SetSpritePath("Sprites/TommyRun.dds");
	spriteRun->SetSize({ 70.0f, 70.0f });
	spriteRun->SetZIndex(500);
	spriteRun->Deactivate();

	SpriteComponent* spriteJump = AddComponent<SpriteComponent>();
	spriteJump->SetSpritePath("Sprites/TommyJump.dds");
	spriteJump->SetSize({ 70.0f, 70.0f });
	spriteJump->SetZIndex(500);
	spriteJump->Deactivate();

	myAnimations[0] = Animation(false, false, true, 0, 3, 3, 0.15f, spriteIdle, 512, 512);
	myAnimations[1] = Animation(false, false, false, 0, 4, 4, 0.15f, spriteRun, 512, 512);
	myAnimations[2] = Animation(false, true, false, 0, 3, 3, 0.15f, spriteJump, 512, 512);

	AnimationComponent* animation = AddComponent<AnimationComponent>();
	animation->SetSprite(spriteIdle);
	animation->SetAnimation(&myAnimations[0]);
	spriteIdle->SetSize({ 70.0f, 70.0f });
}

void Player::InitCollider()
{
	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(true);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(true);

	physics->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this);
}

Player::~Player()
{

}

void Player::Update(const float& aDeltaTime)
{
	myBashAbility->Update(aDeltaTime);

	PhysicsComponent* physics = GetComponent<PhysicsComponent>();

	if (physics)
	{
		CheckMove(aDeltaTime);
		CheckJump();
		UpdateCoyoteTime(aDeltaTime);
	}

	AnimationState();

	GameObject::Update(aDeltaTime);
}

void Player::CheckJump()
{
	if (myInputHandler->IsJumping())
	{
		if (myHasLanded && (GetComponent<PhysicsComponent>()->GetVelocityY() == 0.0f || myAirCoyoteTimer > 0))
		{
			GetComponent<PhysicsComponent>()->SetVelocityY(-myJumpVelocity);
			GetComponent<AnimationComponent>()->SetAnimation(&myAnimations[2]);
			myCurrentAnimationIndex = 2;
			myHasLanded = false;
		}
		else if (!myHasDoubleJumped)
		{
			GetComponent<PhysicsComponent>()->SetVelocityY(Utils::Min(GetComponent<PhysicsComponent>()->GetVelocityY() - myDoubleJumpVelocity, -myDoubleJumpVelocity));
			GetComponent<AnimationComponent>()->SetAnimation(&myAnimations[2]);
			myCurrentAnimationIndex = 2;
			myHasDoubleJumped = true;
		}
	}
}

void Player::UpdateCoyoteTime(const float& aDeltaTime)
{
	if (GetComponent<PhysicsComponent>()->GetVelocityY() > 0)
	{
		myAirCoyoteTimer -= aDeltaTime;
	}
}

void Player::CheckMove(const float& aDeltaTime)
{
	PhysicsComponent* physics = GetComponent<PhysicsComponent>();

	if (myInputHandler->IsMovingRight())
	{
		GetComponent<PhysicsComponent>()->SetVelocityX(Utils::Lerp(physics->GetVelocityX(), myMaxSpeed, myAcceleration * aDeltaTime));
		myAnimations[myCurrentAnimationIndex].mySpriteComponent->SetSizeX(70.0f);
	}
	else if (myInputHandler->IsMovingLeft())
	{
		GetComponent<PhysicsComponent>()->SetVelocityX(Utils::Lerp(physics->GetVelocityX(), -myMaxSpeed, myAcceleration * aDeltaTime));
		myAnimations[myCurrentAnimationIndex].mySpriteComponent->SetSizeX(-70.0f);
	}
	else
	{
		GetComponent<PhysicsComponent>()->SetVelocityX(Utils::Lerp(physics->GetVelocityX(), 0.0f, myRetardation * aDeltaTime));
	}
}

void Player::Landed(const int& aOverlapY)
{
	if (aOverlapY < 0)
	{
		myAirCoyoteTimer = myAirCoyoteTime;
		myHasLanded = true;
		myHasDoubleJumped = false;
	}
}

void Player::AnimationState()
{
	AnimationComponent* animation = GetComponent<AnimationComponent>();
	if (Utils::Abs(GetComponent<PhysicsComponent>()->GetVelocityX()) <= 50.0f && myHasLanded && myCurrentAnimationIndex != 0)
	{
		animation->SetAnimation(&myAnimations[0]);
		myCurrentAnimationIndex = 0;
	}
	else if (Utils::Abs(GetComponent<PhysicsComponent>()->GetVelocityX()) > 50.0f && myHasLanded && myCurrentAnimationIndex != 1)
	{
		animation->SetAnimation(&myAnimations[1]);
		myCurrentAnimationIndex = 1;
	}
}