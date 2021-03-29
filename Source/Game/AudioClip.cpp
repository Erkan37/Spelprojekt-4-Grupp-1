#include "stdafx.h"
#include "AudioClip.h"
#include "tga2d/audio/audio.h"
#include "tga2d/audio/audio_out.h"
#include "AudioClip.h"

AudioClip::AudioClip(const char* anAudioPath, const bool aIsLooping, const float& aVolume, const float& aMinVol, const float& aMaxVol, AudioLayer aLayer) :
	myMaxVolume(aMaxVol), myMinVolume(aMinVol)
{
	myAudio = new Tga2D::CAudio();
	myVolume = aVolume;
	myAudio->Init(anAudioPath, aIsLooping);
	myLayer = aLayer;
	myAudio->SetVolume(myVolume);
}

AudioClip::~AudioClip()
{
	myAudio = nullptr;
	delete myAudio;
}

void AudioClip::SetVolume(const float& aVolChange)
{
	myVolume = aVolChange;
	if (myVolume < myMinVolume)
	{
		myVolume = myMinVolume;
	}
	if (myVolume > myMaxVolume)
	{
		myVolume = myMaxVolume;
	}
	myAudio->SetVolume(myVolume);
}

void AudioClip::AddVolume(const float& aVolChange)
{
	myVolume += aVolChange;
	if (myVolume < 0)
	{
		myVolume = 0;
	}
	if (myVolume > 1)
	{
		myVolume = 1;
	}
	myAudio->SetVolume(myVolume);
}

void AudioClip::SetPosition(const VECTOR2F aPosition)
{
	//myAudio->SetPosition(aPosition / 10);
}

void AudioClip::Play()
{
	if (myCanPlay) myAudio->Play();
}

void AudioClip::Mute()
{
	//myAudio->Stop(true);
	myAudio->SetVolume(0);
}

void AudioClip::UnMute()
{
	myAudio->SetVolume(myVolume);
}

void AudioClip::Stop()
{
	myAudio->Stop();
	UnLock();
}

void AudioClip::Lock()
{
	myCanPlay = false;
}

void AudioClip::UnLock()
{
	myCanPlay = true;
}

AudioLayer AudioClip::GetLayer()
{
	return myLayer;
}
