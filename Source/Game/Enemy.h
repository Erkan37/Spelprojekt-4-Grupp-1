#pragma once
#include "GameObject.h"
#include "Animation.hpp"
#include "DataManager.h"
#include <vector>

class LevelScene;
class EnemyProjectile;
class WaypointComponent;

class Enemy : public GameObject
{
public:
	Enemy(Scene* aScene);
	~Enemy();
	void InitEnemy(const std::vector<v2f>& someCoordinates, const float& aSpeed);
	void Update(const float& aDeltaTime) override;
	void OnCollision(GameObject* aGameObject) override;
	virtual void InitCollider();
private:
	float mySpeed = 200;
	bool IsMoving = false;
	WaypointComponent* myWayPointComponent;
};

class NormalEnemy : public Enemy
{
public:
	NormalEnemy(Scene* aScene);
	~NormalEnemy() = default;
private:
	void InitCollider() override;
	v2f mySize = { 150.0f, 100.0f }; // Get from Json
	v2f myColliderSize = { 150.0f, 100.0f }; // Get from Json
};

class ShootingEnemy : public Enemy
{
public:
	ShootingEnemy(Scene* aScene);
	void Update(const float& aDeltaTime);

private:
	void InitCollider() override;
	void Shoot();
	const float myFireRate = 4.0f; // Imgui
	v2f mySpriteSize = { 40.0f, 50.0f }; // Get from Json
	v2f myColliderSize = { 40.0f, 50.0f }; // Get from Json
	const float myRadius = 250.0f; // imGui?
	float myShotTimer = 0.0f;
};

