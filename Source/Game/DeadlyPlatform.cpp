#include "stdafx.h"
#include "DeadlyPlatform.hpp"
#include "Player.hpp"

DeadlyPlatform::DeadlyPlatform(Scene* aLevelScene)
	:
	Platform(aLevelScene)
{

}

void DeadlyPlatform::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		player->Kill();
	}
}