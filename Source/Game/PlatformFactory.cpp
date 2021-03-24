#include "stdafx.h"
#include "PlatformFactory.hpp"

#include "Platform.h"
#include "MovingPlatform.hpp"
#include "UnstablePlatform.hpp"
#include "DestructiblePlatform.hpp"
#include "DeadlyPlatform.hpp"

#include "Ledge.h"

#include "SpriteComponent.h"
#include "WaypointComponent.hpp"

Platform* PlatformFactory::CreateStaticPlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize, const bool aIsOneWay)
{
	Platform* staticPlatform = new Platform(aLevelScene);
	staticPlatform->Init(aCollisionSize, aSpriteSize, aPosition, aIsOneWay);
	return staticPlatform;
}

MovingPlatform* PlatformFactory::CreateMovingPlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize, const std::vector<v2f>& aWayPoints, const float& aSpeed)
{
	MovingPlatform* movingPlatform = new MovingPlatform(aLevelScene);

	movingPlatform->AddComponent<SpriteComponent>();
	std::string spritePath = "Sprites/Platforms/Moving6.dds";

	v2f adjustedSize = v2f(0.0f, 8.0f);
	if (aCollisionSize.x >= 40.0f)
	{
		adjustedSize.x = 48.0f;
		spritePath = "Sprites/Platforms/Moving6.dds";
	}
	else if (aCollisionSize.x >= 24.0f)
	{
		adjustedSize.x = 32.0f;
		spritePath = "Sprites/Platforms/Moving4.dds";
	}
	else
	{
		adjustedSize.x = 16.0f;
		spritePath = "Sprites/Platforms/Moving2.dds";
	}

	movingPlatform->Init(adjustedSize, adjustedSize, aPosition, true);
	movingPlatform->SetWaypoints(aWayPoints);
	movingPlatform->GetComponent<WaypointComponent>()->SetSpeed(aSpeed);
	movingPlatform->GetComponent<SpriteComponent>()->SetSpritePath(spritePath);
	movingPlatform->GetComponent<SpriteComponent>()->SetSize(adjustedSize);
	return movingPlatform;
}

UnstablePlatform* PlatformFactory::CreateUnstablePlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize, const float& aDestroyTime, const float& aRespawnTime)
{
	UnstablePlatform* unstablePlatform = new UnstablePlatform(aLevelScene);

	unstablePlatform->AddComponent<SpriteComponent>();
	std::string spritePath = "Sprites/Platforms/Unstable5.dds";

	v2f adjustedSize = v2f(0.0f, 8.0f);
	v2f adjustedSpriteSize = v2f(0.0f, 8.0f);
	if (aCollisionSize.x >= 40.0f)
	{
		adjustedSize.x = 40.0f;
		adjustedSpriteSize.x = 64.0f;
		spritePath = "Sprites/Platforms/Unstable5.dds";
	}
	else if (aCollisionSize.x >= 24.0f)
	{
		adjustedSize.x = 24.0f;
		adjustedSpriteSize.x = 32.0f;
		spritePath = "Sprites/Platforms/Unstable3.dds";
	}
	else
	{
		adjustedSize.x = 8.0f;
		adjustedSpriteSize.x = 8.0f;
		spritePath = "Sprites/Platforms/Unstable1.dds";
	}

	unstablePlatform->Init(adjustedSize, adjustedSize, aPosition, false);
	unstablePlatform->SetTimerProperties(aDestroyTime, aRespawnTime);
	unstablePlatform->GetComponent<SpriteComponent>()->SetSpritePath(spritePath);
	unstablePlatform->GetComponent<SpriteComponent>()->SetSize(adjustedSpriteSize);
	return unstablePlatform;
}

DestructiblePlatform* PlatformFactory::CreateDestructiblePlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize)
{
	DestructiblePlatform* destructiblePlatform = new DestructiblePlatform(aLevelScene);

	destructiblePlatform->AddComponent<SpriteComponent>();
	std::string spritePath = "Sprites/Platforms/BreakableWall.dds";

	v2f adjustedSize = v2f(0.0f, 0.0f);
	if (aCollisionSize.x >= 32.0f)
	{
		adjustedSize.x = 32.0f;
		adjustedSize.y = 24.0f;
		spritePath = "Sprites/Platforms/BreakableFloor.dds";
	}
	else
	{
		adjustedSize.x = 24.0f;
		adjustedSize.y = 32.0f;
		spritePath = "Sprites/Platforms/BreakableWall.dds";
	}


	destructiblePlatform->Init(adjustedSize, adjustedSize, aPosition, false);
	destructiblePlatform->GetComponent<SpriteComponent>()->SetSpritePath(spritePath);
	destructiblePlatform->GetComponent<SpriteComponent>()->SetSize(aSpriteSize);
	return destructiblePlatform;
}

DeadlyPlatform* PlatformFactory::CreateDeadlyPlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize)
{
	DeadlyPlatform* deadlyPlatform = new DeadlyPlatform(aLevelScene);
	deadlyPlatform->Init(aCollisionSize, aSpriteSize, aPosition, false);
	return deadlyPlatform;
}