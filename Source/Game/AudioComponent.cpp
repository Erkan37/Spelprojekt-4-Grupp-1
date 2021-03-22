#include "stdafx.h"
#include "AudioComponent.h"
#include "LevelScene.h"
#include <iostream>
#include "CU/Utilities.h"

AudioComponent::AudioComponent() : Component()
{

}

void AudioComponent::AddAudio(AudioList aSound)
{
	//myAudioList.push_back(new AudioClip(*AudioLibrary::GetInstance().myAudioList[aSound]));
}

void AudioComponent::PlayAudio(AudioList aSound)
{
	//myAudioList[0]->Play();
	//AudioLibrary::GetInstance().myAudioList[aSound]->Play();
}

void AudioComponent::StopAudio(AudioList aSound)
{
	//AudioLibrary::GetInstance().myAudioList[aSound]->Stop();
}

void AudioComponent::SetRadius(const float& aRadius)
{
	myRadius = aRadius;
	myHasRadius = true;
	//myAudioList[0]->SetVolume(0);//AudioLibrary::GetInstance().myAudioList[AudioList::ProjectileFly]->SetVolume(0);
}

void AudioComponent::SetHasRadius(bool aHasRadius)
{
	myHasRadius = aHasRadius;
}

void AudioComponent::SetVolume(const int& anIndex, const float& aVolume)
{
	//myAudioList[anIndex - 1]->SetVolume(aVolume);
}

void AudioComponent::SetMinVolume(const float& aMinVolume)
{
	myMinVolume = aMinVolume;
}

void AudioComponent::SetMaxVolume(const float& aMaxVolume)
{
	myMaxVolume = aMaxVolume;
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
	if (myHasRadius)
	{
		v2f lengthFromPlayer = aGameObject.GetPosition() - dynamic_cast<LevelScene*>(aGameObject.GetScene())->GetPlayer()->GetPosition();
		if (lengthFromPlayer.Length() <= myRadius)
		{
			//float length = lengthFromPlayer.Length();
			//float volPercentage = length / myRadius;
			//AudioLibrary::GetInstance().myAudioList[AudioList::ProjectileFly]->SetVolume(1 - volPercentage);
			//AudioLibrary::GetInstance().myAudioList[AudioList::ProjectileFly]->SetPosition(lengthFromPlayer.GetNormalized());
		}
	}
}
