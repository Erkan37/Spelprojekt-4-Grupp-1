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
	SetZIndex(94);
}

void DestructiblePlatform::OnCollision(GameObject* aGameObject)
{
	if (!myWasDestroyed)
	{
		Player* player = dynamic_cast<Player*>(aGameObject);
		if (player)
		{
			player->SetPlatformVelocity(v2f(0.0f, 0.0f));

			if (player->GetIsBashing())
			{
				GetComponent<PhysicsComponent>()->SetCanCollide(false);
				GetComponent<SpriteComponent>()->Deactivate(); //Actually, play animation;
				player->BounceOnDestructibleWall();

				myWasDestroyed = true;
			}
		}
	}
}