#include "stdafx.h"
#include "EnemyFactory.h"
#include "Enemy.h"

#include <vector>

NormalEnemy* EnemyFactory::CreateNormalEnemy(Scene* aLevelScene, std::vector<v2f>& someCoordinates, const float& aSpeed)
{
	NormalEnemy* enemy = new NormalEnemy(aLevelScene);
	enemy->InitEnemy(someCoordinates, aSpeed);
	return enemy;
}

ShootingEnemy* EnemyFactory::CreateShootingEnemy(Scene* aLevelScene, std::vector<v2f>& someCoordinates, const float& aSpeed)
{
	ShootingEnemy* enemy = new ShootingEnemy(aLevelScene);
	enemy->InitEnemy(someCoordinates, aSpeed);
	return enemy;
}