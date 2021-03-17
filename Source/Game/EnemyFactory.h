#pragma once
#include "../External/Headers/CU/Vector2.hpp"
#include <vector>

class Enemy;
class NormalEnemy;
class ShootingEnemy;
class Scene;

class EnemyFactory
{
public:
	void ReadEnemies(Scene* aLevelScene, const std::string& aFilePath);
	NormalEnemy* CreateNormalEnemy(Scene* aLevelScene, std::vector<v2f>& someCoordinates, const float& aSpeed);
	ShootingEnemy* CreateShootingEnemy(Scene* aLevelScene, std::vector<v2f>& someCoordinates, const float& aSpeed);
};

