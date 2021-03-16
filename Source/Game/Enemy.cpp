#include "stdafx.h"
#include "LevelScene.h"
#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "Player.hpp"
#include "EnemyProjectile.h"
#include "Enemy.h"
#include "WaypointComponent.hpp"

Enemy::Enemy(Scene* aScene) : GameObject(aScene)
{
}

Enemy::~Enemy()
{
}

void Enemy::InitEnemy(const std::vector<v2f>& someWayPoints, const float& aSpeed)
{
	if (someWayPoints.size() > 1)
	{
		myWayPointComponent = AddComponent<WaypointComponent>();
		myWayPointComponent->SetOwner(this);
		myWayPointComponent->SetWaypoints(someWayPoints);
		myWayPointComponent->SetSpeed(aSpeed);
		IsMoving = true;
		mySpeed = aSpeed;
	}
	if (someWayPoints.size() == 0)
	{
		this->SetPosition({ 0.0f, 0.0f });
	}
	else
	{
		this->SetPosition(someWayPoints[0]);
	}
	//InitAnimations();
	InitCollider();
}

void Enemy::Update(const float& aDeltaTime)
{
	if (IsMoving)
	{
		myWayPointComponent->Move(aDeltaTime);
	}
	GameObject::Update(aDeltaTime);
}

void Enemy::InitCollider()
{
	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(false);

	physics->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this);
}

void Enemy::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		player->Kill();
	}
}

NormalEnemy::NormalEnemy(Scene* aScene) : Enemy(aScene)
{
	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/TempEnemy.dds");
	spriteIdle->SetSize(mySize);
	this->SetZIndex(400);
}

ShootingEnemy::ShootingEnemy(Scene* aScene) : Enemy(aScene)
{
	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/TempShootingEnemy.dds");
	spriteIdle->SetSize(mySize);
	this->SetZIndex(400);
}

void ShootingEnemy::Update(const float& aDeltaTime)
{
	Enemy::Update(aDeltaTime);
	v2f lengthToPlayer = dynamic_cast<LevelScene*>(this->myScene)->GetPlayer()->GetPosition() - this->GetPosition();
	if (lengthToPlayer.Length() <= myRadius)
	{
		myShotTimer -= aDeltaTime;
		if (myShotTimer <= 0)
		{
			myShotTimer = myFireRate;
			Shoot();
		}
	}
}

void ShootingEnemy::Shoot()
{
	EnemyProjectile* projectile = new EnemyProjectile(this->myScene);
	projectile->InitProjectile(this->GetPosition(), dynamic_cast<LevelScene*>(this->myScene)->GetPlayer()->GetPosition());
}