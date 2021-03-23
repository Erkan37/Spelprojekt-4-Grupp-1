#include "stdafx.h"
#include "Platform.h"

#include "../External/Headers/CU/Utilities.h"

#include "PhysicsComponent.h"
#include "ColliderComponent.h"

#include "Player.hpp"

#include "PostMaster.hpp"

Platform::Platform(Scene* aScene)
	:
	GameObject(aScene)
{

}

Platform::~Platform()
{

}

void Platform::Init(const v2f& aSize, const v2f& aSpriteSize, const v2f& aPosition, const bool& aIsOneway)
{
	SetPosition(aPosition);
	SetPivot({ 0.0f, 0.0f });

	PhysicsComponent* gphys = AddComponent<PhysicsComponent>();
	gphys->SetCanCollide(true);
	gphys->SetIsStatic(true);

	if (aIsOneway)
	{
		gphys->SetCollisionType(PhysicsComponent::eCollisionType::OneWay);
	}

	ColliderComponent* collider = AddComponent<ColliderComponent>();
	collider->SetPosition({ aSpriteSize.x / 2.0f, aSpriteSize.y / 2.0f });
	collider->SetSize(aSize);

	GameObject::Init();
}

void Platform::Update(const float& aDeltaTime)
{
	GameObject::Update(aDeltaTime);
}

void Platform::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		player->SetPlatformVelocity(v2f(0.0f, 0.0f));
		player->SetGroundIndex(myTypeIndex);
		if (player->GetHasLanded())
		{
			PostMaster::GetInstance().ReceiveMessage(Message(eMessageType::PlayerSafeLanded, 0));
		}
	}
}