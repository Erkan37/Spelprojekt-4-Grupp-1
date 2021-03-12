#include "stdafx.h"
#include "LevelScene.h"
#include "EnemyProjectile.h"
#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "Player.hpp"
#include <iostream>

EnemyProjectile::EnemyProjectile(Scene* aScene) : GameObject(aScene)
{
	SpriteComponent* spriteIdle = this->AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/TempProjectile.dds");
	spriteIdle->SetSize(mySize);
	this->SetZIndex(400);
	this->SetPosition({600, 870});
	InitCollider();


	//myAnimation = Animation(false, false, true, 1, 1, 1, 0.15f, spriteIdle, 512, 512);

	//AnimationComponent* animation = AddComponent<AnimationComponent>();
	//animation->SetSprite(spriteIdle);
	//animation->SetAnimation(&myAnimation);
	//spriteIdle->SetSize(mySize);

}

void EnemyProjectile::InitProjectile(const v2f& aPosition, const v2f& aTarget)
{
	//this->SetPosition(aPosition);
	myDirection = aPosition - aTarget;
	myDirection.Normalize();
	PhysicsComponent* physics = this->GetComponent<PhysicsComponent>();
	physics->SetVelocity(myDirection * mySpeed);
}

void EnemyProjectile::Update(const float& aDeltaTime)
{
	GameObject::Update(aDeltaTime);
	//std::cout << this->GetPosition().x << " " << this->GetPosition().y << "\n";
}

void EnemyProjectile::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		player->Kill();
	}
	this->Destroy();
}

void EnemyProjectile::InitCollider()
{
	PhysicsComponent* physics = this->AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(false);

	physics->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this);
	physics->SetVelocity({10, 0});
}