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
	myMaxDashDuration = 2.0f;
	myMaxDashDurationTimer = myMaxDashDuration;
	myDashDuration = 1.0f;
	myTimer = myDashDuration;
	myTimeScale = 0.0f;
	myIsBashing = false;
	myAcceleration = {};
	myLMBMousePressed = {};
	myBashObject = nullptr;
}

BashAbility::~BashAbility()
{
}

void BashAbility::Init()
{
	myAcceleration = 10.0f;
	myRetardation = 1.0f;
	myDashDuration = 0.5f;
	myMaxDashDuration = 2.0f;
	myTimeScale = 0.0f;
	myRadiusFromDash = true;
	myDashSpeed = 1000.f;
	myAspectRatioFactorY = Tga2D::CEngine::GetInstance()->GetWindowSize().x / Tga2D::CEngine::GetInstance()->GetWindowSize().y;
}

void BashAbility::Update(const float& aDeltaTime)
{
	if (myDashAbilityActive)
	{
		UseBashAbility(aDeltaTime);
	}

	UpdateBashVelocity(aDeltaTime);

	CheckButtonPress();

#ifdef _DEBUG
	ImGuiUpdate();
#endif //DEBUG
}

void BashAbility::UpdateBashVelocity(const float& aDeltaTime)
{
	myTimer -= aDeltaTime;
	if (myTimer > 0)
	{
		myCurrentDashVelocity.x = Utils::Lerp(myCurrentDashVelocity.x, myDashDirection.x * myDashSpeed, myAcceleration * aDeltaTime);
		myCurrentDashVelocity.y = Utils::Lerp(myCurrentDashVelocity.y, myDashDirection.y * myDashSpeed, myAcceleration * aDeltaTime) * myAspectRatioFactorY;
		myIsBashing = true;
	}
	else if(myTimer <= 0)
	{
		myTimer = 0;
		myCurrentDashVelocity.x = Utils::Lerp(myCurrentDashVelocity.x, 0.0f, myRetardation * aDeltaTime);
		myCurrentDashVelocity.y = Utils::Lerp(myCurrentDashVelocity.y, 0.0f, myRetardation * aDeltaTime);
		myIsBashing = false;
	}
}

void BashAbility::Render()
{
}

v2f BashAbility::GetVelocity()
{
	return myCurrentDashVelocity;
}

void BashAbility::SetVelocity(const v2f& aDashVelocity)
{
	myCurrentDashVelocity = aDashVelocity;
}

void BashAbility::ResetVelocity(const bool aResetX, const bool aResetY)
{
	if (aResetX)
	{
		myCurrentDashVelocity.x = 0;
	}

	if (aResetY)
	{
		myCurrentDashVelocity.y = 0;
		myTimer = 0.0f;
	}
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

void BashAbility::ImGuiUpdate()
{
	ImGui::Begin("Dash", &myIsActive, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::SliderFloat("Acceleration: ", &myAcceleration, 0.0f, 100.0f);
	ImGui::SliderFloat("Retardation: ", &myRetardation, 0.0f, 5.0f);
	ImGui::SliderFloat("Dash Speed: ", &myDashSpeed, 0.0f, 3000.0f);
	ImGui::SliderFloat("Dash Duration: ", &myDashDuration, 0.0f, 10.0f);
	ImGui::SliderFloat("Max Dash Duration: ", &myMaxDashDuration, 0.0f, 10.0f);

	ImGui::End();
}

void BashAbility::FreezeTime()
{
	myTimerInput->SetTimeScale(myTimeScale);
}

void BashAbility::DashUse(const float& aDeltaTime)
{
	myDashDirection = myInput->GetAxisMovement();
	if (myDashDirection.x == 0.0f && myDashDirection.y == 0.0f)
	{
		myDashDirection = v2f(0.0f, -1.0f);
	}

	myPlayer->ResetVelocity();
	myPlayer->ReactivateDoubleJump();
	ResetVelocity(true, true);

	myDashAbilityActive = {};
	myTimerInput->SetTimeScale(1.0f);
	myTimer = myDashDuration;
	myMaxDashDurationTimer = myMaxDashDuration;

	myBashObject->OnBashed();
	myBashObject = nullptr;
}

void BashAbility::UseBashAbility(const float& aDeltaTime)
{
	myTimerInput->SetTimeScale(1.0f);
	myMaxDashDurationTimer -= myTimerInput->GetDeltaTime();
	myTimerInput->SetTimeScale(myTimeScale);

	if (myButtonHold == false || myMaxDashDurationTimer <= 0)
	{
		DashUse(aDeltaTime);
		myPlayer->EndLerp();
	}
}


void BashAbility::CheckButtonPress()
{
	if (myPlayer->GetLedgeIsGrabbed())
	{
		return;
	}

	if (myInput->IsDashing() && myBashObject)
	{
		myButtonHold = true;
		myDashAbilityActive = true;
		FreezeTime();
	}
	else if (myInput->IsDashingReleased())
		myButtonHold = false;


}

const bool BashAbility::GetIsBashing()
{
	return myIsBashing;
}

void BashAbility::ActivateBash(GameObject* aGameObject)
{
	myBashObject = aGameObject;
}