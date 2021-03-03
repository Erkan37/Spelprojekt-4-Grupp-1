#pragma once
#include "GameObject.h"

class InputWrapper;
class LevelScene;
class AnimationComponent;

class Player : public GameObject
{
public:
	Player(LevelScene* aLevelScene);
	~Player();

	void Update(const float& aDeltaTime) override;

	void CheckJump(const float& aDeltaTime);

	void CheckMove(const float& aDeltaTime);

	void Landed() override;

private:
	std::shared_ptr<InputWrapper> myInputHandler;

	float myMaxSpeed;

	float myAcceleration;
	float myRetardation;

	float myJumpVelocity;
	float myDoubleJumpVelocity;

	bool myHasLanded;
	bool myHasDoubleJumped;
};

