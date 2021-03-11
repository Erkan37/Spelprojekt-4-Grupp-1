#pragma once
#include "../External/Headers/CU/Vector2.hpp"
#include <vector>

class Enemy;
class Scene;

class EnemyFactory
{
public:
	void ReadEnemies(Scene* aLevelScene, const std::string& aFilePath);
	Enemy* CreateEnemy(Scene* aLevelScene, std::vector<v2f>& someCoordinates);
};

