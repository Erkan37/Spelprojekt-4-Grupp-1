#include "stdafx.h"
#include "LevelScene.h"
#include "EnemyProjectile.h"
#include "SpriteComponent.h"
#include "AnimationComponent.hpp"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "Player.hpp"
#include "GameObject.h"
#include "Platform.h"

typedef EnemyData::EnemyFloatEnum EEnum;

EnemyProjectile::EnemyProjectile(Scene* aScene, const v2f& aPosition, const v2f& aTarget) : GameObject(aScene)
{
	myJsonData = dynamic_cast<EnemyData*>(&DataManager::GetInstance().GetDataStruct(DataEnum::enemy));

	this->Activate();
	this->SetZIndex(141);

	InitVisuals();
	InitCollider();
	SetDirection(aPosition, aTarget);
}

void EnemyProjectile::SetDirection(const v2f& aPosition, const v2f& aTarget)
{
	this->SetPosition(aPosition);
	myDirection = aTarget - aPosition;
	myDirection.Normalize();
	PhysicsComponent* physics = this->GetComponent<PhysicsComponent>();
	physics->SetVelocity(myDirection * myJsonData->myFloatValueMap[EEnum::Speed]);
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
	ColliderComponent* collider = this->AddComponent<ColliderComponent>();
	Transform transform = this->GetTransform();
	collider->SetSize(myColliderSize);

	PhysicsComponent* physics = this->AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(false);
}

void EnemyProjectile::InitVisuals()
{
	SpriteComponent* spriteIdle = this->AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/Enemies/Enemy2Bullet.dds");
	spriteIdle->SetSize(mySpriteSize);

	//myAnimation = Animation(false, false, true, 1, 1, 1, 0.15f, spriteIdle, 512, 512);

	//AnimationComponent* animation = AddComponent<AnimationComponent>();
	//animation->SetSprite(spriteIdle);
	//animation->SetAnimation(&myAnimation);
	//spriteIdle->SetSize(mySize);
}