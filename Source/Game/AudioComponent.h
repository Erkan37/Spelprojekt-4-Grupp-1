#pragma once
#include "Component.hpp"
#include "AudioClip.h"
#include <vector>
#include "AudioLibrary.h"
class AudioComponent : public Component
{
public:
	AudioComponent();
	
	void AddAudio(AudioList aSound);
	void PlayAudio();
	void StopAudio();
	void SetRadius(const float& aRadius);
	void SetVolume(const int& anIndex, const float& aVolume);
	void SetMinVolume(const float& aMinVolume);
	void SetMaxVolume(const float& aMaxVolume);
	void LockAudio(AudioList aSound);
	void UnLockAudio(AudioList aSound);

	void Update(Transform& aTransform, GameObject& aGameObject) override;

private:
	std::vector<AudioList> myAudioList;
	float myRadius = 150.0f;
	float myMinVolume = 0.1f;
	float myMaxVolume = 0.4f;
	float myAudioSpectrum = 0;
	AudioList myAudio;
};

