#pragma once
#include "GameObject.h"
#include "Animation.hpp"
#include <vector>

class LevelScene;

class Enemy : public GameObject
{
public:
	Enemy(LevelScene* aScene);
	Enemy(Scene* aScene, const std::vector<v2f>& someCoordinates);
	~Enemy();
	void Update(const float& aDeltaTime) override;
	void OnCollision(GameObject* aGameObject) override;
private:
	void InitAnimations();
	void InitCollider();
	void Move(const float& aDeltaTime);
	void SetNextWayPoint();
	void SetDirection(const v2f& aDestination);
	std::vector<v2f> myWayPoints; // Get from Tiled.
	const float mySpeed = 200; //Get from Json
	v2f mySize = { 150.0f, 100.0f }; // Get from Json
	v2f myDestination;
	v2f myDirection;
	int myCurrentPoint = 1;
	Animation myAnimation;
};

class ShootingEnemy : public Enemy, GameObject
{

};

