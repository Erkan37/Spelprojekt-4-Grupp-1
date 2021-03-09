#pragma once
#include "GameObject.h"
#include "Animation.hpp"
#include <vector>

class LevelScene;

class Enemy : public GameObject
{
public:
	Enemy(LevelScene* aScene);
	~Enemy();
	void Update(const float& aDeltaTime) override;
	void Move(const float& aDeltaTime);
	void SetNextWayPoint();
	void SetDirection(const v2f& aDestination);
	std::vector<v2f> myWayPoints; // Get from Tiled.
	const float mySpeed = 5.0f; //Get from Data
	v2f mySize = { 1.0f, 1.0f };
	v2f myDestination;
	v2f myDirection;
	v2f myPosition;
	int myCurrentPoint = 0;
	Animation myAnimation;
};

