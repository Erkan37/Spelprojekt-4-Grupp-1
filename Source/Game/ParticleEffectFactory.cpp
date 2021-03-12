#include "stdafx.h"
#include "ParticleEffectFactory.h"
#include "ParticleStats.hpp"
#include "Scene.h"

#include "../External/Headers/rapidjson/document.h"
#include "../External/Headers/rapidjson/istreamwrapper.h"
#include <fstream>

ParticleEffectFactory::ParticleEffectFactory(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
{
}

void ParticleEffectFactory::ReadEffects(Scene* aLevelScene)
{
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
			stats.myIsRepeating = (*particleStat)["IsRepeating"].GetBool();
			stats.myEmitTime = (*particleStat)["EmitTime"].GetFloat();
			stats.myPauseTime = (*particleStat)["PauseTime"].GetFloat();
			stats.myStartScale = (*particleStat)["StartScale"].GetFloat();
			stats.myEndScale = (*particleStat)["EndScale"].GetFloat();
			stats.myMinBetweenSpawn = (*particleStat)["MinTimeBetweenSpawns"].GetFloat();
			stats.myMaxBetweenSpawn = (*particleStat)["MaxTimeBetweenSpawns"].GetFloat();
			stats.myMinStartSpeed = (*particleStat)["MinStartSpeed"].GetFloat();
			stats.myMaxStartSpeed = (*particleStat)["MaxStartSpeed"].GetFloat();
			stats.myMinAcceleration = (*particleStat)["MinAcceleration"].GetFloat();
			stats.myMaxAcceleration = (*particleStat)["MaxAcceleration"].GetFloat();
			stats.myParticleAngleInterval = (*particleStat)["ParticleAngleInterval"].GetFloat();
			stats.myMinParticleAngularVel = (*particleStat)["MinParticleAngularVel"].GetFloat();
			stats.myMaxParticleAngularVel = (*particleStat)["MaxParticleAngularVel"].GetFloat();
			stats.myEmitterAngle = (*particleStat)["EmitterAngle"].GetFloat();
			stats.myEmitterWidth = (*particleStat)["EmitterWidth"].GetFloat();
			stats.myMinEmitterAngularVelocity = (*particleStat)["MinEmitterAngularVelocity"].GetFloat();
			stats.myMaxEmitterAngularVelocity = (*particleStat)["MaxEmitterAngularVelocity"].GetFloat();
			stats.myMinParticleLifeTime = (*particleStat)["MinParticleLifeTime"].GetFloat();
			stats.myMaxParticleLifeTime = (*particleStat)["MaxParticleLifeTime"].GetFloat();
			stats.myEmitterLifeTime = (*particleStat)["EmitterLifeTime"].GetFloat();
			stats.myStartColor = { (*particleStat)["StartColor"][0].GetFloat(), (*particleStat)["StartColor"][1].GetFloat(), (*particleStat)["StartColor"][2].GetFloat(), (*particleStat)["StartColor"][3].GetFloat() };
			stats.myEndColor = { (*particleStat)["EndColor"][0].GetFloat(), (*particleStat)["EndColor"][1].GetFloat(), (*particleStat)["EndColor"][2].GetFloat(), (*particleStat)["EndColor"][3].GetFloat() };

			std::shared_ptr<ParticleEffect> particle = std::make_shared<ParticleEffect>();
			particle->Init(stats, aLevelScene);
			myEffects.push_back(particle);
		}

		particleFile.close();
		index++;
		
	}

	effectObjectFile.close();


}

void ParticleEffectFactory::Init()
{
}

void ParticleEffectFactory::Update(const float& aDeltaTime)
{
	for (auto effect : myEffects)
		effect->Update(aDeltaTime);
}

void ParticleEffectFactory::SpawnEffect(const v2f aPosition, const eParticleEffects aEffectType)
{
	switch (aEffectType)
	{
	case eParticleEffects::RunEffect:
	{
		myEffects[static_cast<int>(aEffectType)]->SetPosition(aPosition);
		myEffects[static_cast<int>(aEffectType)]->SetIsActive(true);
		break;
	}
	case eParticleEffects::FallEffect:
	{
		myEffects[static_cast<int>(aEffectType)]->SetPosition(aPosition);
		myEffects[static_cast<int>(aEffectType)]->SetIsActive(true);
		break;
	}
	}
}
