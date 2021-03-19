#include "stdafx.h"
#include "UnstablePlatform.hpp"

#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

#include "Player.hpp"

UnstablePlatform::UnstablePlatform(Scene* aLevelScene)
	:
	Platform(aLevelScene),
	myDestroyTime(0.0f),
	myRespawnTime(0.0f),
	myTimer(0.0f),
	myCollidedWithPlayer(false),
	myIsDeactivated(false)
{
	SetZIndex(94);
}

void UnstablePlatform::Update(const float& aDeltaTime)
{
	if (myCollidedWithPlayer || myIsDeactivated)
	{
		myTimer -= aDeltaTime;
	}

	if (myCollidedWithPlayer && myTimer <= 0)
	{
		myTimer = myRespawnTime;
		myCollidedWithPlayer = false;
		DeactivatePlatform();
	}
	else if(myTimer <= 0)
	{
		ActivatePlatform();
	}

	myPlayerIsOnTop = false;

	Platform::Update(aDeltaTime);
}

void UnstablePlatform::SetTimerProperties(const float& aDestroyTime, const float& aRespawnTime)
{
	myDestroyTime = aDestroyTime;
	myRespawnTime = aRespawnTime;

	myTimer = myDestroyTime;
}

void UnstablePlatform::OnCollision(GameObject* aGameObject)
{
	if (!myPlayerIsOnTop)
	{
		return;
	}

	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player && (!myCollidedWithPlayer && !myIsDeactivated) && aGameObject->GetPositionY() < myTransform.myPosition.y)
	{	
		myCollidedWithPlayer = true;
		myTimer = myDestroyTime;
	}

	Platform::OnCollision(aGameObject);
}

void UnstablePlatform::Landed(const int& aOverlapY)
{
	if (aOverlapY >= 0)
	{
		myPlayerIsOnTop = true;
	}
}

void UnstablePlatform::ActivatePlatform()
{
	GetComponent<PhysicsComponent>()->SetCanCollide(true);
	GetComponent<SpriteComponent>()->Activate();
	myIsDeactivated = false;
}

void UnstablePlatform::DeactivatePlatform()
{
	GetComponent<PhysicsComponent>()->SetCanCollide(false);
	GetComponent<SpriteComponent>()->Deactivate();
	myIsDeactivated = true;
}