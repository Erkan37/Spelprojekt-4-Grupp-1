#pragma once
#include "Component.hpp"
#include "../External/Headers/CU/Vector2.hpp"

class GameObject;

class WaypointComponent : public Component
{
public:
	void Move(const float& aDeltaTime);

	void CheckReachedWayPoint();

	void SetNextWayPoint();

	void SetSpeed(const float& aSpeed);

	void AddWaypoint(const v2f& aWaypoint);

	void SetWaypoints(const std::vector<v2f>& aWaypoints);

	void ClearWaypoints();

	const v2f GetVelocity();

	void SetOwner(GameObject* aGameObject);

private:
	GameObject* myOwner;

	std::vector<v2f> myWaypoints;
	v2f myDirection;

	float mySpeed;

	int myCurrentWayPointIndex;

};

