#include "stdafx.h"
#include "EnemyFactory.h"
#include "Enemy.h"

#include "../External/Headers/rapidjson/document.h"
#include "../External/Headers/rapidjson/istreamwrapper.h"
#include <fstream>
#include <vector>

void EnemyFactory::ReadEnemies(Scene* aLevelScene, const std::string& aFilePath)
{
	std::ifstream enemyFile(aFilePath);
	rapidjson::IStreamWrapper enemyFileStream(enemyFile);

	rapidjson::Document Enemies;
	Enemies.ParseStream(enemyFileStream);

	for (rapidjson::Value::ConstValueIterator enemy = Enemies["Enemies"].Begin(); enemy != Enemies["Enemies"].End(); ++enemy)
	{
		std::vector<v2f> tempCoordinates;
		for (rapidjson::Value::ConstValueIterator waypoint = (*enemy)["Coordinates"].Begin(); waypoint != (*enemy)["Coordinates"].End(); ++waypoint)
		{
			const v2f coordinate = v2f(((*waypoint)["X"].GetFloat()), ((*waypoint)["Y"].GetFloat()));
			tempCoordinates.push_back(coordinate);
		}
		CreateEnemy(aLevelScene, tempCoordinates);
		tempCoordinates.empty();
	}

	enemyFile.close();
}

Enemy* EnemyFactory::CreateEnemy(Scene* aLevelScene, std::vector<v2f>& someCoordinates)
{
	Enemy* enemy = new Enemy(aLevelScene, someCoordinates);
	return enemy;
}