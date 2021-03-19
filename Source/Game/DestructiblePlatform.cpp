#include "stdafx.h"
#include "DestructiblePlatform.hpp"

#include "Player.hpp"

#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

DestructiblePlatform::DestructiblePlatform(Scene* aLevelScene)
	:
	Platform(aLevelScene),
	myWasDestroyed(false)
{
	SetZIndex(-6);
}

void DestructiblePlatform::OnCollision(GameObject* aGameObject)
{
	if (!myWasDestroyed)
	{
		Player* player = dynamic_cast<Player*>(aGameObject);
		if (player)
		{
			if (player->GetIsBashing())
			{
				GetComponent<PhysicsComponent>()->SetCanCollide(false);
				GetComponent<SpriteComponent>()->Deactivate(); //Actually, play animation;
				player->BounceOnDestructibleWall();

				myWasDestroyed = true;
			}
		}

		Platform::OnCollision(aGameObject);
	}
}