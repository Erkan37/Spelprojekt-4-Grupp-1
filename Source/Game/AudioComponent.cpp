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

void AudioComponent::AddAudio(AudioList aSound, Scene* aScene)
{
	myAudio = aSound;
	myScene = aScene;
}

void AudioComponent::PlayAudio()
{
	//myAudioList[0]->Play();
	//AudioLibrary::GetInstance().myAudioList[aSound]->Play();
	//AudioManager::GetInstance()->PlayIfAvailable(myAudio);
}

void AudioComponent::StopAudio()
{
	AudioManager::GetInstance()->Stop(myAudio);

	//AudioLibrary::GetInstance().myAudioList[aSound]->Stop();
}

void AudioComponent::SetRadius(const float& aRadius)
{
	myRadius = aRadius;
	AudioManager::GetInstance()->SetSoundVolume(myAudio, 0);
	//myAudioList[0]->SetVolume(0);//AudioLibrary::GetInstance().myAudioList[AudioList::ProjectileFly]->SetVolume(0);
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
	if (lengthFromPlayer.Length() <= myRadius)
	{
		float length = lengthFromPlayer.Length();
		//If is closest to player. 
		// Set the new distance
		// play 
		//else
		//Stop
		//if (dynamic_cast<Player*>(dynamic_cast<LevelScene*>(this->myScene)->GetPlayer())->GetClosestPlatform() > length)
		//{
		//	dynamic_cast<Player*>(dynamic_cast<LevelScene*>(this->myScene)->GetPlayer())->SetClosestPlatform(length);
		//	float volPercentage = length / myRadius;
		//	AudioManager::GetInstance()->SetSoundVolume(myAudio, 1 - volPercentage);
		//	AudioManager::GetInstance()->SetSoundPosition(myAudio, lengthFromPlayer.GetNormalized());
		//	AudioManager::GetInstance()->PlayIfAvailable(myAudio);
		//}
		//else
		//{
		//	AudioManager::GetInstance()->Stop(myAudio);
		//}
		//AudioLibrary::GetInstance().myAudioList[AudioList::ProjectileFly]->SetPosition(lengthFromPlayer.GetNormalized());
	}
	else
	{
		//AudioManager::GetInstance()->SetSoundVolume(myAudio, 0);
		//AudioManager::GetInstance()->Stop(myAudio);
	}
}
