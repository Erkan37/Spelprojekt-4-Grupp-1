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
}

BashAbility::~BashAbility()
{
}

void BashAbility::Init()
{
	myRadiusFromDash = true;
	myDashSpeed = 50.f;
	myDashDistance = { 500.f, 500.f };
}

void BashAbility::Update(const float& aDeltaTime)
{
	if (myDashAbilityActive)
	{
		UseBashAbility(aDeltaTime);
	}

	CheckButtonPress();
}

void BashAbility::Render()
{
}

void BashAbility::AddPlayerPhysics(std::shared_ptr<PhysicsComponent> somePhysics)
{
	myPhysics = somePhysics;
}

void BashAbility::AddInputWrapper(const std::shared_ptr<InputWrapper> aInputWrapper)
{
	myInput = aInputWrapper;
}

void BashAbility::UseBashAbility(const float& aDeltaTime)
{
	if (myInput->GetLeftPullForce() && myButtonHold == false)
	{
		v2f leftStickPosition = myInput->GetLeftStickMovement();
		v2f dash = { leftStickPosition.x * myDashDistance.x, leftStickPosition.y * myDashDistance.y };

		v2f calculatedDash = { dash.x + myDashSpeed * aDeltaTime, dash.y + myDashSpeed * aDeltaTime };
		myPhysics->SetVelocity(myPhysics->GetVelocity() + calculatedDash);
		myButtonHold = true;
		myDashAbilityActive = false;
	}
}

void BashAbility::CheckButtonPress()
{
	if (myInput->IsDashing() && myRadiusFromDash)
	{
		myButtonHold = true;
		myDashAbilityActive = true;
	}
	else
		myButtonHold = false;
}
