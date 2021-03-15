#pragma once
#include "GameObject.h"
#include "Animation.hpp"
#include <vector>

class LevelScene;
class EnemyProjectile;

class Enemy : public GameObject
{
public:
	Enemy(Scene* aScene);
	Enemy(Scene* aScene, const std::vector<v2f>& someCoordinates);
	~Enemy();
	void InitEnemy(const std::vector<v2f>& someCoordinates);
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
	bool IsMoving = false;
};

class NormalEnemy : public Enemy
{
public:
	NormalEnemy(Scene* aScene);
	~NormalEnemy() = default;
private:
	v2f mySize = { 150.0f, 100.0f }; // Get from Json
};

class ShootingEnemy : public Enemy
{
public:
	ShootingEnemy(Scene* aScene);
	//ShootingEnemy(Scene* aScene, const std::vector<v2f>& someCoordinates);
	void Update(const float& aDeltaTime);
private:
	void Shoot();
	const float myFireRate = 4.0f;
	float myShotTimer = 0.0f;
	v2f mySize = { 40.0f, 50.0f }; // Get from Json
	bool myHasShot = false;
};

