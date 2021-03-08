#pragma once

namespace Utils
{
	class Input;
	class Timer;
}

class LevelScene;
class InputWrapper;
class Player;

class BashAbility : public GameObject
{
public:
	BashAbility(LevelScene* aLevelScene);
	~BashAbility();

	void Init();

	void Update(const float& aDeltaTime);
	void UpdateBashVelocity(const float& aDeltaTime);
	void Render();

	v2f GetVelocity();

	void ResetVelocity(const bool aResetX, const bool aResetY);

	void AddPlayerRelation(Player* aPlayer);
	void AddInputWrapper(const std::shared_ptr<InputWrapper> aInputWrapper);
	void AddTimer(Utils::Timer* aTimer);

	const bool GetIsBashing();

	void ImGuiUpdate();

private:
	std::shared_ptr<InputWrapper> myInput;
	
	Player* myPlayer;
	Utils::Timer* myTimerInput;

	float myTimeScale;

	bool myDashAbilityActive;
	bool myButtonHold;
	bool myRadiusFromDash;
	bool myIsBashing;
	bool myLMBMousePressed;

	float myTimer;
	float myDashDuration;
	float myDelayTimer;
	float myDashSpeed;
	float myAcceleration;
	float myRetardation;

	float myAspectRatioFactorY;

	v2f myDashDirection;
	v2f myCurrentDashVelocity;

	void FreezeTime();
	void DashUse(const float& aDeltaTime);
	void UseBashAbility(const float& aDeltaTime);
	void CheckButtonPress();

};

