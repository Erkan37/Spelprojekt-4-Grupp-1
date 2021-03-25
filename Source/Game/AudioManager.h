#pragma once

#include <string>
#include <memory>
#include "AudioLibrary.h"

namespace Tga2D
{
	class AudioOut;
}

class AudioManager
{
public:

	AudioManager();
	~AudioManager();

	const static std::unique_ptr<AudioManager>& GetInstance();

	void Init();

	void SetMusicVolume(float aVolume);
	void SetSFXVolume(float aVolume);
	void AddMusicVolume(float aVolume);
	void AddSFXVolume(float aVolume);

	void SetSoundVolume(AudioList aSound, const float& aVolume);
	void SetSoundPosition(AudioList aSound, const VECTOR2F& aPosition);

	float GetMusicVolume() const;
	float GetSFXVolume() const;

	void PlayAudio(AudioList aSound);

	void Stop(AudioList aSound);

	//bool IsPlaying(const std::string& anAudioPath);

	//void StopAll(bool anOnlyRepeating = false);

	void LockAudio(AudioList anAudio);
	void UnLockAudio(AudioList anAudio);

private:

	std::unique_ptr<Tga2D::AudioOut> myAudioOut;
	float myMusicVolume;
	float mySFXVolume;

	void StopCurrentMusic();

	AudioLibrary myLibrary = AudioLibrary();

};

