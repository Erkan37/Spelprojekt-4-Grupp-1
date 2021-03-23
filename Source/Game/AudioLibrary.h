#pragma once
#include <map>

class AudioClip;
enum class AudioList
{
	PlayerJump, PlayerDoubleJump, PlayerLedgeGrab, PlayerDeath,
	EnemyNormalIdle, EnemyShootingIdle, EnemyShootingShot,
	ProjectileFly, ProjectileHit,
	WeakPlatform, MovingPlatform,
	WalkGravelRight, WalkGravelLeft, WalkGrassRight, WalkGrassLeft,
	LandOnGrassHeavy, LandOnGrassEasy,
	BashCharge, BashRelease,
	CollectableV1,
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

