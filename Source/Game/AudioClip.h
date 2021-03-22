#pragma once
#include "AudioLibrary.h"

namespace Tga2D
{
	class AudioOut;
	class CAudio;
}

class AudioClip
{
public:
	AudioClip() = default;
	AudioClip(const char* anAudioPath, const bool aIsLooping, const float& aVolume, AudioLayer aLayer);
	AudioClip(AudioClip& anAudioClip);
	~AudioClip();

	void Update(const float& someDeltaTime);

	void SetVolume(const float& aVolChange);
	void AddVolume(const float& aVolChange);
	void SetPosition(const VECTOR2F aPosition);

	void Play();
	void Stop();

	void Mute();
	void UnMute();

	void Lock();
	void UnLock();

private:
	bool myFade = false;
	float myFadeSpeed = 1;
	float myVolume = 0.0f;
	Tga2D::CAudio* myAudio = nullptr;
	bool myCanPlay = true;
	AudioLayer myLayer;
};