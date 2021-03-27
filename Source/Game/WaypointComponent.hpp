#pragma once
#include "Component.hpp"
#include "../External/Headers/CU/Vector2.hpp"

class GameObject;

class WaypointComponent : public Component
{
public:
	WaypointComponent();

	void Move(const float& aDeltaTime);

	void CheckReachedWayPoint();

	void SetNextWayPoint();

	void SetSpeed(const float& aSpeed);

	void AddWaypoint(const v2f& aWaypoint);

	void SetWaypoints(const std::vector<v2f>& aWaypoints);

	void ClearWaypoints();

	const v2f GetVelocity();

	void ResetVelocity();

	const float& GetSpeed();

	void SetOwner(GameObject* aGameObject);

	void ReverseWaypoints();
	bool IsAtLastCheckPoint();

private:
	GameObject* myOwner;

	std::vector<v2f> myWaypoints;
	v2f myDirection;


	float mySpeed;
	float myOriginalSpeed;

	int myWaypointIncrement;
	int myCurrentWayPointIndex;
	bool myLastCheckpointReached;
};

