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
	myWayPoints.push_back({ 300.0f, 750.0f });
	myWayPoints.push_back({ 500.0f, 950.0f });
	myWayPoints.push_back({ 600.0f, 750.0f });
	myWayPoints.push_back({ 500.0f, 550.0f });
	myDestination = myWayPoints[1];
	this->SetPosition(myWayPoints[0]);
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
	this->SetZIndex(400);
}

Enemy::~Enemy()
{

}

void Enemy::Update(const float& aDeltaTime)
{
	Move(aDeltaTime);
	SetDirection(myDestination);
	if (myDestination.x >= this->GetPosition().x && myDestination.x <= this->GetPosition().x + mySize.x &&
		myDestination.y >= this->GetPosition().y && myDestination.y <= this->GetPosition().y + mySize.y)
	{
		SetNextWayPoint();
	}
	GameObject::Update(aDeltaTime);
}

void Enemy::Move(const float& aDeltaTime)
{
	PhysicsComponent* physics = this->GetComponent<PhysicsComponent>();
	physics->SetVelocity(myDirection * mySpeed);
}


void Enemy::SetNextWayPoint()
{
	++myCurrentPoint;
	if (myCurrentPoint >= myWayPoints.size())
	{
		myCurrentPoint = 0;
	}
	myDestination = myWayPoints[myCurrentPoint];
}

void Enemy::SetDirection(const v2f& aDestination)
{
	myDirection = aDestination - this->GetPosition();
	myDirection.Normalize();
}