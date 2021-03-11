#include "stdafx.h"
#include "LevelScene.h"
#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "Player.hpp"
#include "Enemy.h"

Enemy::Enemy(LevelScene* aScene) : GameObject(aScene)
{
	myWayPoints.push_back({ 0.0f, 0.0f });
	myDestination = myWayPoints[0];
	this->SetPosition(myWayPoints[0]);
	SetDirection(myDestination);
	InitAnimations();
	InitCollider();
}

Enemy::Enemy(Scene* aScene, const std::vector<v2f>& someCoordinates) : GameObject(aScene)
{
	myWayPoints = someCoordinates;
	myDestination = myWayPoints[1];
	this->SetPosition(myWayPoints[0]);
	SetDirection(myDestination);
	InitAnimations();
	InitCollider();
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

void Enemy::InitAnimations()
{
	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/TempEnemy.dds");
	spriteIdle->SetSize(mySize);

	//myAnimation = Animation(false, false, true, 1, 1, 1, 0.15f, spriteIdle, 512, 512);

	//AnimationComponent* animation = AddComponent<AnimationComponent>();
	//animation->SetSprite(spriteIdle);
	//animation->SetAnimation(&myAnimation);
	//spriteIdle->SetSize(mySize);

	this->SetZIndex(400);
}

void Enemy::InitCollider()
{
	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(false);

	physics->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this);
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

void Enemy::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		player->Kill();
	}
}