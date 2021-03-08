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
#include "ColliderComponent.h"

#include "Ledge.h"

#include "imgui.h"

Player::Player(LevelScene* aLevelScene)
	:
	GameObject(aLevelScene)
{
	SetZIndex(500);
	SetPosition({ 960.0f, 540.0f });

	InitAnimations();

	InitCollider();

	CGameWorld* world = CGameWorld::GetInstance();
	myInputHandler = world->Input();

	myMaxRunningSpeed = 400.0f;

	myAcceleration = 6.0f;
	myRetardation = 20.0f;
	myLerpToPositionAcceleration = 6.0f;

	myAirCoyoteTime = 0.1f;
	myAirCoyoteTimer = myAirCoyoteTime;

	myJumpVelocity = 600.0f;
	myDoubleJumpVelocity = 600.0f;

	myJumpWhenFallingTime = 0.075f;

	myCurrentAnimationIndex = 0;

	myHasLanded = true;
	myHasDoubleJumped = false;

	myCanJumpWhenFalling = false;
	myWillJumpWhenFalling = false;

	myGrabbedLedge = false;

	myIsLerpingToPosition = false;

	myBashAbility = std::make_unique<BashAbility>(aLevelScene);
	myBashAbility->Init();
	myBashAbility->AddInputWrapper(world->Input());
	myBashAbility->AddPlayerRelation(this);
	myBashAbility->AddTimer(world->GetTimer());
}

void Player::InitAnimations()
{
	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/TommyIdle.dds");
	spriteIdle->SetSize({ 70.0f, 70.0f });

	SpriteComponent* spriteRun = AddComponent<SpriteComponent>();
	spriteRun->SetSpritePath("Sprites/TommyRun.dds");
	spriteRun->SetSize({ 70.0f, 70.0f });
	spriteRun->Deactivate();

	SpriteComponent* spriteJump = AddComponent<SpriteComponent>();
	spriteJump->SetSpritePath("Sprites/TommyJump.dds");
	spriteJump->SetSize({ 70.0f, 70.0f });
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
	physics->SetApplyGravity(false);

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
		if (!myBashAbility->GetIsBashing())
		{
			CheckMove(aDeltaTime);
			CheckJump();
			UpdateCoyoteTime(aDeltaTime);
		}

		UpdatePlayerVelocity(aDeltaTime);

		if (myIsLerpingToPosition)
		{
			LerpToPosition(myLerpPosition, aDeltaTime);
		}
	}

	AnimationState();
	GameObject::Update(aDeltaTime);


#ifdef _DEBUG
	ImGuiUpdate();
#endif //DEBUG
}

void Player::CheckJump()
{
	if (myInputHandler->IsJumping())
	{
		if (myGrabbedLedge)
		{
			LedgeJump();
		}
		else
		{
			if (myCanJumpWhenFalling && !myHasLanded && GetComponent<PhysicsComponent>()->GetVelocityY() >= 0.0f)
			{
				myWillJumpWhenFalling = true;
			}

			if (myHasLanded && (GetComponent<PhysicsComponent>()->GetVelocityY() == 0.0f || myAirCoyoteTimer > 0))
			{
				Jump();
			}
			else if (!myHasDoubleJumped)
			{
				DoubleJump();
			}
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

void Player::TryLetJumpWhenFalling(const float& aYDistance)
{
	const float distancePerJumpWhenLandingTime = GetComponent<PhysicsComponent>()->GetVelocityY() * myJumpWhenFallingTime;
	if (aYDistance < distancePerJumpWhenLandingTime && aYDistance > 0)
	{
		myCanJumpWhenFalling = true;		
	}
	else
	{
		myCanJumpWhenFalling = false;
	}
}

void Player::CheckMove(const float& aDeltaTime)
{
	if (myGrabbedLedge)
	{
		return;
	}

	PhysicsComponent* physics = GetComponent<PhysicsComponent>();

	if (myInputHandler->IsMovingRight())
	{
		GoRight(aDeltaTime);
	}
	else if (myInputHandler->IsMovingLeft())
	{
		GoLeft(aDeltaTime);
	}
	else
	{
		myCurrentVelocity.x = Utils::Lerp(myCurrentVelocity.x, 0.0f, myRetardation * aDeltaTime);
	}
}

void Player::GoRight(const float& aDeltaTime)
{
	if (myCurrentVelocity.x < 0)
	{
		myCurrentVelocity.x = 0.0f;
	}

	if (myBashAbility->GetVelocity().x < 0)
	{
		myBashAbility->ResetVelocity(true, false);
	}

	myCurrentVelocity.x = Utils::Lerp(myCurrentVelocity.x, myMaxRunningSpeed, myAcceleration * aDeltaTime);
	myAnimations[myCurrentAnimationIndex].mySpriteComponent->SetSizeX(70.0f);
}

void Player::GoLeft(const float& aDeltaTime)
{
	if (myCurrentVelocity.x > 0)
	{
		myCurrentVelocity.x = 0.0f;
	}

	if (myBashAbility->GetVelocity().x > 0)
	{
		myBashAbility->ResetVelocity(true, false);
	}

	myCurrentVelocity.x = Utils::Lerp(myCurrentVelocity.x, -myMaxRunningSpeed, myAcceleration * aDeltaTime);
	myAnimations[myCurrentAnimationIndex].mySpriteComponent->SetSizeX(-70.0f);
}

void Player::Jump()
{
	myCurrentVelocity.y = -myJumpVelocity;
	GetComponent<AnimationComponent>()->SetAnimation(&myAnimations[2]);
	myCurrentAnimationIndex = 2;
	myHasLanded = false;
	myWillJumpWhenFalling = false;
	myBashAbility->ResetVelocity(false, true);
}

void Player::DoubleJump()
{
	myCurrentVelocity.y = -myDoubleJumpVelocity;
	GetComponent<AnimationComponent>()->SetAnimation(&myAnimations[2]);
	myCurrentAnimationIndex = 2;
	myHasDoubleJumped = true;
	myWillJumpWhenFalling = false;
	myBashAbility->ResetVelocity(false, true);
}

void Player::LedgeJump()
{
	myGrabbedLedge = false;

	if (!myInputHandler->GetInput()->GetKeyDown(Keys::SKey) && myInputHandler->GetController()->GetLeftThumbStick().y < 0.3f)
	{
		myCurrentVelocity.y = -myDoubleJumpVelocity * 0.6f;
	}
	
	myIsLerpingToPosition = false;

	GetComponent<AnimationComponent>()->SetAnimation(&myAnimations[2]);
	myCurrentAnimationIndex = 2;
	myHasDoubleJumped = false;
	myWillJumpWhenFalling = false;
	myBashAbility->ResetVelocity(false, true);
}

void Player::ReactivateDoubleJump()
{
	myHasDoubleJumped = false;
}

void Player::Landed(const int& aOverlapY)
{
	if (aOverlapY > 0)
	{
		myAirCoyoteTimer = myAirCoyoteTime;
		myHasLanded = true;
		myHasDoubleJumped = false;

		myBashAbility->ResetVelocity(true, true);

		if (myWillJumpWhenFalling)
		{
			Jump();
		}
	}

	myCurrentVelocity.y = 0.0f;
	myBashAbility->ResetVelocity(false, true);
}

void Player::SideCollision(const int& aOverlapX)
{
	myCurrentVelocity.x = 0.0f;
	myBashAbility->ResetVelocity(true, false);
}

void Player::ResetVelocity()
{
	myCurrentVelocity.x = 0;
	myCurrentVelocity.y = 0;
}

void Player::AnimationState()
{
	AnimationComponent* animation = GetComponent<AnimationComponent>();
	if (Utils::Abs(myCurrentVelocity.x) <= 50.0f && myHasLanded && myCurrentAnimationIndex != 0)
	{
		animation->SetAnimation(&myAnimations[0]);
		myCurrentAnimationIndex = 0;
	}
	else if (Utils::Abs(myCurrentVelocity.x) > 50.0f && myHasLanded && myCurrentAnimationIndex != 1)
	{
		animation->SetAnimation(&myAnimations[1]);
		myCurrentAnimationIndex = 1;
	}
}

void Player::UpdatePlayerVelocity(const float& aDeltaTime)
{
	if (!myGrabbedLedge)
	{
		myCurrentVelocity.y += PhysicsManager::ourGravity * aDeltaTime;
	}
	
	PhysicsComponent* physics = GetComponent<PhysicsComponent>();
	physics->SetVelocity(myCurrentVelocity + myBashAbility->GetVelocity());
}

void Player::GrabLedge(const v2f& aLedgeLerpPosition, const v2f& aLedgePosition)
{
	if (myTransform.myPosition.x > aLedgePosition.x)
	{
		myAnimations[myCurrentAnimationIndex].mySpriteComponent->SetSizeX(-70.0f);
	}
	else if (myTransform.myPosition.x < aLedgePosition.x)
	{
		myAnimations[myCurrentAnimationIndex].mySpriteComponent->SetSizeX(70.0f);
	}

	myIsLerpingToPosition = true;
	myLerpPosition = aLedgeLerpPosition;

	myGrabbedLedge = true;
	myCurrentVelocity.y = 0;
	myBashAbility->ResetVelocity(true, true);
}

void Player::LeaveLedge()
{
	myGrabbedLedge = false;
}

const bool Player::GetLedgeIsGrabbed()
{
	return myGrabbedLedge;
}

void Player::LerpToPosition(const v2f& aPosition, const float& aDeltaTime)
{
	myTransform.myPosition.x = Utils::Lerp(myTransform.myPosition.x, aPosition.x, myLerpToPositionAcceleration * aDeltaTime);
	myTransform.myPosition.y = Utils::Lerp(myTransform.myPosition.y, aPosition.y, myLerpToPositionAcceleration * aDeltaTime);
}

void Player::ImGuiUpdate()
{
	ImGui::Begin("Player", &myIsActive, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::SliderFloat("Max Speed", &myMaxRunningSpeed, 0.0f, 2000.0f);
	ImGui::SliderFloat("Acceleration", &myAcceleration, 0.0f, 100.0f);
	ImGui::SliderFloat("Retardation", &myRetardation, 0.0f, 100.0f);
	ImGui::SliderFloat("Coyote Time", &myAirCoyoteTime, 0.0f, 1.0f);
	ImGui::SliderFloat("Jump Velocity", &myJumpVelocity, 0.0f, 2000.0f);
	ImGui::SliderFloat("Double Jump Velocity", &myDoubleJumpVelocity, 0.0f, 2000.0f);
	ImGui::SliderFloat("Jump When Falling Time", &myJumpWhenFallingTime, 0.0f, 1.0f);

	ImGui::End();
}