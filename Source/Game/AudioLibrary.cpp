#include "stdafx.h"
#include "AudioLibrary.h"
#include "AudioClip.h"

AudioLibrary::AudioLibrary()
{
	myAudioList.insert_or_assign(AudioList::BashRelease,     new AudioClip("Sounds/Effects/Bash.wav",             false, 0.4f, 0, 1, AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::CollectableV1,   new AudioClip("Sounds/Effects/Collectible_V1.wav",   false, 0.2f, 0, 1, AudioLayer::SoundEffect));

	myAudioList.insert_or_assign(AudioList::WalkGravelRight, new AudioClip("Sounds/Effects/Gravel_right.wav",     false, 0.4f, 0, 1, AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::WalkGravelLeft,  new AudioClip("Sounds/Effects/Gravel_left.wav",      false, 0.4f, 0, 1, AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::WalkGrassRight,  new AudioClip("Sounds/Effects/WalkGrassRight.wav",   false, 0.4f, 0, 1, AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::WalkGrassLeft,   new AudioClip("Sounds/Effects/WalkGrassLeft.wav",    false, 0.4f, 0, 1, AudioLayer::SoundEffect));

	myAudioList.insert_or_assign(AudioList::LandOnGrassEasy, new AudioClip("Sounds/Effects/LandGrassEasy.wav",    false, 0.4f, 0, 1, AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::LandOnGrassHeavy,new AudioClip("Sounds/Effects/LandGrassHeavy.wav",   false, 0.2f, 0, 1, AudioLayer::SoundEffect));


	myAudioList.insert_or_assign(AudioList::BashCharge,      new AudioClip("Sounds/Effects/PushfromBash.wav",     false, 0.4f, 0, 1, AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::PlayerJump,      new AudioClip("Sounds/Effects/Jump.wav",             false, 0.4f, 0, 1, AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::WeakPlatform,    new AudioClip("Sounds/Effects/Temporaryplatform.wav",false, 0.2f, 0, 0.2f, AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::PlayerDeath,     new AudioClip("Sounds/Effects/death.wav",            false, 0.5f, 0, 1, AudioLayer::SoundEffect));
	//myAudioList[AudioList::ProjectileFly]->SetVolume(-0.80f);
}
