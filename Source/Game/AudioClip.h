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
	AudioClip(const char* anAudioPath, const bool aIsLooping, const float& aVolume, const float& aMinVol, const float& aMaxVol, AudioLayer aLayer);
	~AudioClip();

	void SetVolume(const float& aVolChange);
	void AddVolume(const float& aVolChange);
	void SetPosition(const VECTOR2F aPosition);

	void Play();
	void Stop();

	void Mute();
	void UnMute();

	void Lock();
	void UnLock();

	AudioLayer GetLayer();

private:
	float myVolume = 0.0f;
	const float myMinVolume;
	const float myMaxVolume;
	bool myCanPlay = true;
	AudioLayer myLayer;
	Tga2D::CAudio* myAudio = nullptr;
};