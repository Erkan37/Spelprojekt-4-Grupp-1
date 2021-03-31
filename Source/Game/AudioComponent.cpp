#include "stdafx.h"
#include "AudioComponent.h"
#include "AudioManager.h"
#include "LevelScene.h"
#include "CU/Utilities.h"
#include "Player.hpp"
#include "Scene.h"

AudioComponent::AudioComponent() : Component()
{

}

AudioComponent::~AudioComponent()
{
	AudioManager::GetInstance()->RemoveomponentToListen(this);
}

void AudioComponent::AddAudio(AudioList aSound)
{
	myAudio = aSound;
}

void AudioComponent::PlayAudio()
{
	AudioManager::GetInstance()->PlayIfAvailable(myAudio);
}

void AudioComponent::StopAudio()
{
	AudioManager::GetInstance()->Stop(myAudio);
}

void AudioComponent::SetRadius(const float& aRadius)
{
	myRadius = aRadius;
	AudioManager::GetInstance()->SetSoundVolume(myAudio, 0);
}
void AudioComponent::LockAudio(AudioList aSound)
{
	//AudioLibrary::GetInstance().myAudioList[aSound]->Lock();
}

void AudioComponent::UnLockAudio(AudioList aSound)
{
	//AudioLibrary::GetInstance().myAudioList[aSound]->UnLock();
}

void AudioComponent::Update(Transform& aTransform, GameObject& aGameObject)
{
	v2f lengthFromPlayer = aGameObject.GetPosition() - dynamic_cast<LevelScene*>(aGameObject.GetScene())->GetPlayer()->GetPosition();
	if (lengthFromPlayer.Length() < myRadius)
	{
		myDistanceToPlayer = lengthFromPlayer.Length();
		if (!myHasBeenAdded)
		{
			AudioManager::GetInstance()->AddComponentToListen(this);
			myHasBeenAdded = true;
		}
		myVolume = 1 - (myDistanceToPlayer / myRadius);
	}
	else
	{
		if (myHasBeenAdded)
		{
			myHasBeenAdded = false;
			AudioManager::GetInstance()->RemoveomponentToListen(this);
		}
	}
}
