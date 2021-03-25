#include "stdafx.h"
#include "DeadlyPlatform.hpp"
#include "AudioManager.h"
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
		AudioManager::GetInstance()->PlayAudio(AudioList::SpikeDeath);
		AudioManager::GetInstance()->LockAudio(AudioList::SpikeDeath);
		AudioManager::GetInstance()->PlayAudio(AudioList::SpikeHit);
		AudioManager::GetInstance()->LockAudio(AudioList::SpikeHit);
		player->Kill();
	}
}