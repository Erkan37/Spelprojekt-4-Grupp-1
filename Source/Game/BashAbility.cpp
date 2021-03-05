#include "stdafx.h"
#include "Player.hpp"
#include "BashAbility.h"
#include "PhysicsComponent.h"
#include "InputWrapper.h"
#include "LevelScene.h"


BashAbility::BashAbility(LevelScene* aLevelScene) 
	:
	GameObject(aLevelScene)
{
	myDashAbilityActive = {};
	myDashSpeed = {};
	myRadiusFromDash = {};
	myButtonHold = {};
	myDelayTimer = {};
	myTimer = {};
	myDashTimer = {};
	myFreezingTime = {};
	myVelocityMovement = {};
	myAcceleration = {};
}

BashAbility::~BashAbility()
{
}

void BashAbility::Init()
{
	myAcceleration = 10.0f;
	myRetardation = 3.0f;
	myDashTimer = 0.5f;
	myDelayTimer = 0.3f;
	myRadiusFromDash = true;
	myVelocityMovement = false;
	myDashSpeed = 1000.f;
	myAspectRatioFactorY = Tga2D::CEngine::GetInstance()->GetWindowSize().x / Tga2D::CEngine::GetInstance()->GetWindowSize().y;
}

void BashAbility::Update(const float& aDeltaTime)
{
	myTimer += aDeltaTime;

	if (myDashAbilityActive)
	{
		UseBashAbility(aDeltaTime);
	}

	UpdateBashVelocity(aDeltaTime);

	CheckButtonPress();
}

void BashAbility::UpdateBashVelocity(const float& aDeltaTime)
{
	if (myVelocityMovement)
	{
		myCurrentDashVelocity.x = Utils::Lerp(myCurrentDashVelocity.x, myDashDirection.x * myDashSpeed, myAcceleration * aDeltaTime);
		myCurrentDashVelocity.y = Utils::Lerp(myCurrentDashVelocity.y, myDashDirection.y * myDashSpeed, myAcceleration * aDeltaTime) * myAspectRatioFactorY;

		if (Utils::Abs(myCurrentDashVelocity.x) + 1.0f >= Utils::Abs(myDashDirection.x * myDashSpeed) || (Utils::Abs(myCurrentDashVelocity.y) + 1.0f) * myAspectRatioFactorY >= Utils::Abs(myDashDirection.y * myDashSpeed) * myAspectRatioFactorY)
		{
			myVelocityMovement = false;
		}
	}
	else
	{
		myCurrentDashVelocity.x = Utils::Lerp(myCurrentDashVelocity.x, 0.0f, myRetardation * aDeltaTime);
		myCurrentDashVelocity.y = Utils::Lerp(myCurrentDashVelocity.y, 0.0f, myRetardation * aDeltaTime);
	}
}

void BashAbility::Render()
{
}

v2f BashAbility::GetVelocity()
{
	return myCurrentDashVelocity;
}

void BashAbility::ResetVelocity()
{
	myCurrentDashVelocity.x = 0;
	myCurrentDashVelocity.y = 0;
	myVelocityMovement = false;
}

void BashAbility::AddPlayerRelation(Player* aPlayer)
{
	myPlayer = aPlayer;
}

void BashAbility::AddInputWrapper(const std::shared_ptr<InputWrapper> aInputWrapper)
{
	myInput = aInputWrapper;
}

void BashAbility::AddTimer(Utils::Timer* aTimer)
{
	myTimerInput = aTimer;
}

bool BashAbility::FreezeTime()
{
	myTimerInput->SetFreezeTime(myFreezingTime);
	return myFreezingTime;
}

void BashAbility::DashUse(const float& aDeltaTime)
{
	v2f leftStickPosition = myInput->GetLeftStickMovement();
	v2f dash = { leftStickPosition.x, leftStickPosition.y };
	Tga2D::CEngine::GetInstance()->GetErrorManager().InfoPrint(std::to_string(dash.x).c_str());
	myDashDirection = dash.GetNormalized();

	myPlayer->ResetVelocity();
	myPlayer->ReactivateDoubleJump();
	ResetVelocity();

	//myPhysics->SetVelocity({ 0.f, 0.f });
	myVelocityMovement = true;
	myDashAbilityActive = {};
	myFreezingTime = {};
	myTimer = {};
}

void BashAbility::UseBashAbility(const float& aDeltaTime)
{
	if (myButtonHold == false)
	{
		DashUse(aDeltaTime);
	}

	FreezeTime();
}

//void BashAbility::DashMovement(const float& adeltaTime)
//{
//	if (myDashTimer > myTimer)
//	{
//		myCalculatedDash.x = Utils::Lerp(myCalculatedDash.x, 0.f, myAcceleration * adeltaTime);
//		myCalculatedDash.y = Utils::Lerp(myCalculatedDash.y, 0.f, myAcceleration * adeltaTime);
//
//		Tga2D::CEngine::GetInstance()->GetErrorManager().InfoPrint(std::to_string(myCalculatedDash.x).c_str());
//
//		myPhysics->SetDashVelocity(myCalculatedDash);
//	}
//	else
//	{
//		myPhysics->SetDashVelocity({ 0.f, 0.f });
//		myVelocityMovement = false;
//	}
//}

void BashAbility::CheckButtonPress()
{
	if (myInput->IsDashing() && myRadiusFromDash)
	{
		myButtonHold = true;
		myDashAbilityActive = true;
		myFreezingTime = true;
	}
	else
		myButtonHold = false;
}
