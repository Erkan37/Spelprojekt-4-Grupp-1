#include "stdafx.h"
#include "AudioLibrary.h"
#include "AudioClip.h"

AudioLibrary::AudioLibrary()
{
	myAudioList.insert_or_assign(AudioList::BashRelease,     new AudioClip("Sounds/Effects/Bash.wav",             false, 0.4f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::CollectableV1,   new AudioClip("Sounds/Effects/Collectible_V1.wav",   false, 0.2f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::SpikeHit,        new AudioClip("Sounds/Effects/SpikeHit.wav",         false, 0.3f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::PlayerRespawn,   new AudioClip("Sounds/Effects/Respawn.wav",          false, 0.1f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::PlayerHover,     new AudioClip("Sounds/Effects/HoverAbility.wav",     true,  0.2f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::PlayerJumpPad,   new AudioClip("Sounds/Effects/spring.wav",           false, 0.4f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::SpikeDeath,      new AudioClip("Sounds/Effects/EnemySpeared.mp3",     false, 0.8f, 0, 1,    AudioLayer::SoundEffect));

	myAudioList.insert_or_assign(AudioList::EnemyShooting,   new AudioClip("Sounds/Effects/EnemyFire.wav",        false, 0.1f, 0, 1,    AudioLayer::SoundEffect));

	myAudioList.insert_or_assign(AudioList::GrabLedge,       new AudioClip("Sounds/Effects/GrabLedge.wav",        false, 0.1f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::GrabLedge2,      new AudioClip("Sounds/Effects/GrabLedge2.wav",       false, 0.1f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::LeaveLedge,      new AudioClip("Sounds/Effects/LeaveLedge.wav",       false, 0.1f, 0, 1,    AudioLayer::SoundEffect));

	myAudioList.insert_or_assign(AudioList::MenuMove,        new AudioClip("Sounds/Effects/MenuMove.wav",         false, 0.2f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::MenuSelect,      new AudioClip("Sounds/Effects/MenuSelect.wav",       false, 0.2f, 0, 1,    AudioLayer::SoundEffect));

	myAudioList.insert_or_assign(AudioList::WalkGravelRight, new AudioClip("Sounds/Effects/Gravel_right.wav",     false, 0.4f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::WalkGravelLeft,  new AudioClip("Sounds/Effects/Gravel_left.wav",      false, 0.4f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::WalkGrassRight,  new AudioClip("Sounds/Effects/WalkGrassRight.wav",   false, 0.4f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::WalkGrassLeft,   new AudioClip("Sounds/Effects/WalkGrassLeft.wav",    false, 0.4f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::WalkStoneRight,  new AudioClip("Sounds/Effects/WalkStoneRight.wav",   false, 0.4f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::WalkStoneLeft,   new AudioClip("Sounds/Effects/WalkStoneLeft.wav",    false, 0.4f, 0, 1,    AudioLayer::SoundEffect));

	myAudioList.insert_or_assign(AudioList::LandOnGrassEasy, new AudioClip("Sounds/Effects/LandGrassEasy.wav",    false, 0.4f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::LandOnGrassHeavy,new AudioClip("Sounds/Effects/LandGrassHeavy.wav",   false, 0.2f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::LandOnStoneHeavy,new AudioClip("Sounds/Effects/LandStoneHeavy.wav",   false, 0.4f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::LandOnStoneLight,new AudioClip("Sounds/Effects/LandStoneLight.wav",   false, 0.2f, 0, 1,    AudioLayer::SoundEffect));

	myAudioList.insert_or_assign(AudioList::MovingPlatform,  new AudioClip("Sounds/Effects/MovingPlatform.wav",   true,  0.1f, 0, 0.15f,AudioLayer::SoundEffect));

	myAudioList.insert_or_assign(AudioList::BashCharge,      new AudioClip("Sounds/Effects/PushfromBash.wav",     false, 0.4f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::PlayerJump,      new AudioClip("Sounds/Effects/Jump.wav",             false, 0.4f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::WeakPlatform,    new AudioClip("Sounds/Effects/Temporaryplatform.wav",false, 0.2f, 0, 0.2f, AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::PlayerDeath,     new AudioClip("Sounds/Effects/death.wav",            false, 0.5f, 0, 1,    AudioLayer::SoundEffect));
	myAudioList.insert_or_assign(AudioList::ButtonPress,     new AudioClip("Sounds/Effects/ButtonPress.wav",      false, 0.5f, 0, 1,    AudioLayer::SoundEffect));
}
