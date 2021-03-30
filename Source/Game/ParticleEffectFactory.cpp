#include "stdafx.h"
#include "ParticleEffectFactory.h"
#include "ParticleStats.hpp"
#include "Scene.h"
#include "LevelScene.h"
#include "Player.hpp"

#include "../External/Headers/rapidjson/document.h"
#include "../External/Headers/rapidjson/istreamwrapper.h"
#include <fstream>

ParticleEffectFactory::ParticleEffectFactory(Scene* aLevelScene)
{
	//myCreatedEffects.clear();
}

void ParticleEffectFactory::ReadEffects(Scene* aLevelScene)
{
	myScene = aLevelScene;
	LevelScene* levelScene = dynamic_cast<LevelScene*>(aLevelScene);
	Player* player = dynamic_cast<Player*>(levelScene->GetPlayer());
	myPlayer = player;

	assert(player != NULL);

	int index = {};
	std::ifstream effectObjectFile("JSON/Particles/MasterParticles.json");
	rapidjson::IStreamWrapper effectObjectStream(effectObjectFile);

	rapidjson::Document effectDocuments;
	effectDocuments.ParseStream(effectObjectStream);

	for (rapidjson::Value::ConstValueIterator effectPaths = effectDocuments["particlesPath"].Begin(); effectPaths != effectDocuments["particlesPath"].End(); ++effectPaths)
	{
		std::string path = "JSON/Particles/infile";
		path.append(std::to_string(index) + ".json");

		std::ifstream particleFile(path);
		rapidjson::IStreamWrapper particleStream(particleFile);

		rapidjson::Document particleDocuments;
		particleDocuments.ParseStream(particleStream);

		for (rapidjson::Value::ConstValueIterator particleStat = particleDocuments["particle"].Begin(); particleStat != particleDocuments["particle"].End(); ++particleStat)
		{
			ParticleStats stats;
			stats.myEffectTypeIndex = (*particleStat)["EffectTypeIndex"].GetInt();
			stats.myEffectType = (*particleStat)["EffectType"].GetString();
			stats.mySpritePath = (*particleStat)["SpritePath"].GetString();
			stats.myLockedPosition = (*particleStat)["LockPosition"].GetBool();
			stats.myEmitTime = (*particleStat)["EmitTime"].GetFloat();
			stats.myPauseTime = (*particleStat)["PauseTime"].GetFloat();
			stats.myStartScale = (*particleStat)["StartScale"].GetFloat();
			stats.myEndScale = (*particleStat)["EndScale"].GetFloat();
			stats.myMinBetweenSpawn = (*particleStat)["MinTimeBetweenSpawns"].GetFloat();
			stats.myMaxBetweenSpawn = (*particleStat)["MaxTimeBetweenSpawns"].GetFloat();
			stats.myMinStartSpeed = (*particleStat)["MinStartSpeed"].GetFloat();
			stats.myMaxStartSpeed = (*particleStat)["MaxStartSpeed"].GetFloat();
			stats.myAcceleration = (*particleStat)["Acceleration"].GetFloat();
			stats.myMinParticleAngularVel = (*particleStat)["MinParticleAngularVel"].GetFloat();
			stats.myMaxParticleAngularVel = (*particleStat)["MaxParticleAngularVel"].GetFloat();
			stats.myEmitterAngle = (*particleStat)["EmitterAngle"].GetFloat();
			stats.myEmitterWidth = (*particleStat)["EmitterWidth"].GetFloat();
			stats.myEmitterHeigth = (*particleStat)["EmitterHeigth"].GetFloat();
			stats.myMinEmitterAngularVelocity = (*particleStat)["MinEmitterAngularVelocity"].GetFloat();
			stats.myMaxEmitterAngularVelocity = (*particleStat)["MaxEmitterAngularVelocity"].GetFloat();
			stats.myMinParticleLifeTime = (*particleStat)["MinParticleLifeTime"].GetFloat();
			stats.myMaxParticleLifeTime = (*particleStat)["MaxParticleLifeTime"].GetFloat();
			stats.myEmitterLifeTime = (*particleStat)["EmitterLifeTime"].GetFloat();
			stats.myOffset = { (*particleStat)["Offset"][0]["X"].GetFloat(), (*particleStat)["Offset"][1]["Y"].GetFloat() };

			stats.myEmitterAngular = { (*particleStat)["EmitterAngular"][0].GetFloat(), (*particleStat)["EmitterAngular"][1].GetFloat(), (*particleStat)["EmitterAngular"][2].GetFloat(), (*particleStat)["EmitterAngular"][3].GetFloat() };
			stats.myStartColor = { (*particleStat)["StartColor"][0].GetFloat(), (*particleStat)["StartColor"][1].GetFloat(), (*particleStat)["StartColor"][2].GetFloat(), (*particleStat)["StartColor"][3].GetFloat() };
			stats.myEndColor = { (*particleStat)["EndColor"][0].GetFloat(), (*particleStat)["EndColor"][1].GetFloat(), (*particleStat)["EndColor"][2].GetFloat(), (*particleStat)["EndColor"][3].GetFloat() };


			myEffects.push_back(stats);
		}

		particleFile.close();
		index++;
		
	}

	effectObjectFile.close();


}

void ParticleEffectFactory::Init()
{
	//SpawnCharacterEffects();
}


void ParticleEffectFactory::SpawnEffect(v2f aPosition, const eParticleEffects aEffectType)
{
	switch (aEffectType)
	{
	case eParticleEffects::RunEffect:
	{
		ParticleEffect* effect = new ParticleEffect(myScene);
		effect->Init(myEffects[static_cast<int>(aEffectType)], myPlayer);
		effect->SetPosition(aPosition);
		effect->SetIsActive(true);
		//myCreatedEffects.push_back(effect);
		break;
	}
	case eParticleEffects::FallEffect:
	{
		ParticleEffect* effect = new ParticleEffect(myScene);
		effect->Init(myEffects[static_cast<int>(eParticleEffects::FallEffect)], myPlayer);
		effect->SetPosition(aPosition);
		effect->SetIsActive(true);
		//myCreatedEffects.push_back(effect);
		break;
	}
	case eParticleEffects::TestEffect:
	{
		ParticleEffect* effect = new ParticleEffect(myScene);
		effect->Init(myEffects[static_cast<int>(eParticleEffects::TestEffect)], myPlayer);
		effect->SetPosition(aPosition);
		effect->SetIsActive(true);
		break;
	}
	}
}

void ParticleEffectFactory::SpawnCharacterEffects()
{
	ParticleEffect* effect = new ParticleEffect(myScene);
	effect->Init(myEffects[static_cast<int>(eParticleEffects::RunEffect)], myPlayer);
	effect->SetIsActive(true);
	//myCreatedEffects.push_back(effect);
}

void ParticleEffectFactory::SpawnCharacterEffects2()
{
	ParticleEffect* effect = new ParticleEffect(myScene);
	effect->Init(myEffects[static_cast<int>(eParticleEffects::FallEffect)], myPlayer);
	effect->SetIsActive(true);
	//myCreatedEffects.push_back(effect);
}
