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
#include "BashComponent.hpp"
#include "SpringObject.h"
#include "AudioManager.h"

#include "Collectible.hpp"

#include "Ledge.h"

#include "PostMaster.hpp"

#ifdef _DEBUG
#include "imgui.h"
#endif // DEBUG

typedef PlayerData::PlayerFloatEnum PEnum;

Player::Player(LevelScene* aLevelScene) : GameObject(aLevelScene)
{
	myJsonData = dynamic_cast<PlayerData*>(&DataManager::GetInstance().GetDataStruct(DataEnum::player));
	CGameWorld* world = CGameWorld::GetInstance();
	myInputHandler = world->Input();
	myTimerInput = world->GetTimer();

	myBashAbility = new BashAbility(aLevelScene);
	myBashAbility->Init();
	myBashAbility->AddInputWrapper(world->Input());
	myBashAbility->AddPlayerRelation(this);
	myBashAbility->AddTimer(world->GetTimer());

	myHasDied = false;
	myIsOnPlatform = false;

	SetZIndex(101);
	SetPosition({ 20.0f, 10.0f });

	SetPivot(v2f(0.5f, 0.5f));

	mySpawnPosition = v2f(20.0f, 10.0f);
	mySize = v2f(16.0f, 16.0f);

	InitAnimations();
	InitCollider();

	myTriggerRunningAnimationSpeed = 50.0f;
	myAirCoyoteTimer = myJsonData->myFloatValueMap[PEnum::Coyote_Time];

	myDirectionX = 1;
	myCurrentAnimationIndex = 0;

	myHasLanded = true;
	myHasDoubleJumped = false;
	myHasLandedOnSpring = false;
	myCanJumpWhenFalling = false;
	myWillJumpWhenFalling = false;
	myActiveSpringJump = false;
	myGrabbedLedge = false;
	myIsLerpingToPosition = false;

	mySpringVelocity = {};
	myPercentageLeftVelocity = {};
	mySpringVelocityRetardation = {};
	mySpringTimer = {};
}

Player::~Player()
{

}

void Player::InitAnimations()
{
	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/Characters/PlayerIdle.dds");
	spriteIdle->SetSize(mySize);

	SpriteComponent* spriteRun = AddComponent<SpriteComponent>();
	spriteRun->SetSpritePath("Sprites/Characters/SpritePlayerRun.dds");
	spriteRun->SetSize(mySize);
	spriteRun->Deactivate();

	SpriteComponent* spriteJump = AddComponent<SpriteComponent>();
	spriteJump->SetSpritePath("Sprites/Characters/PlayerJump.dds");
	spriteJump->SetSize(mySize);
	spriteJump->Deactivate();

	SpriteComponent* spriteDoubleJump = AddComponent<SpriteComponent>();
	spriteDoubleJump->SetSpritePath("Sprites/Characters/PlayerDoubleJump.dds");
	spriteDoubleJump->SetSize(mySize);
	spriteDoubleJump->Deactivate();

	SpriteComponent* spriteFall = AddComponent<SpriteComponent>();
	spriteFall->SetSpritePath("Sprites/Characters/PlayerFall.dds");
	spriteFall->SetSize(mySize);
	spriteFall->Deactivate();

	SpriteComponent* spriteLedgeGrab = AddComponent<SpriteComponent>();
	spriteLedgeGrab->SetSpritePath("Sprites/Characters/playerLedgeGrab.dds");
	spriteLedgeGrab->SetSize(mySize);
	spriteLedgeGrab->Deactivate();

	SpriteComponent* spriteBashStart = AddComponent<SpriteComponent>();
	spriteBashStart->SetSpritePath("Sprites/Characters/PlayerBashStart.dds");
	spriteBashStart->SetSize(mySize);
	spriteBashStart->Deactivate();

	SpriteComponent* spriteBashLoop = AddComponent<SpriteComponent>();
	spriteBashLoop->SetSpritePath("Sprites/Characters/PlayerBashLoop.dds");
	spriteBashLoop->SetSize(mySize);
	spriteBashLoop->Deactivate();

	SpriteComponent* spriteBashFlying = AddComponent<SpriteComponent>();
	spriteBashFlying->SetSpritePath("Sprites/Characters/PlayerBashFlyingLoop.dds");
	spriteBashFlying->SetSize(mySize);
	spriteBashFlying->Deactivate();

	SpriteComponent* spriteBashFlyingTransition = AddComponent<SpriteComponent>();
	spriteBashFlyingTransition->SetSpritePath("Sprites/Characters/PlayerBashFlyingTransition.dds");
	spriteBashFlyingTransition->SetSize(mySize);
	spriteBashFlyingTransition->Deactivate();

	SpriteComponent* spriteDeath = AddComponent<SpriteComponent>();
	spriteDeath->SetSpritePath("Sprites/Characters/PlayerDeath.dds");
	spriteDeath->SetSize(mySize);
	spriteDeath->Deactivate();

	myAnimations[0] = Animation(false, false, false, 0, 74, 74, 0.10f, spriteIdle, 16, 16);
	myAnimations[1] = Animation(false, false, false, 0, 12, 12, 0.09f, spriteRun, 16, 16);
	myAnimations[2] = Animation(false, true, false, 0, 6, 6, 0.09f, spriteJump, 16, 16);
	myAnimations[3] = Animation(false, true, false, 0, 5, 5, 0.09f, spriteDoubleJump, 16, 16);
	myAnimations[4] = Animation(false, false, false, 0, 4, 4, 0.09f, spriteFall, 16, 16);
	myAnimations[5] = Animation(false, false, false, 0, 22, 22, 0.125f, spriteLedgeGrab, 16, 16);
	myAnimations[6] = Animation(false, true, false, 0, 13, 13, 0.07f, spriteBashStart, 16, 16);
	myAnimations[7] = Animation(false, false, false, 0, 9, 9, 0.10f, spriteBashLoop, 16, 16);
	myAnimations[8] = Animation(false, false, false, 0, 4, 4, 0.10f, spriteBashFlying, 16, 16);
	myAnimations[9] = Animation(false, true, false, 0, 4, 4, 0.10f, spriteBashFlyingTransition, 16, 16);
	myAnimations[10] = Animation(false, true, false, 0, 22, 22, 0.07f, spriteDeath, 16, 16);

	AnimationComponent* animation = AddComponent<AnimationComponent>();
	animation->SetSprite(spriteIdle);
	animation->SetAnimation(&myAnimations[0]);
	spriteIdle->SetSize(mySize);
}
void Player::InitCollider()
{
	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(true);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(false);

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetSize(7.0f, 12.0f);
	collider->SetPosition(v2f(0.0f, 2.0f));
}

void Player::Update(const float& aDeltaTime)
{
	GameObject::Update(aDeltaTime);

	if (myHasDied)
	{
		Kill();
		GetComponent<PhysicsComponent>()->SetVelocity(v2f(0.0f, 0.0f));
		return;
	}

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
			LerpToPosition(myLerpPosition);
		}
	}

	if (CGameWorld::GetInstance()->GetTimer()->GetTimeScale() <= 0)
	{
		CGameWorld::GetInstance()->GetTimer()->SetTimeScale(1.0f);
		GetComponent<AnimationComponent>()->Update(myTransform, *this);
		CGameWorld::GetInstance()->GetTimer()->SetTimeScale(0.0f);
	}

	AnimationState();

	/*
	if (myTransform.myPosition.y + mySize.y > myScene->GetCamera().GetBounds().y + myScene->GetCamera().GetBoundSize().y)
	{
		Kill();
	}
	*/

#ifdef _DEBUG
	ImGuiUpdate();
#endif //DEBUG
}
void Player::UpdateCoyoteTime(const float& aDeltaTime)
{
	if (GetComponent<PhysicsComponent>()->GetVelocityY() > 0)
	{
		myAirCoyoteTimer -= aDeltaTime;
	}
}
void Player::UpdatePlayerVelocity(const float& aDeltaTime)
{
	if (!myGrabbedLedge)
	{
		myCurrentVelocity.y = Utils::Min(myCurrentVelocity.y + PhysicsManager::ourGravity * aDeltaTime, myJsonData->myFloatValueMap[PEnum::Max_Fall_Speed]);
	}

	PhysicsComponent* physics = GetComponent<PhysicsComponent>();
	physics->SetVelocity(myCurrentVelocity + myBashAbility->GetVelocity() + myPlatformVelocity + mySpringVelocity);

	if (physics->GetVelocityX() > 0)
	{
		myDirectionX = 1;
	}
	else if (physics->GetVelocityX() < 0)
	{
		myDirectionX = -1;
	}

	if (myCurrentVelocity.y > myJsonData->myFloatValueMap[PEnum::Trigger_Falling_Speed] && myAirCoyoteTimer <= 0)
	{
		myHasLanded = false;
	}

	myPlatformVelocity.x = Utils::Lerp(myPlatformVelocity.x, 0.0f, myJsonData->myFloatValueMap[PEnum::Platform_Velocity_Retardation] * aDeltaTime);
	myPlatformVelocity.y = Utils::Lerp(myPlatformVelocity.y, 0.0f, myJsonData->myFloatValueMap[PEnum::Platform_Velocity_Retardation] * aDeltaTime);

	if (myActiveSpringJump)
		DecreaseSpringJump(aDeltaTime);

	if (myCurrentVelocity.y > 0)
	{
		myPlatformVelocity.y = 0.0f;
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
		myCurrentVelocity.x = Utils::Lerp(myCurrentVelocity.x, 0.0f, myJsonData->myFloatValueMap[PEnum::Retardation] * aDeltaTime);
	}
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
void Player::GoRight(const float& aDeltaTime)
{
	if (myCurrentVelocity.x < 0)
	{
		myCurrentVelocity.x = 0.0f;
	}

	if (myPlatformVelocity.x < 0)
	{
		myPlatformVelocity.x = 0.0f;
	}

	if (myBashAbility->GetVelocity().x < 0)
	{
		myBashAbility->ResetVelocity(true, false);
	}

	myCurrentVelocity.x = Utils::Lerp(myCurrentVelocity.x, myJsonData->myFloatValueMap[PEnum::Max_Speed], myJsonData->myFloatValueMap[PEnum::Acceleration] * aDeltaTime);
}
void Player::GoLeft(const float& aDeltaTime)
{
	if (myCurrentVelocity.x > 0)
	{
		myCurrentVelocity.x = 0.0f;
	}

	if (myPlatformVelocity.x > 0)
	{
		myPlatformVelocity.x = 0.0f;
	}

	if (myBashAbility->GetVelocity().x > 0)
	{
		myBashAbility->ResetVelocity(true, false);
	}

	myCurrentVelocity.x = Utils::Lerp(myCurrentVelocity.x, -myJsonData->myFloatValueMap[PEnum::Max_Speed], myJsonData->myFloatValueMap[PEnum::Acceleration] * aDeltaTime);
}

void Player::TryLetJumpWhenFalling(const float& aYDistance)
{
	const float distancePerJumpWhenLandingTime = GetComponent<PhysicsComponent>()->GetVelocityY() * myJsonData->myFloatValueMap[PEnum::Jump_When_Falling_Time];
	if (aYDistance < distancePerJumpWhenLandingTime && aYDistance > 0)
	{
		myCanJumpWhenFalling = true;
	}
	else
	{
		myCanJumpWhenFalling = false;
	}
}
void Player::Jump()
{
	if (myPlatformVelocity.y > 0.0f)
	{
		myPlatformVelocity.y = 0;
	}

	UnlockLandingSounds();
	AudioManager::GetInstance()->PlayAudio(AudioList::PlayerJump);
	v2f calculatedSpring = mySpringVelocity;
	calculatedSpring.y = calculatedSpring.y;
	myCurrentVelocity.y = -myJsonData->myFloatValueMap[PEnum::Jump_Velocity] + myPlatformVelocity.y - calculatedSpring.y;
	GetComponent<AnimationComponent>()->SetAnimation(&myAnimations[2]);
	GetComponent<AnimationComponent>()->SetNextAnimation(&myAnimations[4]);
	myCurrentAnimationIndex = 2;
	myHasLanded = false;
	myWillJumpWhenFalling = false;
	myBashAbility->ResetVelocity(false, true);
}
void Player::DoubleJump()
{
	AudioManager::GetInstance()->PlayAudio(AudioList::PlayerJump);
	myCurrentVelocity.y = -myJsonData->myFloatValueMap[PEnum::Double_Jump_Velocity] + myPlatformVelocity.y - mySpringVelocity.y;
	GetComponent<AnimationComponent>()->SetAnimation(&myAnimations[3]);
	GetComponent<AnimationComponent>()->SetNextAnimation(&myAnimations[4]);
	myCurrentAnimationIndex = 3;
	myHasLanded = false;
	myHasDoubleJumped = true;
	myWillJumpWhenFalling = false;
	myBashAbility->ResetVelocity(false, true);
}
void Player::LedgeJump()
{
	myGrabbedLedge = false;
	AudioManager::GetInstance()->UnLockAudio(AudioList::LandOnGrassEasy);
	if (!myInputHandler->GetInput()->GetKeyDown(Keys::SKey) && myInputHandler->GetController()->GetLeftThumbStick().y < 0.3f)
	{
		myCurrentVelocity.y = -myJsonData->myFloatValueMap[PEnum::Ledge_Jump_Velocity];
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
	if (!myHasLanded)
	{
		myInputHandler->GetController()->Vibrate(
			myJsonData->myFloatValueMap[PEnum::Land_Vibration_Strength],
			myJsonData->myFloatValueMap[PEnum::Land_Vibration_Strength],
			myJsonData->myFloatValueMap[PEnum::Land_Vibration_Length]);

		myScene->GetCamera().Shake(
			myJsonData->myFloatValueMap[PEnum::Land_Shake_Duration],
			myJsonData->myFloatValueMap[PEnum::Land_Shake_Intensity],
			myJsonData->myFloatValueMap[PEnum::Land_Shake_DropOff]);
	}

	if (aOverlapY > 0)
	{
		myAirCoyoteTimer = myJsonData->myFloatValueMap[PEnum::Coyote_Time];
		if (!myActiveSpringJump)
			myHasLanded = true;
		myHasDoubleJumped = false;

		myBashAbility->ResetVelocity(true, true);

		if (myWillJumpWhenFalling)
		{
			Jump();
		}
	}
	LandingSoundCheck();
	myCurrentVelocity.y = 0.0f;
	myBashAbility->ResetVelocity(false, true);
	if (!myHasLandedOnSpring)
		mySpringVelocity.y = {};
}

const bool& Player::GetHasLanded()
{
	return myHasLanded;
}

void Player::SideCollision(const int& aOverlapX)
{
	aOverlapX;
	myCurrentVelocity.x = 0.0f;
	myBashAbility->ResetVelocity(true, false);
	mySpringVelocity.x = {};
}

void Player::ResetVelocity()
{
	myCurrentVelocity.x = 0;
	myCurrentVelocity.y = 0;
}


const v2f Player::GetPlatformVelocity()
{
	return myPlatformVelocity;
}
void Player::SetPlatformVelocity(const v2f& aPlatformVelocity)
{
	myPlatformVelocity = aPlatformVelocity;
}

void Player::AnimationState()
{
	AnimationComponent* animation = GetComponent<AnimationComponent>();
	if (Utils::Abs(myCurrentVelocity.x) <= myTriggerRunningAnimationSpeed && myHasLanded && myCurrentAnimationIndex != 0)
	{
		animation->SetAnimation(&myAnimations[0]);
		myCurrentAnimationIndex = 0;
	}
	else if (Utils::Abs(myCurrentVelocity.x) > myTriggerRunningAnimationSpeed && myHasLanded && myCurrentAnimationIndex != 1)
	{
		animation->SetAnimation(&myAnimations[1]);
		myCurrentAnimationIndex = 1;
	}

	if (myCurrentAnimationIndex != 2 && myCurrentAnimationIndex != 3 && myCurrentAnimationIndex != 4 && !myHasLanded)
	{
		UnlockLandingSounds();
		animation->SetAnimation(&myAnimations[4]);
		myCurrentAnimationIndex = 4;
	}

	for (Animation& animation : myAnimations)
	{
		animation.mySpriteComponent->SetSizeX(mySize.x * myDirectionX);
	}

	WalkingSoundCheck();
}

void Player::GrabLedge(const v2f& aLedgeLerpPosition, const v2f& aLedgePosition)
{
	if (myTransform.myPosition.x > aLedgePosition.x)
	{
		myDirectionX = -1;
	}
	else if (myTransform.myPosition.x < aLedgePosition.x)
	{
		myDirectionX = 1;
	}

	SetLerpPosition(aLedgeLerpPosition);

	AnimationComponent* animation = GetComponent<AnimationComponent>();
	animation->SetAnimation(&myAnimations[5]);

	myGrabbedLedge = true;
	myCurrentVelocity.y = 0;
	myBashAbility->ResetVelocity(true, true);
}
void Player::LeaveLedge()
{
	myGrabbedLedge = false;
	myIsLerpingToPosition = false;
}
const bool Player::GetLedgeIsGrabbed()
{
	return myGrabbedLedge;
}

void Player::LerpToPosition(const v2f& aPosition)
{
	const float timeScale = myTimerInput->GetTimeScale();;

	myTimerInput->SetTimeScale(1.0f);

	myTransform.myPosition.x = Utils::Lerp(myTransform.myPosition.x, aPosition.x, myJsonData->myFloatValueMap[PEnum::Lerp_Acceleration] * myTimerInput->GetDeltaTime());
	myTransform.myPosition.y = Utils::Lerp(myTransform.myPosition.y, aPosition.y, myJsonData->myFloatValueMap[PEnum::Lerp_Acceleration] * myTimerInput->GetDeltaTime());

	if (aPosition.x > myTransform.myPosition.x)
	{
		myDirectionX = 1;
	}
	else if(aPosition.x < myTransform.myPosition.x)
	{
		myDirectionX = -1;
	}

	myTimerInput->SetTimeScale(timeScale);
}
void Player::SetLerpPosition(const v2f& aPosition)
{
	myLerpPosition = aPosition;
	myIsLerpingToPosition = true;
}
void Player::EndLerp()
{
	myIsLerpingToPosition = false;
}

void Player::ActivateSpringForce(float aSpringVelocity, const float aRetardation)
{
	ReactivateDoubleJump();
	myHasLanded = false;
	myActiveSpringJump = true;
	myHasLandedOnSpring = true;
	myBashAbility->ResetVelocity(false, true);
	myCurrentVelocity.y = {};
	mySpringVelocityRetardation = aRetardation;
	mySpringVelocity.y = aSpringVelocity;
}
void Player::BounceOnDestructibleWall()
{
	v2f dashVelocity = myBashAbility->GetVelocity();
	dashVelocity.x *= -0.8f;

	myBashAbility->InvertDashDirectionX();
	myBashAbility->SetVelocity(dashVelocity);
}

void Player::Kill()
{
	if (!myHasDied)
	{
		AudioManager::GetInstance()->PlayAudio(AudioList::PlayerDeath);
		KillReset();
	}
	else if (GetComponent<AnimationComponent>()->GetIsDisplayedOnce() && GetComponent<AnimationComponent>()->GetHasBeenDisplayedOnce())
	{
		Respawn();
		PostMaster::GetInstance().ReceiveMessage(Message(eMessageType::PlayerDeath, 0));
	}
}

void Player::Eaten()
{
	KillReset();
}

void Player::KillReset()
{
	myScene->GetCamera().Shake(
		myJsonData->myFloatValueMap[PEnum::Die_Shake_Duration],
		myJsonData->myFloatValueMap[PEnum::Die_Shake_Intensity],
		myJsonData->myFloatValueMap[PEnum::Die_Shake_DropOff]);
	myInputHandler->GetController()->Vibrate(
		myJsonData->myFloatValueMap[PEnum::Die_Vibration_Strength],
		myJsonData->myFloatValueMap[PEnum::Die_Vibration_Strength],
		myJsonData->myFloatValueMap[PEnum::Die_Vibration_Length]);

	ResetVelocity();
	myBashAbility->ResetVelocity(true, true);
	myBashAbility->StopBashing();
	myPlatformVelocity = v2f();
	myHasDied = true;
	SetAnimation(10);
	GetComponent<AnimationComponent>()->SetNextAnimation(nullptr);
}

void Player::Respawn()
{
	myHasDied = false;
	SetAnimation(0);
	SetPosition(mySpawnPosition);
}

const bool& Player::GetIsBashing()
{
	return myBashAbility->GetIsBashing();
}

void Player::BashCollision(GameObject* aGameObject, BashComponent* aBashComponent)
{
	if (myHasDied)
	{
		return;
	}

	if (aBashComponent->GetRadius() * aBashComponent->GetRadius() >= (aGameObject->GetPosition() - GetPosition()).LengthSqr())
	{
		if (myInputHandler->IsDashing() && !myBashAbility->GetIsBashing())
		{
			aGameObject->OnStartBashed();
			myBashAbility->ActivateBash(aGameObject);
			SetLerpPosition(aGameObject->GetPosition());
		}
	}
}

void Player::DecreaseSpringJump(const float& aDeltaTime)
{
	if (myCurrentVelocity.y == 0)
	{
		myActiveSpringJump = false;
		mySpringVelocity = {};
		myCurrentVelocity.y = {};
	}

	if (GetComponent<PhysicsComponent>()->GetVelocityY() > 0)
	{
		myActiveSpringJump = false;
		mySpringVelocity = {};
		myCurrentVelocity.y = {};
	}
	else
	{
		myHasLandedOnSpring = false;
		mySpringVelocity.x = {};
		mySpringVelocity.y = Utils::Lerp(mySpringVelocity.y, 0.f, mySpringVelocityRetardation * aDeltaTime);
	}
}

void Player::SetAnimation(const int& aAnimationIndex)
{
	GetComponent<AnimationComponent>()->SetAnimation(&myAnimations[aAnimationIndex]);
}


void Player::SetNextAnimation(const int& aAnimationIndex)
{
	GetComponent<AnimationComponent>()->SetNextAnimation(&myAnimations[aAnimationIndex]);
}

void Player::SetGroundIndex(const int& aGroundType)
{
	myGroundIndex = aGroundType;
}

void Player::WalkingSoundCheck()
{
	AnimationComponent* animation = GetComponent<AnimationComponent>();
	if (myCurrentAnimationIndex == 1)
	{
		//If is running
		switch (myGroundIndex)
		{
		case 0: // Grass
			switch (animation->GetCurrentIndex())
			{
			case 1:
				AudioManager::GetInstance()->PlayAudio(AudioList::WalkGrassRight);
				AudioManager::GetInstance()->LockAudio(AudioList::WalkGrassRight);
				break;
			case 7:
				AudioManager::GetInstance()->PlayAudio(AudioList::WalkGrassLeft);
				AudioManager::GetInstance()->LockAudio(AudioList::WalkGrassLeft);
				break;
			default:
				AudioManager::GetInstance()->UnLockAudio(AudioList::WalkGrassRight);
				AudioManager::GetInstance()->UnLockAudio(AudioList::WalkGrassLeft);
				break;
			}
			break;
		case 1:
			switch (animation->GetCurrentIndex())
			{
			case 1:
				AudioManager::GetInstance()->PlayAudio(AudioList::WalkStoneRight);
				AudioManager::GetInstance()->LockAudio(AudioList::WalkStoneRight);
				break;
			case 7:
				AudioManager::GetInstance()->PlayAudio(AudioList::WalkStoneLeft);
				AudioManager::GetInstance()->LockAudio(AudioList::WalkStoneLeft);
				break;
			default:
				AudioManager::GetInstance()->UnLockAudio(AudioList::WalkStoneRight);
				AudioManager::GetInstance()->UnLockAudio(AudioList::WalkStoneLeft);
				break;
			}
		default:
			break;
		}
	}
}

void Player::LandingSoundCheck()
{
	if (myCurrentVelocity.y > 200.0f)
	{
		switch (myGroundIndex)
		{
		case 0:
			AudioManager::GetInstance()->PlayAudio(AudioList::LandOnGrassHeavy);
			AudioManager::GetInstance()->LockAudio(AudioList::LandOnGrassEasy);
			break;
		case 1:
			AudioManager::GetInstance()->PlayAudio(AudioList::LandOnStoneHeavy);
			AudioManager::GetInstance()->LockAudio(AudioList::LandOnStoneLight);
			break;
		}
	}
	else if (myCurrentVelocity.y != 0)
	{
		switch (myGroundIndex)
		{
		case 0:
			AudioManager::GetInstance()->PlayAudio(AudioList::LandOnGrassEasy);
			AudioManager::GetInstance()->LockAudio(AudioList::LandOnGrassEasy);
			break;
		case 1:
			AudioManager::GetInstance()->PlayAudio(AudioList::LandOnStoneLight);
			AudioManager::GetInstance()->LockAudio(AudioList::LandOnStoneLight);
			break;
		}
	}
}

void Player::UnlockLandingSounds()
{
	AudioManager::GetInstance()->UnLockAudio(AudioList::LandOnGrassEasy);
	AudioManager::GetInstance()->UnLockAudio(AudioList::LandOnStoneLight);
}

void Player::SetSpawnPosition(const v2f& aSpawnPosition)
{
	mySpawnPosition = aSpawnPosition;
}

#ifdef _DEBUG
void Player::ImGuiUpdate()
{
	ImGui::Begin("Player", &myIsActive, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Save to JSON"))
	{
		DataManager::GetInstance().SetDataStruct(DataEnum::player);
	}

	ImGui::InputFloat("Max Speed", &myJsonData->myFloatValueMap[PEnum::Max_Speed], 0.0f, 2000.0f);
	ImGui::InputFloat("Acceleration", &myJsonData->myFloatValueMap[PEnum::Acceleration], 0.0f, 100.0f);
	ImGui::InputFloat("Retardation", &myJsonData->myFloatValueMap[PEnum::Retardation], 0.0f, 100.0f);
	ImGui::InputFloat("Lerp Acceleration", &myJsonData->myFloatValueMap[PEnum::Lerp_Acceleration], 0.0f, 100.0f);
	ImGui::InputFloat("Platform Velocity Retardation", &myJsonData->myFloatValueMap[PEnum::Platform_Velocity_Retardation], 0.0f, 100.0f);
	ImGui::InputFloat("Coyote Time", &myJsonData->myFloatValueMap[PEnum::Coyote_Time], 0.0f, 1.0f);
	ImGui::InputFloat("Jump Velocity", &myJsonData->myFloatValueMap[PEnum::Jump_Velocity], 0.0f, 2000.0f);
	ImGui::InputFloat("Double Jump Velocity", &myJsonData->myFloatValueMap[PEnum::Double_Jump_Velocity], 0.0f, 2000.0f);
	ImGui::InputFloat("Max Fall Speed", &myJsonData->myFloatValueMap[PEnum::Max_Fall_Speed], 0.0f, 2000.0f);
	ImGui::InputFloat("Ledge Jump Velocity", &myJsonData->myFloatValueMap[PEnum::Ledge_Jump_Velocity], 0.0f, 2000.0f);
	ImGui::InputFloat("Jump When Falling Time", &myJsonData->myFloatValueMap[PEnum::Jump_When_Falling_Time], 0.0f, 1.0f);
	ImGui::InputFloat("Trigger Falling Speed", &myJsonData->myFloatValueMap[PEnum::Trigger_Falling_Speed], 0.0f, 50.0f);

	ImGui::Text("Vibrations");
	ImGui::InputFloat("Die Vibration Strength", &myJsonData->myFloatValueMap[PEnum::Die_Vibration_Strength], 0, 65000);
	ImGui::InputFloat("Land Vibration Strength", &myJsonData->myFloatValueMap[PEnum::Land_Vibration_Strength], 0, 65000);
	ImGui::InputFloat("Springs Vibration Strength", &myJsonData->myFloatValueMap[PEnum::Springs_Vibration_Strength], 0, 65000);

	ImGui::InputFloat("Die Vibration Length", &myJsonData->myFloatValueMap[PEnum::Die_Vibration_Length], 0.0f, 10.0f);
	ImGui::InputFloat("Land Vibration Length", &myJsonData->myFloatValueMap[PEnum::Land_Vibration_Length], 0.0f, 10.0f);
	ImGui::InputFloat("Springs Vibration Length", &myJsonData->myFloatValueMap[PEnum::Springs_Vibration_Length], 0.0f, 10.0f);

	ImGui::Text("Camera Shake");
	ImGui::InputFloat("Die Shake Duration", &myJsonData->myFloatValueMap[PEnum::Die_Shake_Duration], 0.0f, 10.0f);
	ImGui::InputFloat("Die Shake Intensity", &myJsonData->myFloatValueMap[PEnum::Die_Shake_Intensity], 0.0f, 10.0f);
	ImGui::InputFloat("Die Shake DropOff", &myJsonData->myFloatValueMap[PEnum::Die_Shake_DropOff], 0.0f, 10.0f);

	ImGui::InputFloat("Land Shake Duration", &myJsonData->myFloatValueMap[PEnum::Land_Shake_Duration], 0.0f, 10.0f);
	ImGui::InputFloat("Land Shake Intensity", &myJsonData->myFloatValueMap[PEnum::Land_Shake_Intensity], 0.0f, 10.0f);
	ImGui::InputFloat("Land Shake DropOff", &myJsonData->myFloatValueMap[PEnum::Land_Shake_DropOff], 0.0f, 10.0f);

	ImGui::InputFloat("Spring Shake Duration", &myJsonData->myFloatValueMap[PEnum::Spring_Shake_Duration], 0.0f, 10.0f);
	ImGui::InputFloat("Spring Shake Intensity", &myJsonData->myFloatValueMap[PEnum::Spring_Shake_Intensity], 0.0f, 10.0f);
	ImGui::InputFloat("Spring Shake DropOff", &myJsonData->myFloatValueMap[PEnum::Spring_Shake_DropOff], 0.0f, 10.0f);

	ImGui::End();
}
#endif // DEBUG
