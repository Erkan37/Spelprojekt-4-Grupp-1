#include "stdafx.h"
#include "AudioObject.h"
#include "AudioComponent.h"

AudioObject::AudioObject(Scene* aScene, const float aRadius, const int aSound, const v2f aPos)
{
	//Do something with aPos
	AudioComponent* audio = AddComponent<AudioComponent>();
	audio->AddAudio(AudioList::MovingPlatform); //aSound
	audio->SetRadius(aRadius);
	audio->PlayAudio();
}
