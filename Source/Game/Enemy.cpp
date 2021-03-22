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
#include "AudioComponent.h"
#ifdef _DEBUG
#include "imgui.h"
#endif // DEBUG

typedef EnemyData::EnemyFloatEnum EEnum;

Enemy::Enemy(Scene* aScene) : GameObject(aScene)
{
	myJsonData = dynamic_cast<EnemyData*>(&DataManager::GetInstance().GetDataStruct(DataEnum::enemy));
	myWayPointComponent = nullptr;
}
NormalEnemy::NormalEnemy(Scene* aScene) : Enemy(aScene)
{
	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/Enemies/Enemy1.dds");
	spriteIdle->SetSize({ myJsonData->myFloatValueMap[EEnum::NE_SpriteSizeX], myJsonData->myFloatValueMap[EEnum::NE_SpriteSizeY] });
	this->SetZIndex(400);
	AudioComponent* audio = AddComponent<AudioComponent>();
	audio->AddAudio(AudioList::ProjectileFly);
	audio->SetRadius(300);
	audio->PlayAudio(AudioList::ProjectileFly);
}
ShootingEnemy::ShootingEnemy(Scene* aScene) : Enemy(aScene)
{
	SpriteComponent* spriteIdle = AddComponent<SpriteComponent>();
	spriteIdle->SetSpritePath("Sprites/Enemies/Enemy2.dds");
	spriteIdle->SetSize({ myJsonData->myFloatValueMap[EEnum::SE_SpriteSizeX], myJsonData->myFloatValueMap[EEnum::SE_SpriteSizeY] });
	this->SetZIndex(400);
	//AudioLibrary::GetInstance().myAudioList[AudioList::ProjectileFly]->Play();
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
void Enemy::InitCollider()
{
	PhysicsComponent* physics = AddComponent<PhysicsComponent>();
	physics->SetCanCollide(false);
	physics->SetIsStatic(false);
	physics->SetApplyGravity(false);

	//physics->CreateColliderFromSprite(GetComponent<SpriteComponent>(), this);
}
void NormalEnemy::InitCollider()
{
	Enemy::InitCollider();
	ColliderComponent* collider = this->AddComponent<ColliderComponent>();
	Transform transform = this->GetTransform();
	collider->SetSize({myJsonData->myFloatValueMap[EEnum::NE_CollisionSizeX], myJsonData->myFloatValueMap[EEnum::NE_CollisionSizeY]});
}
void ShootingEnemy::InitCollider()
{
	Enemy::InitCollider();
	ColliderComponent* collider = this->AddComponent<ColliderComponent>();
	Transform transform = this->GetTransform();
	collider->SetSize({ myJsonData->myFloatValueMap[EEnum::SE_CollisionSizeX], myJsonData->myFloatValueMap[EEnum::SE_CollisionSizeY] });
}

void NormalEnemy::Update(const float& aDeltaTime)
{
	if (IsMoving)
	{
		myWayPointComponent->Move(aDeltaTime);
	}
	GameObject::Update(aDeltaTime);
}
void ShootingEnemy::Update(const float& aDeltaTime)
{
	if (IsMoving)
	{
		myWayPointComponent->Move(aDeltaTime);
	}
	GameObject::Update(aDeltaTime);

	v2f lengthToPlayer = dynamic_cast<LevelScene*>(this->myScene)->GetPlayer()->GetPosition() - this->GetPosition();
	if (lengthToPlayer.Length() <= myJsonData->myFloatValueMap[EEnum::FireRadius])
	{
		myShotTimer -= aDeltaTime;
		if (myShotTimer <= 0)
		{
			myShotTimer = myJsonData->myFloatValueMap[EEnum::FireRate];
			Shoot();
		}
	}

#ifdef _DEBUG
	ImGuiUpdate();
#endif // _DEBUG
}

void ShootingEnemy::Shoot()
{
	EnemyProjectile* projectile = new EnemyProjectile(this->myScene, this->GetPosition(), dynamic_cast<LevelScene*>(this->myScene)->GetPlayer()->GetPosition());
}
void Enemy::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		player->Kill();
	}
}

#ifdef _DEBUG
void ShootingEnemy::ImGuiUpdate()
{
	ImGui::Begin("Enemies", &myIsActive, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Save to JSON"))
	{
		DataManager::GetInstance().SetDataStruct(DataEnum::enemy);
	}

	ImGui::InputFloat("Fire Rate", &myJsonData->myFloatValueMap[EEnum::FireRate], 0.0f, 50.0f);
	ImGui::InputFloat("Fire Radius", &myJsonData->myFloatValueMap[EEnum::FireRadius], 0.0f, 1000.0f);
	ImGui::InputFloat("Speed", &myJsonData->myFloatValueMap[EEnum::Speed], 0.0f, 1000.0f);

	ImGui::End();
}
#endif // _DEBUG
