#include "stdafx.h"
#include "LevelScene.h"
#include "EnemyProjectile.h"
#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "Player.hpp"
#include "GameObject.h"
#include <iostream>
#include "Platform.h"

EnemyProjectile::EnemyProjectile(Scene* aScene) : GameObject(aScene)
{
	this->Activate();
	SpriteComponent* spriteIdle = this->AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/TempProjectile.dds");
	spriteIdle->SetSize(mySize);

	this->SetZIndex(400);
	this->SetPosition({400, 600});

	ColliderComponent* collider = this->AddComponent<ColliderComponent>();
	Transform transform = this->GetTransform();
	collider->SetSize(mySize);

	PhysicsComponent* physics = this->AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(false);
	

	//myAnimation = Animation(false, false, true, 1, 1, 1, 0.15f, spriteIdle, 512, 512);

	//AnimationComponent* animation = AddComponent<AnimationComponent>();
	//animation->SetSprite(spriteIdle);
	//animation->SetAnimation(&myAnimation);
	//spriteIdle->SetSize(mySize);

	GameObject::Init();
}

void EnemyProjectile::InitProjectile(const v2f& aPosition, const v2f& aTarget)
{
	this->SetPosition(aPosition);
	myDirection = aTarget - aPosition;
	myDirection.Normalize();
	PhysicsComponent* physics = this->GetComponent<PhysicsComponent>();
	physics->SetVelocity(myDirection * mySpeed);
}

void EnemyProjectile::Update(const float& aDeltaTime)
{
	GameObject::Update(aDeltaTime);
}

void EnemyProjectile::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	Platform* platform = dynamic_cast<Platform*>(aGameObject);
	if (player)
	{
		player->Kill();
	}
	if (platform || player)
	{
		this->Destroy();
	}
}

void EnemyProjectile::InitCollider()
{
	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(true);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(true);

	physics->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this);
	//physics->SetVelocity({10, 0});
}