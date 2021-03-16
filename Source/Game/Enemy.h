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
	virtual ~Enemy()
	{

	}

	void InitEnemy(const std::vector<v2f>& someCoordinates, const float& aSpeed);
	virtual void Update(const float& aDeltaTime) = 0;
	void OnCollision(GameObject* aGameObject) override;

protected:
	EnemyData* myJsonData = new EnemyData();
	bool IsMoving = false;
	WaypointComponent* myWayPointComponent;

private:
	void InitCollider();
	float mySpeed = 200;

};

class NormalEnemy : public Enemy
{
public:
	NormalEnemy(Scene* aScene);
	~NormalEnemy() = default;

	void Update(const float& aDeltaTime);

private:
	v2f mySize = { 150.0f, 100.0f }; // Get from Json
};

class ShootingEnemy : public Enemy
{
public:
	ShootingEnemy(Scene* aScene);
	~ShootingEnemy() = default;

	void Update(const float& aDeltaTime);

protected:
#ifdef _DEBUG
	void ImGuiUpdate();
#endif // _DEBUG

private:
	void Shoot();
	const float myFireRate = 4.0f; // Imgui
	v2f mySize = { 40.0f, 50.0f }; // Get from Json
	const float myRadius = 250.0f; // imGui?
	float myShotTimer = 0.0f;
};
