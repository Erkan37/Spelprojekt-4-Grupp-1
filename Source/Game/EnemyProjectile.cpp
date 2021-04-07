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
#include "ParticleEffectFactory.h"

typedef EnemyData::EnemyFloatEnum EEnum;

EnemyProjectile::EnemyProjectile(Scene* aScene, const v2f& aPosition, const v2f& aTarget) : GameObject(aScene)
{
	myJsonData = dynamic_cast<EnemyData*>(&DataManager::GetInstance().GetDataStruct(DataEnum::enemy));
	
	this->Activate();
	this->SetZIndex(141);

	InitVisuals();
	InitCollider();
	SetDirection(aPosition, aTarget);
	GameObject::Init();

	LevelScene* levelScene = dynamic_cast<LevelScene*>(aScene);
	myEffectFactory = &levelScene->GetEffectFactory();
	myEffectFactory->SpawnEffectFollowObject(this, eParticleEffects::BulletEffectTrail);
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
		if (!player->GetHasDied())
		{
			player->Kill();
		}
	}
	if (platform || player)
	{
		myEffectFactory->SpawnEffect(GetPosition(), eParticleEffects::BulletEffectHit);
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
	spriteIdle->SetSize(v2f(8.0f, 8.0f));

	myAnimation = Animation(false, false, false, 0, 5, 5, 0.1f, spriteIdle, 8, 8);

	AnimationComponent* animation = AddComponent<AnimationComponent>();
	animation->SetSprite(spriteIdle);
	animation->SetAnimation(&myAnimation);
	spriteIdle->SetSize(v2f(8.0f, 8.0f));
}