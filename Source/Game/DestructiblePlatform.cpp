#include "stdafx.h"
#include "DestructiblePlatform.hpp"

#include "Player.hpp"

#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"

DestructiblePlatform::DestructiblePlatform(Scene* aLevelScene)
	:
	Platform(aLevelScene)
{

}

void DestructiblePlatform::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		if (player->GetIsBashing())
		{
			GetComponent<PhysicsComponent>()->SetCanCollide(false);
			GetComponent<SpriteComponent>()->Deactivate();
			player->BounceOnDestructibleWall();
		}
	}

	Platform::OnCollision(aGameObject);
}