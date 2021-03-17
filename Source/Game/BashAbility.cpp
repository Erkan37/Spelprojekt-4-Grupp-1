#include "stdafx.h"
#include "Player.hpp"
#include "BashAbility.h"
#include "SpriteComponent.h"
#include "InputWrapper.h"
#include "LevelScene.h"

#include <iostream>


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

	myVibrationStrength = 60000;
	myVibrationLength = 0.25f;

	myDashShakeDuration = 0.5f;
	myDashShakeIntensity = 0.5f;
	myDashShakeDropOff = 0.5f;
}

BashAbility::~BashAbility()
{
}

void BashAbility::Init()
{
	SetZIndex(1000);
	SetPivot(v2f(0.5f, 0.5f));

	myAcceleration = 100.0f;
	myRetardation = 2.0f;
	myDashDuration = 0.15f;
	myMaxDashDuration = 2.0f;
	myTimeScale = 0.0f;
	myRadiusFromDash = true;
	myDashSpeed = 400.0f;
	myAspectRatioFactorY = Tga2D::CEngine::GetInstance()->GetWindowSize().x / Tga2D::CEngine::GetInstance()->GetWindowSize().y;

	SpriteComponent* sprite = AddComponent<SpriteComponent>();
	sprite->SetSpritePath("BashArrow.dds");
	sprite->SetSize(v2f(16.0f, 16.0f));
	//sprite->Deactivate();

	GameObject::Init();
}

void BashAbility::Update(const float& aDeltaTime)
{
	if (myDashAbilityActive)
	{
		UseBashAbility(aDeltaTime);
	}

	UpdateBashVelocity(aDeltaTime);

	CheckButtonPress();

	if (myPlayer)
	{
		SetPosition(myPlayer->GetPosition());
	}

	GameObject::Update(aDeltaTime);

#ifdef _DEBUG
	ImGuiUpdate();
#endif //DEBUG
}

void BashAbility::UpdateBashVelocity(const float& aDeltaTime)
{
	myTimer -= aDeltaTime;
	if (myTimer > 0)
	{
		myCurrentDashVelocity.x = Utils::Lerp(myCurrentDashVelocity.x, myUsedDashDirection.x * myDashSpeed, myAcceleration * aDeltaTime);
		myCurrentDashVelocity.y = Utils::Lerp(myCurrentDashVelocity.y, myUsedDashDirection.y * myDashSpeed, myAcceleration * aDeltaTime) * myAspectRatioFactorY;
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

	ImGui::InputFloat("Acceleration: ", &myAcceleration, 0.0f, 100.0f);
	ImGui::InputFloat("Retardation: ", &myRetardation, 0.0f, 5.0f);
	ImGui::InputFloat("Dash Speed: ", &myDashSpeed, 0.0f, 3000.0f);
	ImGui::InputFloat("Dash Duration: ", &myDashDuration, 0.0f, 10.0f);
	ImGui::InputFloat("Max Dash Duration: ", &myMaxDashDuration, 0.0f, 10.0f);

	ImGui::Text("Vibration");
	ImGui::InputInt("Vibration Strength: ", &myVibrationStrength, 0, 65000);
	ImGui::InputFloat("Vibration Length: ", &myVibrationLength, 0.0f, 1.0f);

	ImGui::Text("Camera Shake");
	ImGui::InputFloat("Dash Shake Duration: ", &myDashShakeDuration, 0.0f, 10.0f);
	ImGui::InputFloat("Dash Shake Intensity: ", &myDashShakeIntensity, 0.0f, 10.0f);
	ImGui::InputFloat("Dash Shake DropOff: ", &myDashShakeDropOff, 0.0f, 10.0f);

	ImGui::End();
}

void BashAbility::FreezeTime()
{
	myTimerInput->SetTimeScale(myTimeScale);
}

void BashAbility::DashUse(const float& aDeltaTime)
{
	myUsedDashDirection = myInput->GetAxisMovement();
	if (myUsedDashDirection.x == 0.0f && myUsedDashDirection.y == 0.0f)
	{
		myUsedDashDirection = v2f(0.0f, -1.0f);
	}

	myScene->GetCamera().Shake(myDashShakeDuration, myDashShakeIntensity, myDashShakeDropOff);
	myInput->GetController()->Vibrate(myVibrationStrength, myVibrationStrength, myVibrationLength);

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

	UpdateBashArrow();

	if (myButtonHold == false || myMaxDashDurationTimer <= 0)
	{
		DashUse(aDeltaTime);
		//GetComponent<SpriteComponent>()->Deactivate();
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
		GetComponent<SpriteComponent>()->Activate();
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

void BashAbility::UpdateBashArrow()
{
	myDashDirection = myInput->GetAxisMovement();
	if (myDashDirection.x == 0.0f && myDashDirection.y == 0.0f)
	{
		myDashDirection = v2f(0.0f, -1.0f);
	}

	SetPosition(myPlayer->GetPosition() + myDashDirection * 32.0f);
	SetRotation(atan2(myDashDirection.y, myDashDirection.x));
}