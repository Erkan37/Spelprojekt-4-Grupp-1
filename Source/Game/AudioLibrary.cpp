#include "stdafx.h"
#include "AudioLibrary.h"
#include "AudioClip.h"

AudioLibrary::AudioLibrary()
{
	myAudioList.insert_or_assign(AudioList::BashRelease, new AudioClip("Sounds/Effects/Bash.wav", false, 0.4f, AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::CollectableV1, new AudioClip("Sounds/Effects/Collectible_V1.wav", false, 0.4f, AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::WalkGravelRight, new AudioClip("Sounds/Effects/Gravel_right.wav", false, 0.4f, AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::WalkGravelLeft, new AudioClip("Sounds/Effects/Gravel_left.wav", false, 0.4f, AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::BashCharge, new AudioClip("Sounds/Effects/PushfromBash.wav", false, 0.4f, AudioLayer::SoundEffect));
	myAudioList.insert_or_assign( AudioList::PlayerJump, new AudioClip("Sounds/Effects/Jump.wav", false, 0.4f, AudioLayer::SoundEffect) );
	//myAudioList[AudioList::ProjectileFly]->SetVolume(-0.80f);
}
