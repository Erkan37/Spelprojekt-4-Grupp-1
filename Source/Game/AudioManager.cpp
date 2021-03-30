#include "stdafx.h"
#include "AudioManager.h"
#include "Random.hpp"
#include "tga2d/audio/audio_out.h"
#include "AudioClip.h"
#include <bass/bass.h>
#include <algorithm>

#pragma comment(lib,"bass.lib")

static std::unique_ptr<AudioManager> ourInstance = std::make_unique<AudioManager>();

const std::unique_ptr<AudioManager>& AudioManager::GetInstance()
{
	return ourInstance;
}

AudioManager::AudioManager()
{
	myAudioOut = {};
	mySFXVolume = 0.2f;
	myMusicVolume = 0.5f;
	SetMusicVolume(mySFXVolume);
	SetSFXVolume(mySFXVolume);
};

AudioManager::~AudioManager() = default;


void AudioManager::Init()
{
	//myAudioOut = std::make_unique<Tga2D::AudioOut>();
	//SetMusicVolume(0.5f);
	//SetSFXVolume(0.5f);
	//PlayMusic("Sounds/Music/04 - Pushing Onwards.mp3", 0.025f);
}

void AudioManager::SetMusicVolume(float aVolume)
{
	for (auto const& [key, val] : myLibrary.myAudioList)
	{
		if (myLibrary.myAudioList[key]->GetLayer() == AudioLayer::Music)
		{
			myLibrary.myAudioList[key]->SetVolume(aVolume);
		}
	}
}

void AudioManager::SetSFXVolume(float aVolume)
{
	for (auto const& [key, val] : myLibrary.myAudioList)
	{
		if (myLibrary.myAudioList[key]->GetLayer() == AudioLayer::SoundEffect)
		{
			myLibrary.myAudioList[key]->SetVolume(aVolume);
		}
	}
}

void AudioManager::AddMusicVolume(float aVolume)
{
	for (auto const& [key, val] : myLibrary.myAudioList)
	{
		if (myLibrary.myAudioList[key]->GetLayer() == AudioLayer::Music)
		{
			myLibrary.myAudioList[key]->AddVolume(aVolume);
		}
	}
}

void AudioManager::AddSFXVolume(float aVolume)
{
	for (auto const& [key, val] : myLibrary.myAudioList)
	{
		if (myLibrary.myAudioList[key]->GetLayer() == AudioLayer::SoundEffect)
		{
			myLibrary.myAudioList[key]->AddVolume(aVolume);
		}
	}
}

void AudioManager::SetSoundVolume(AudioList aSound, const float& aVolume)
{
	myLibrary.myAudioList[aSound]->SetVolume(aVolume);
}

void AudioManager::SetSoundPosition(AudioList aSound, const VECTOR2F& aPosition)
{
	myLibrary.myAudioList[aSound]->SetPosition(aPosition);
}

float AudioManager::GetMusicVolume() const
{
	return myMusicVolume;
}

float AudioManager::GetSFXVolume() const
{
	return mySFXVolume;
}

//void AudioManager::PlayMusic(const std::string & anAudioPath, float aVolume, bool aShouldLoop)
//{
//	Tga2D::AudioOut::Handle channel = {};
//
//	if (!IsPlaying(anAudioPath))
//	{
//		const float volume = myMusicVolume * aVolume;
//		StopCurrentMusic();
//
//		if (Utils::RandomInt(0, 100) == 100)
//		{
//			myAudioOut->PlayMusic("Sounds/Music/GameMusic.mp3", aShouldLoop, channel);
//		}
//		else
//		{
//			myAudioOut->PlayMusic(anAudioPath, aShouldLoop, channel);
//		}
//		
//		myAudioOut->SetVolume(channel, volume);
//	}
//
//	if (aShouldLoop)
//	{
//		BASS_ChannelFlags(channel, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
//	}
//}

void AudioManager::PlayAudio(AudioList aSound)
{
	myLibrary.myAudioList[aSound]->Play();
	//Tga2D::AudioOut::Handle channel;

	//const float volume = mySFXVolume * aVolume;
	//myAudioOut->Play(anAudioPath, false, channel);

	//myAudioOut->SetVolume(channel, volume);

	//if (aShouldLoop)
	//{
	//	BASS_ChannelFlags(channel, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	//}
}

void AudioManager::PlayIfAvailable(AudioList aSound)
{
	myLibrary.myAudioList[aSound]->PlayIfAvailable();
}

void AudioManager::Stop(AudioList aSound)
{
	myLibrary.myAudioList[aSound]->Stop();
	//myAudioOut->Stop(anAudioPath, true);
}

//bool AudioManager::IsPlaying(const std::string & anAudioPath)
//{
//	return Tga2D::audio_helpers::IsNowPlaying(*myAudioOut, anAudioPath);
//}
//
//void AudioManager::StopAll(bool anOnlyRepeating)
//{
//	Tga2D::audio_helpers::StopAllNowPlaying(*myAudioOut, anOnlyRepeating);
//}

void AudioManager::StopCurrentMusic()
{
	myAudioOut->StopMusic(true);
}

void AudioManager::StopAllSounds(bool anAndMusic)
{
	if (anAndMusic)
	{
		StopCurrentMusic();
	}

	for (auto const& [key, val] : myLibrary.myAudioList)
	{
		val->Stop();
	}
}

void AudioManager::LockAudio(AudioList anAudio)
{
	myLibrary.myAudioList[anAudio]->Lock();
}

void AudioManager::UnLockAudio(AudioList anAudio)
{
	myLibrary.myAudioList[anAudio]->UnLock();
}
