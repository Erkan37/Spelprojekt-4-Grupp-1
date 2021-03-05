#pragma once

namespace Utils
{
	class Input;
	class Timer;
}

class LevelScene;
class InputWrapper;
class Player;
class PhysicsComponent;

class BashAbility : public GameObject
{
public:
	BashAbility(LevelScene* aLevelScene);
	~BashAbility();

	void Init();

	void Update(const float& aDeltaTime);
	void Render();

	void AddPlayerPhysics(const std::shared_ptr<PhysicsComponent> somePhysics);
	void AddInputWrapper(const std::shared_ptr<InputWrapper> aInputWrapper);
	void AddTimer(Utils::Timer* aTimer);

private:
	std::shared_ptr<PhysicsComponent> myPhysics;
	std::shared_ptr<InputWrapper> myInput;
	Utils::Timer* myTimerInput;

	bool myFreezingTime;
	bool myDashAbilityActive;
	bool myButtonHold;
	bool myRadiusFromDash;
	bool myVelocityMovement;

	float myTimer;
	float myDashTimer;
	float myDelayTimer;
	float myDashSpeed;
	float myAcceleration;

	v2f myCalculatedDash;
	v2f myDashDistance;

	bool FreezeTime();
	void DashUse(const float& aDeltaTime);
	void UseBashAbility(const float& aDeltaTime);
	void DashMovement(const float& adeltaTime);
	void CheckButtonPress();

};

