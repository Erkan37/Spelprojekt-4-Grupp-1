#pragma once

#include <string>
#include <memory>

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

	float GetMusicVolume() const;
	float GetSFXVolume() const;

	void PlayMusic(const std::string& anAudioPath, float aVolume = 1.0f, bool aShouldLoop = true);
	void PlaySFX(const std::string& anAudioPath, float aVolume = 1.0f, bool aShouldLoop = false);


	void Stop(const std::string& anAudioPath);

	bool IsPlaying(const std::string& anAudioPath);

	void StopAll(bool anOnlyRepeating = false);

private:

	std::unique_ptr<Tga2D::AudioOut> myAudioOut;
	float myMusicVolume;
	float mySFXVolume;

	void StopCurrentMusic();

};

