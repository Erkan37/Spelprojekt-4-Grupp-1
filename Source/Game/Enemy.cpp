#include "stdafx.h"
#include "LevelScene.h"
#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include <iostream>
#include "Enemy.h"

Enemy::Enemy(LevelScene* aScene) : GameObject(aScene)
{
	myWayPoints.push_back({ 0.0f, 550.0f });
	myWayPoints.push_back({ 20.0f, 550.0f });
	myPosition = myWayPoints[0];
	myDestination = myWayPoints[1];
	SetDirection(myDestination);

	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/TommyIdle.dds");
	spriteIdle->SetSize(mySize);

	myAnimation = Animation(false, false, true, 0, 3, 3, 0.15f, spriteIdle, 512, 512);

	AnimationComponent* animation = AddComponent<AnimationComponent>();
	animation->SetSprite(spriteIdle);
	animation->SetAnimation(&myAnimation);
	spriteIdle->SetSize(mySize);

	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(true);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(false);

	physics->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this);
}

Enemy::~Enemy()
{

}

void Enemy::Update(const float& aDeltaTime)
{
	Move(aDeltaTime);
	PhysicsComponent* physics = this->GetComponent<PhysicsComponent>();
	if (physics->HasCollidedAtPoint(this, myDestination))
	{
		SetNextWayPoint();
	}
	GameObject::Update(aDeltaTime);
}

void Enemy::Move(const float& aDeltaTime)
{
	PhysicsComponent* physics = this->GetComponent<PhysicsComponent>();
	physics->SetVelocity(myDirection * mySpeed * aDeltaTime);
}



void Enemy::SetNextWayPoint()
{
	++myCurrentPoint;
	if (myCurrentPoint > myWayPoints.size())
	{
		myCurrentPoint = 0;
		myDestination = myWayPoints[0];
	}
	else
	{
		myDestination = myWayPoints[myCurrentPoint];
	}
	SetDirection(myDestination);
}

void Enemy::SetDirection(const v2f& aDestination)
{
	myDirection = aDestination - myPosition;
	myDirection.Normalize();
}