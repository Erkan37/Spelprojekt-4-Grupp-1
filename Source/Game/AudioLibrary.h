#pragma once
#include <map>

class AudioClip;
enum class AudioList
{
	SoundStart,
	PlayerJump, PlayerDoubleJump, PlayerLedgeGrab, PlayerDeath,
	EnemyNormalIdle, EnemyShootingIdle, EnemyShootingShot,
	ProjectileFly, ProjectileHit,
	WalkGravelRight, WalkGravelLeft,
	BashCharge, BashRelease,
	CollectableV1,
	SoundAmount
};

enum class AudioLayer
{
	SoundEffect, Music
};

class AudioLibrary
{
	//static AudioLibrary& GetInstance()
	//{
	//	static AudioLibrary lib;
	//	return lib;
	//}
	~AudioLibrary() = default;
	std::map<AudioList, AudioClip*> myAudioList;
	AudioLibrary();
	friend class AudioManager;
	friend class AudioClip;
};

