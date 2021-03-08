#pragma once
#include "../External/Headers/CU/Vector2.hpp"
#include "GameObject.h"
#include <vector>

class Scene;

class Platform : public GameObject
{
public:
	Platform(Scene* aScene);
	~Platform();

	void Init(const v2f& aSize, const v2f& aSpriteSize, const v2f& aPosition, const float& aSpeed, const bool& aIsOneway);

	void Update(const float& aDeltaTime) override;

	void Move(const float& aDeltaTime);

	void AddWaypoint(const v2f& aWaypoint);
	void SetWaypoints(const std::vector<v2f>& aWaypoints);

	void ClearWaypoints();

	void OnCollision(GameObject* aGameObject) override;

private:
	std::vector<v2f> myWaypoints;
	v2f myDirection;
	
	float mySpeed;
	
	int myCurrentWayPointIndex;

};

