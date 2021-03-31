#pragma once
#include "Component.hpp"
#include "AudioClip.h"
#include <vector>
#include "AudioLibrary.h"
class Scene;

class AudioComponent : public Component
{
public:
	AudioComponent();
	~AudioComponent();
	
	void AddAudio(AudioList aSound);
	void PlayAudio();
	void StopAudio();
	void SetRadius(const float& aRadius);
	void LockAudio(AudioList aSound);
	void UnLockAudio(AudioList aSound);


	void Update(Transform& aTransform, GameObject& aGameObject) override;

	float myVolume = 0;
	AudioList myAudio;
private:
	std::vector<AudioList> myAudioList;
	float myRadius = 150.0f;
	float myMinVolume = 0.1f;
	float myMaxVolume = 0.4f;
	float myAudioSpectrum = 0;
	float myDistanceToPlayer = 0;
	bool myHasBeenAdded = false;
	Scene* myScene;
};

