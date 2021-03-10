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
class Ledge;
class BashComponent;

class Player : public GameObject
{
public:
	Player(LevelScene* aLevelScene);
	~Player();

	void InitAnimations();
	void InitCollider();
	void InitVibrations();

	void Update(const float& aDeltaTime) override;

	void CheckJump();

	void UpdateCoyoteTime(const float& aDeltaTime);

	void TryLetJumpWhenFalling(const float& aYDistance);

	void CheckMove(const float& aDeltaTime);

	void GoRight(const float& aDeltaTime);
	void GoLeft(const float& aDeltaTime);

	void Jump();
	void DoubleJump();
	void LedgeJump();

	void ReactivateDoubleJump();

	void Landed(const int& aOverlapY) override;
	void SideCollision(const int& aOverlapX) override;

	void ResetVelocity();

	const v2f GetPlatformVelocity();
	void SetPlatformVelocity(const v2f& aPlatformVelocity);

	void AnimationState();

	void UpdatePlayerVelocity(const float& aDeltaTime);

	void GrabLedge(const v2f& aLedgeLerpPosition, const v2f& aLedgePosition);
	void LeaveLedge();
	const bool GetLedgeIsGrabbed();

	void LerpToPosition(const v2f& aPosition, const float& aDeltaTime);
	void SetLerpPosition(const v2f& aPosition);
	void EndLerp();

	void BounceOnDestructibleWall();
	const bool& GetIsBashing();

	void Kill();

	void BashCollision(GameObject* aGameObject, BashComponent* aBashComponent) override;

	void ImGuiUpdate();

private:
	Animation myAnimations[3];

	std::shared_ptr<InputWrapper> myInputHandler;
	std::unique_ptr<BashAbility> myBashAbility;

	Utils::Timer* myTimerInput;

	v2f myCurrentVelocity;

	v2f myPlatformVelocity;

	v2f myLerpPosition;

	v2f mySize;

	v2f mySpawnPosition;

	float myAirCoyoteTime;
	float myAirCoyoteTimer;

	float myMaxRunningSpeed;
	float myRunningAnimationSpeed;

	float myAcceleration;
	float myRetardation;
	float myLerpToPositionAcceleration;
	float myPlatformVelocityRetardation;

	float myJumpVelocity;
	float myDoubleJumpVelocity;
	float myLedgeJumpVelocity;

	float myMaxFallSpeed;

	float myJumpWhenFallingTime;

	float myDieVibrationLength;
	float myLandVibrationLength;
	float mySpringsVibrationLength;

	int myDieVibrationStrength;
	int myLandVibrationStrength;
	int mySpringsVibrationStrength;

	int myCurrentAnimationIndex;

	bool myHasLanded;
	bool myHasLandedVibration;
	bool myHasDoubleJumped;

	bool myCanJumpWhenFalling;
	bool myWillJumpWhenFalling;

	bool myGrabbedLedge;

	bool myIsLerpingToPosition;
};

