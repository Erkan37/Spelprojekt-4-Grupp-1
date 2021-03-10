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

AudioManager::AudioManager() = default;

AudioManager::~AudioManager() = default;


void AudioManager::Init()
{
	myAudioOut = std::make_unique<Tga2D::AudioOut>();
}

//void AudioManager::SetMasterVolume(float aVolume)
//{
//	const DWORD volume = static_cast<DWORD>(std::clamp(aVolume, 0.0f, 1.0f) * 10000.0f);
//	BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, volume);
//}

void AudioManager::SetMusicVolume(float aVolume)
{
	const DWORD volume = static_cast<DWORD>(std::clamp(aVolume, 0.0f, 1.0f) * 10000.0f);
	BASS_SetConfig(BASS_CONFIG_GVOL_MUSIC, volume);
}

void AudioManager::SetSFXVolume(float aVolume)
{
	const DWORD volume = static_cast<DWORD>(std::clamp(aVolume, 0.0f, 1.0f) * 10000.0f);
	BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, volume);
}

float AudioManager::GetMusicVolume() const
{
	return static_cast<float>(BASS_GetConfig(BASS_CONFIG_GVOL_MUSIC)) / 10000.0f;
}

float AudioManager::GetSFXVolume() const
{
	return static_cast<float>(BASS_GetConfig(BASS_CONFIG_GVOL_SAMPLE)) / 10000.0f;
}

void AudioManager::Play(const std::string& anAudioPath, float aVolume, bool aShouldLoop)
{
	Tga2D::AudioOut::Handle channel;

	myAudioOut->Play(anAudioPath, false, channel);
	myAudioOut->SetVolume(channel, aVolume);

	if (aShouldLoop)
	{
		BASS_ChannelFlags(channel, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	}
}

void AudioManager::Stop(const std::string& anAudioPath)
{
	myAudioOut->Stop(anAudioPath, true);
}

bool AudioManager::IsPlaying(const std::string& anAudioPath)
{
	return Tga2D::audio_helpers::IsNowPlaying(*myAudioOut, anAudioPath);
}

void AudioManager::StopAll(bool anOnlyRepeating)
{
	Tga2D::audio_helpers::StopAllNowPlaying(*myAudioOut, anOnlyRepeating);
}
