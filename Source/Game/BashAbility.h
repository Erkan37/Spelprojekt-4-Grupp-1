#pragma once

namespace Utils
{
	class Input;
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

private:
	std::shared_ptr<PhysicsComponent> myPhysics;
	std::shared_ptr<InputWrapper> myInput;

	bool myDashAbilityActive;
	bool myButtonHold;
	bool myRadiusFromDash;

	float myTimer;
	float myDelayTimer;
	float myDashSpeed;
	v2f myDashDistance;

	void UseBashAbility(const float& aDeltaTime);
	void CheckButtonPress();

};

