#pragma once
#include "Platform.h"
#include "Button.h"

class MovingPlatform : public Platform
{
public:
	MovingPlatform(Scene* aLevelScene);

	void Update(const float& aDeltaTime) override;

	void Move(const float& aDeltaTime);

	void SetSpeed(const float& aSpeed);

	void AddWaypoint(const v2f& aWaypoint);
	void SetWaypoints(const std::vector<v2f>& aWaypoints);

	void ClearWaypoints();

	void OnCollision(GameObject* aGameObject) override;

private:
	Button myButton;
	std::vector<v2f> myWaypoints;
	v2f myDirection;

	float mySpeed;

	int myCurrentWayPointIndex;

};

