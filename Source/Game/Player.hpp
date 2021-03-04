#pragma once
#include "GameObject.h"
#include "Animation.hpp"

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

	void Update(const float& aDeltaTime) override;

	void CheckJump();

	void CheckMove(const float& aDeltaTime);

	void Landed(const int& aOverlapY) override;

	void AnimationState();

private:
	Animation myAnimations[3];

	std::shared_ptr<InputWrapper> myInputHandler;

	float myMaxSpeed;

	float myAcceleration;
	float myRetardation;

	float myJumpVelocity;
	float myDoubleJumpVelocity;

	int myCurrentAnimationIndex;

	bool myHasLanded;
	bool myHasDoubleJumped;
};

