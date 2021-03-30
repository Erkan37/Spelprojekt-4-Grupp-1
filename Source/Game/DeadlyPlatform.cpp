#include "stdafx.h"
#include "DeadlyPlatform.hpp"
#include "AudioManager.h"
#include "Player.hpp"

#include "PhysicsComponent.h"

DeadlyPlatform::DeadlyPlatform(Scene* aLevelScene)
	:
	Platform(aLevelScene)
{

}

void DeadlyPlatform::Init(const v2f& aSize, const v2f& aSpriteSize, const v2f& aPosition, const bool& aIsOneway)
{
	Platform::Init(aSize, aSpriteSize, aPosition, aIsOneway);

	GetComponent<PhysicsComponent>()->SetCanCollide(false);
}

void DeadlyPlatform::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		AudioManager::GetInstance()->PlayAudio(AudioList::SpikeDeath);
		AudioManager::GetInstance()->LockAudio(AudioList::SpikeDeath);
		AudioManager::GetInstance()->PlayAudio(AudioList::SpikeHit);
		AudioManager::GetInstance()->LockAudio(AudioList::SpikeHit);

		if (!player->GetHasDied())
		{
			player->Kill();
		}
	}
}