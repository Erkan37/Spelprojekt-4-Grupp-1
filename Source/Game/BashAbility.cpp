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
	myDashDistance = {};
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
	myAcceleration = 0.2f;
	myDashTimer = 0.5f;
	myDelayTimer = 0.3f;
	myRadiusFromDash = true;
	myDashSpeed = 1.f;
	myDashDistance = { 2000.f, 2000.f };
}

void BashAbility::Update(const float& aDeltaTime)
{
	myTimer += aDeltaTime;

	myVelocityMovement = false;

	if (myDashAbilityActive && myTimer > myDelayTimer)
	{
		UseBashAbility(aDeltaTime);
	}
	/*if (myVelocityMovement)
	{
		DashMovement(aDeltaTime);
	}*/

	CheckButtonPress();
}

void BashAbility::Render()
{
}

v2f BashAbility::GetVelocity()
{
	if (myVelocityMovement)
		return myCalculatedDash;
	else
		return v2f(0.f, 0.f);
}

void BashAbility::AddPlayerPhysics(PhysicsComponent* somePhysics)
{
	myPhysics = somePhysics;
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
	v2f dash = { leftStickPosition.x * myDashDistance.x, leftStickPosition.y * myDashDistance.y };
	Tga2D::CEngine::GetInstance()->GetErrorManager().InfoPrint(std::to_string(dash.x).c_str());
	myCalculatedDash = { dash.x + myDashSpeed * aDeltaTime, dash.y + myDashSpeed * aDeltaTime };

	myPhysics->SetVelocity({ 0.f, 0.f });
	myVelocityMovement = true;
	myDashAbilityActive = {};
	myFreezingTime = {};
	myTimer = {};
}

void BashAbility::UseBashAbility(const float& aDeltaTime)
{
	if (myButtonHold == false)
		DashUse(aDeltaTime);

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
