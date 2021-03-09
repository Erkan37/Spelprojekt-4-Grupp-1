#include "stdafx.h"
#include "PlatformFactory.hpp"

#include "Platform.h"
#include "MovingPlatform.hpp"
#include "UnstablePlatform.hpp"
#include "DestructiblePlatform.hpp"

void PlatformFactory::CreatePlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize, const bool aIsOneWay)
{
	Platform* staticPlatform = new Platform(aLevelScene);
	staticPlatform->Init(v2f(aCollisionSize.x, aCollisionSize.y), v2f(aSpriteSize.x, aSpriteSize.y), v2f(aPosition.x, aPosition.y), aIsOneWay);
}

void PlatformFactory::CreatePlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize, const std::vector<v2f>& aWayPoints)
{
	MovingPlatform* movingPlatform = new MovingPlatform(aLevelScene);
	movingPlatform->Init(v2f(aCollisionSize.x, aCollisionSize.y), v2f(aSpriteSize.x, aSpriteSize.y), v2f(aPosition.x, aPosition.y), true);
}

void PlatformFactory::CreatePlatform(Scene* aLevelScene, const v2f& aPosition, const v2f& aCollisionSize, const v2f& aSpriteSize, const float& aDestroyTime, const float& aRespawnTime)
{

}