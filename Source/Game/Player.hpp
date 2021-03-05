#pragma once
#include "GameObject.h"
#include "Animation.hpp"
#include "BashAbility.h"

namespace Utils
{
	class Input;
}

class InputWrapper;
class LevelScene;
class AnimationComponent;

class Player : public GameObject
{
public:
	Player(LevelScene* aLevelScene);
	~Player();

	void InitAnimations();
	void InitCollider();

	void Update(const float& aDeltaTime) override;

	void CheckJump();

	void UpdateCoyoteTime(const float& aDeltaTime);

	void TryLetJumpWhenFalling(const float& aYDistance);

	void CheckMove(const float& aDeltaTime);

	void GoRight(const float& aDeltaTime);
	void GoLeft(const float& aDeltaTime);

	void Jump();
	void DoubleJump();

	void Landed(const int& aOverlapY) override;

	void AnimationState();

	void UpdatePlayerVelocity(const float& aDeltaTime);

	void ImGuiUpdate();

private:
	Animation myAnimations[3];

	std::shared_ptr<InputWrapper> myInputHandler;
	std::unique_ptr<BashAbility> myBashAbility;

	v2f myCurrentVelocity;

	float myAirCoyoteTime;
	float myAirCoyoteTimer;

	float myMaxRunningSpeed;

	float myAcceleration;
	float myRetardation;

	float myJumpVelocity;
	float myDoubleJumpVelocity;

	float myJumpWhenFallingTime;

	int myCurrentAnimationIndex;

	bool myHasLanded;
	bool myHasDoubleJumped;

	bool myCanJumpWhenFalling;
	bool myWillJumpWhenFalling;
};

