#pragma once
#include <map>

class AudioClip;
enum class AudioList
{
	PlayerJump, PlayerDoubleJump, PlayerDeath, PlayerRespawn, PlayerHover, PlayerJumpPad,
	EnemyNormalIdle, EnemyShootingIdle, EnemyShooting,
	MenuMove, MenuSelect,
	GrabLedge, GrabLedge2, LeaveLedge,
	ButtonPress,
	SpikeDeath, SpikeHit,
	ProjectileFly, ProjectileHit,
	WeakPlatform, MovingPlatform,
	WalkGravelRight, WalkGravelLeft, WalkGrassRight, WalkGrassLeft, WalkStoneRight, WalkStoneLeft,
	LandOnGrassHeavy, LandOnGrassEasy, LandOnStoneHeavy, LandOnStoneLight,
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

