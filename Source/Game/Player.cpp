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

#include "Ledge.h"

#include "imgui.h"

Player::Player(LevelScene* aLevelScene)
	:
	GameObject(aLevelScene)
{

	SetZIndex(500);
	SetPosition({ 700.0f, 640.0f });
	mySpawnPosition = v2f(700.0f, 640.0f);
	mySize = v2f(16.0f, 16.0f);

	InitAnimations();

	InitCollider();

	CGameWorld* world = CGameWorld::GetInstance();
	myInputHandler = world->Input();

	myJsonData = dynamic_cast<PlayerData*>(&DataManager::GetInstance().GetDataStruct(DataEnum::player));

	myRunningAnimationSpeed = 50.0f;

	myAcceleration = 6.0f;
	myRetardation = 20.0f;
	myLerpToPositionAcceleration = 6.0f;
	myPlatformVelocityRetardation = 1.0f;

	myAirCoyoteTime = 0.1f;
	myAirCoyoteTimer = myAirCoyoteTime;

	myJumpVelocity = 600.0f;
	myDoubleJumpVelocity = 600.0f;
	myLedgeJumpVelocity = 360.0f;

	myMaxFallSpeed = 700.0f;

	myJumpWhenFallingTime = 0.075f;

	myCurrentAnimationIndex = 0;

	myHasLanded = true;
	myHasDoubleJumped = false;

	myCanJumpWhenFalling = false;
	myWillJumpWhenFalling = false;

	myGrabbedLedge = false;

	myIsLerpingToPosition = false;

	myTimerInput = world->GetTimer();

	myBashAbility = std::make_unique<BashAbility>(aLevelScene);
	myBashAbility->Init();
	myBashAbility->AddInputWrapper(world->Input());
	myBashAbility->AddPlayerRelation(this);
	myBashAbility->AddTimer(world->GetTimer());

	InitVibrations();

	InitShakes();
}

void Player::InitAnimations()
{
	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/TommyIdle.dds");
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

	myAnimations[0] = Animation(false, false, true, 0, 3, 3, 0.15f, spriteIdle, 512, 512);
	myAnimations[1] = Animation(false, false, false, 0, 12, 12, 0.05f, spriteRun, 16, 16);
	myAnimations[2] = Animation(false, true, false, 0, 6, 6, 0.10f, spriteJump, 16, 16);
	myAnimations[3] = Animation(false, true, false, 0, 5, 5, 0.10f, spriteDoubleJump, 16, 16);
	myAnimations[4] = Animation(false, false, false, 0, 4, 4, 0.10f, spriteFall, 16, 16);

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

	physics->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this);
}

void Player::InitVibrations()
{
	myDieVibrationStrength = 65000;
	myDieVibrationLength = 0.5f;

	myLandVibrationStrength = 60000;
	myLandVibrationLength = 0.15f;

	mySpringsVibrationStrength = 55000;
	mySpringsVibrationLength = 0.3f;
}

void Player::InitShakes()
{
	myDieShakeDuration = 1.0f;
	myDieShakeIntensity = 2.0f;
	myDieShakeDropOff = 1.0f;

	myLandingShakeDuration = 0.5f;
	myLandingShakeIntensity = 0.8f;
	myLandingShakeDropOff = 1.0f;

	mySpringShakeDuration = 1.0f;
	mySpringShakeIntensity = 1.0f;
	mySpringShakeDropOff = 1.0f;
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

	if (myTransform.myPosition.y + mySize.y > myScene->GetCamera().GetBounds().y + myScene->GetCamera().GetBoundSize().y)
	{
		Kill();
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

	if (myPlatformVelocity.x < 0)
	{
		myPlatformVelocity.x = 0.0f;
	}

	if (myBashAbility->GetVelocity().x < 0)
	{
		myBashAbility->ResetVelocity(true, false);
	}

	myCurrentVelocity.x = Utils::Lerp(myCurrentVelocity.x, myJsonData->myMaxSpeed, myAcceleration * aDeltaTime);
	myAnimations[myCurrentAnimationIndex].mySpriteComponent->SetSizeX(mySize.x);
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

	myCurrentVelocity.x = Utils::Lerp(myCurrentVelocity.x, -myJsonData->myMaxSpeed, myAcceleration * aDeltaTime);
	myAnimations[myCurrentAnimationIndex].mySpriteComponent->SetSizeX(-mySize.x);
}

void Player::Jump()
{
	myCurrentVelocity.y = -myJumpVelocity + myPlatformVelocity.y;
	GetComponent<AnimationComponent>()->SetAnimation(&myAnimations[2]);
	GetComponent<AnimationComponent>()->SetNextAnimation(&myAnimations[4]);
	myCurrentAnimationIndex = 2;
	myHasLanded = false;
	myWillJumpWhenFalling = false;
	myBashAbility->ResetVelocity(false, true);
}

void Player::DoubleJump()
{
	myCurrentVelocity.y = -myDoubleJumpVelocity + myPlatformVelocity.y;
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

	if (!myInputHandler->GetInput()->GetKeyDown(Keys::SKey) && myInputHandler->GetController()->GetLeftThumbStick().y < 0.3f)
	{
		myCurrentVelocity.y = -myLedgeJumpVelocity;
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
		myInputHandler->GetController()->Vibrate(myLandVibrationStrength, myLandVibrationStrength, myLandVibrationLength);
		myScene->GetCamera().Shake(myLandingShakeDuration, myLandingShakeIntensity, myLandingShakeDropOff);
	}

	if (aOverlapY > 0)
	{
		myAirCoyoteTimer = myAirCoyoteTime;
		myHasLanded = true;
		myHasDoubleJumped = false;

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
	aOverlapX;
	myCurrentVelocity.x = 0.0f;
	myBashAbility->ResetVelocity(true, false);
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
	if (Utils::Abs(myCurrentVelocity.x) <= myRunningAnimationSpeed && myHasLanded && myCurrentAnimationIndex != 0)
	{
		animation->SetAnimation(&myAnimations[0]);
		myCurrentAnimationIndex = 0;
	}
	else if (Utils::Abs(myCurrentVelocity.x) > myRunningAnimationSpeed && myHasLanded && myCurrentAnimationIndex != 1)
	{
		animation->SetAnimation(&myAnimations[1]);
		myCurrentAnimationIndex = 1;
	}
}

void Player::UpdatePlayerVelocity(const float& aDeltaTime)
{
	if (!myGrabbedLedge)
	{
		myCurrentVelocity.y = Utils::Min(myCurrentVelocity.y + PhysicsManager::ourGravity * aDeltaTime, myMaxFallSpeed);
	}

	PhysicsComponent* physics = GetComponent<PhysicsComponent>();
	physics->SetVelocity(myCurrentVelocity + myBashAbility->GetVelocity() + myPlatformVelocity);

	myPlatformVelocity.x = Utils::Lerp(myPlatformVelocity.x, 0.0f, myPlatformVelocityRetardation * aDeltaTime);
	myPlatformVelocity.y = Utils::Lerp(myPlatformVelocity.y, 0.0f, myPlatformVelocityRetardation * aDeltaTime);
}

void Player::GrabLedge(const v2f& aLedgeLerpPosition, const v2f& aLedgePosition)
{
	if (myTransform.myPosition.x > aLedgePosition.x)
	{
		myAnimations[myCurrentAnimationIndex].mySpriteComponent->SetSizeX(-mySize.x);
	}
	else if (myTransform.myPosition.x < aLedgePosition.x)
	{
		myAnimations[myCurrentAnimationIndex].mySpriteComponent->SetSizeX(mySize.x);
	}

	SetLerpPosition(aLedgeLerpPosition);

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

void Player::LerpToPosition(const v2f& aPosition, const float& aDeltaTime)
{
	const float timeScale = myTimerInput->GetTimeScale();;

	myTimerInput->SetTimeScale(1.0f);

	myTransform.myPosition.x = Utils::Lerp(myTransform.myPosition.x, aPosition.x, myLerpToPositionAcceleration * myTimerInput->GetDeltaTime());
	myTransform.myPosition.y = Utils::Lerp(myTransform.myPosition.y, aPosition.y, myLerpToPositionAcceleration * myTimerInput->GetDeltaTime());

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

void Player::BounceOnDestructibleWall()
{
	v2f dashVelocity = myBashAbility->GetVelocity();
	dashVelocity.x *= -0.8f;
}

const bool& Player::GetIsBashing()
{
	return myBashAbility->GetIsBashing();
}

void Player::Kill()
{
	myScene->GetCamera().Shake(myDieShakeDuration, myDieShakeIntensity, myDieShakeDropOff);
	myInputHandler->GetController()->Vibrate(myDieVibrationStrength, myDieVibrationStrength, myDieVibrationLength);

	SetPosition(mySpawnPosition);

	ResetVelocity();
	myBashAbility->ResetVelocity(true, true);
	myPlatformVelocity = v2f();
}

void Player::BashCollision(GameObject* aGameObject, BashComponent* aBashComponent)
{
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

void Player::ImGuiUpdate()
{
	ImGui::Begin("Player", &myIsActive, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Save to JSON"))
	{
		DataManager::GetInstance().SetDataStruct(DataEnum::player);
	}

	ImGui::SliderFloat("Max Speed", &myJsonData->myMaxSpeed, 0.0f, 2000.0f);
	ImGui::SliderFloat("Acceleration", &myAcceleration, 0.0f, 100.0f);
	ImGui::SliderFloat("Retardation", &myRetardation, 0.0f, 100.0f);
	ImGui::SliderFloat("Lerp Acceleration", &myLerpToPositionAcceleration, 0.0f, 100.0f);
	ImGui::SliderFloat("Platform Velocity Retardation", &myPlatformVelocityRetardation, 0.0f, 100.0f);
	ImGui::SliderFloat("Coyote Time", &myAirCoyoteTime, 0.0f, 1.0f);
	ImGui::SliderFloat("Jump Velocity", &myJumpVelocity, 0.0f, 2000.0f);
	ImGui::SliderFloat("Double Jump Velocity", &myDoubleJumpVelocity, 0.0f, 2000.0f);
	ImGui::SliderFloat("Max Fall Speed", &myMaxFallSpeed, 0.0f, 2000.0f);
	ImGui::SliderFloat("Ledge Jump Velocity", &myLedgeJumpVelocity, 0.0f, 2000.0f);
	ImGui::SliderFloat("Jump When Falling Time", &myJumpWhenFallingTime, 0.0f, 1.0f);

	ImGui::Text("Vibrations");
	ImGui::SliderInt("Die Vibration Strength", &myDieVibrationStrength, 0, 65000);
	ImGui::SliderInt("Land Vibration Strength", &myLandVibrationStrength, 0, 65000);
	ImGui::SliderInt("Springs Vibration Strength", &mySpringsVibrationStrength, 0, 65000);

	ImGui::SliderFloat("Die Vibration Length", &myDieVibrationLength, 0.0f, 10.0f);
	ImGui::SliderFloat("Land Vibration Length", &myLandVibrationLength, 0.0f, 10.0f);
	ImGui::SliderFloat("Springs Vibration Length", &mySpringsVibrationLength, 0.0f, 10.0f);

	ImGui::Text("Camera Shake");
	ImGui::SliderFloat("Die Shake Duration", &myDieShakeDuration, 0.0f, 10.0f);
	ImGui::SliderFloat("Die Shake Intensity", &myDieShakeIntensity, 0.0f, 10.0f);
	ImGui::SliderFloat("Die Shake DropOff", &myDieShakeDropOff, 0.0f, 10.0f);

	ImGui::SliderFloat("Land Shake Duration", &myLandingShakeDuration, 0.0f, 10.0f);
	ImGui::SliderFloat("Land Shake Intensity", &myLandingShakeIntensity, 0.0f, 10.0f);
	ImGui::SliderFloat("Land Shake DropOff", &myLandingShakeDropOff, 0.0f, 10.0f);

	ImGui::SliderFloat("Spring Shake Duration", &mySpringShakeDuration, 0.0f, 10.0f);
	ImGui::SliderFloat("Spring Shake Intensity", &mySpringShakeIntensity, 0.0f, 10.0f);
	ImGui::SliderFloat("Spring Shake DropOff", &mySpringShakeDropOff, 0.0f, 10.0f);

	ImGui::End();
}