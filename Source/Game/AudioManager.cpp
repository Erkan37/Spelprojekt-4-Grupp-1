#include "stdafx.h"
#include "AudioManager.h"

#include "tga2d/audio/audio_out.h"

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
	mySFXVolume = {};
	myMusicVolume = {};
};

AudioManager::~AudioManager() = default;


void AudioManager::Init()
{
	myAudioOut = std::make_unique<Tga2D::AudioOut>();
	SetMusicVolume(1.f);
	SetSFXVolume(1.f);
}

void AudioManager::SetMusicVolume(float aVolume)
{
	myMusicVolume = std::clamp(aVolume, 0.f, 1.f);
}

void AudioManager::SetSFXVolume(float aVolume)
{
	mySFXVolume = std::clamp(aVolume, 0.f, 1.f);
}

float AudioManager::GetMusicVolume() const
{
	return myMusicVolume;
}

float AudioManager::GetSFXVolume() const
{
	return mySFXVolume;
}

void AudioManager::PlayMusic(const std::string & anAudioPath, float aVolume, bool aShouldLoop)
{
	Tga2D::AudioOut::Handle channel = {};

	if (!IsPlaying(anAudioPath))
	{
		float volume = myMusicVolume * aVolume;
		myAudioOut->Stop(anAudioPath, true);
		myAudioOut->PlayMusic(anAudioPath, aShouldLoop, channel);
		myAudioOut->SetVolume(channel, volume);
	}

	if (aShouldLoop)
	{
		BASS_ChannelFlags(channel, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	}
}

void AudioManager::PlaySFX(const std::string & anAudioPath, float aVolume, bool aShouldLoop)
{
	Tga2D::AudioOut::Handle channel;

	float volume = mySFXVolume * aVolume;
	myAudioOut->Play(anAudioPath, false, channel);
	myAudioOut->SetVolume(channel, volume);

	if (aShouldLoop)
	{
		BASS_ChannelFlags(channel, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	}
}

void AudioManager::Stop(const std::string & anAudioPath)
{
	myAudioOut->Stop(anAudioPath, true);
}

bool AudioManager::IsPlaying(const std::string & anAudioPath)
{
	return Tga2D::audio_helpers::IsNowPlaying(*myAudioOut, anAudioPath);
}

void AudioManager::StopAll(bool anOnlyRepeating)
{
	Tga2D::audio_helpers::StopAllNowPlaying(*myAudioOut, anOnlyRepeating);
}
