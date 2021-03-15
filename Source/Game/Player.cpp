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

#include "Collectible.hpp"

#include "Ledge.h"

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

	myBashAbility = std::make_unique<BashAbility>(aLevelScene);
	myBashAbility->Init();
	myBashAbility->AddInputWrapper(world->Input());
	myBashAbility->AddPlayerRelation(this);
	myBashAbility->AddTimer(world->GetTimer());

	SetZIndex(500);
	SetPosition({ 700.0f, 640.0f });

	SetPivot(v2f(0.5f, 0.5f));

	mySpawnPosition = v2f(700.0f, 640.0f);
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

	myAnimations[0] = Animation(false, false, false, 0, 74, 74, 0.08f, spriteIdle, 16, 16);
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

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetSize(7.0f, 12.0f);
	collider->SetPosition(v2f(0.0f, 2.0f));
}

void Player::Update(const float& aDeltaTime)
{
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

	if (myCurrentVelocity.y > myJsonData->myFloatValueMap[PEnum::Trigger_Falling_Speed])
	{
		myHasLanded = false;
	}

	myPlatformVelocity.x = Utils::Lerp(myPlatformVelocity.x, 0.0f, myJsonData->myFloatValueMap[PEnum::Platform_Velocity_Retardation] * aDeltaTime);
	myPlatformVelocity.y = Utils::Lerp(myPlatformVelocity.y, 0.0f, myJsonData->myFloatValueMap[PEnum::Platform_Velocity_Retardation] * aDeltaTime);

	if (myActiveSpringJump)
		DecreaseSpringJump(aDeltaTime);
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

	myDirectionX = 1;
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

	myDirectionX = -1;
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


		if (myWillJumpWhenFalling)
		{
			Jump();
		}
	}
	myCurrentVelocity.y = 0.0f;
	myBashAbility->ResetVelocity(false, true);
	if (!myHasLandedOnSpring)
		mySpringVelocity.y = {};
}

void Player::SideCollision(const int& aOverlapX)
{
	aOverlapX;
	myCurrentVelocity.x = 0.0f;
	myBashAbility->ResetVelocity(true, false);
	mySpringVelocity = {};
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
		animation->SetAnimation(&myAnimations[4]);
		myCurrentAnimationIndex = 4;
	}

	for (Animation& animation : myAnimations)
	{
		animation.mySpriteComponent->SetSizeX(mySize.x * myDirectionX);
	}
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

void Player::LerpToPosition(const v2f& aPosition)
{
	const float timeScale = myTimerInput->GetTimeScale();;

	myTimerInput->SetTimeScale(1.0f);

	myTransform.myPosition.x = Utils::Lerp(myTransform.myPosition.x, aPosition.x, myJsonData->myFloatValueMap[PEnum::Lerp_Acceleration] * myTimerInput->GetDeltaTime());
	myTransform.myPosition.y = Utils::Lerp(myTransform.myPosition.y, aPosition.y, myJsonData->myFloatValueMap[PEnum::Lerp_Acceleration] * myTimerInput->GetDeltaTime());

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
	mySpringVelocityRetardation = aRetardation;
	mySpringVelocity.y = aSpringVelocity;
}
void Player::BounceOnDestructibleWall()
{
	v2f dashVelocity = myBashAbility->GetVelocity();
	dashVelocity.x *= -0.8f;
}

void Player::Kill()
{
	KillReset();
	Respawn();
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
	myPlatformVelocity = v2f();
	Deactivate();
}

void Player::Respawn()
{
	SetPosition(mySpawnPosition);
	Activate();
}

const bool& Player::GetIsBashing()
{
	return myBashAbility->GetIsBashing();
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

void Player::AddCollectible(Collectible* aCollectible)
{
	myCollectibles.push_back(aCollectible);
}

std::vector<Collectible*> Player::GetCollectibles()
{
	return myCollectibles;
}

void Player::ClearCollectibles(const bool aIsTurningIn)
{
	if (aIsTurningIn)
	{
		myCollectibles.clear();
	}
	else
	{
		for (int collectible = static_cast<int>(myCollectibles.size()) - 1; collectible >= 0; --collectible)
		{
			myCollectibles[collectible]->Reset(false);
		}
	}
	
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
