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

		const int enemyType = (*enemy)["Type"].GetInt();
		switch (enemyType)
		{
		case 0: CreateNormalEnemy(aLevelScene, tempCoordinates); break;
		case 1: CreateShootingEnemy(aLevelScene, tempCoordinates); break;
		default: CreateNormalEnemy(aLevelScene, tempCoordinates); break;
		}
		tempCoordinates.empty();
	}

	enemyFile.close();
}

NormalEnemy* EnemyFactory::CreateNormalEnemy(Scene* aLevelScene, std::vector<v2f>& someCoordinates)
{
	NormalEnemy* enemy = new NormalEnemy(aLevelScene);
	enemy->InitEnemy(someCoordinates);
	return enemy;
}

ShootingEnemy* EnemyFactory::CreateShootingEnemy(Scene* aLevelScene, std::vector<v2f>& someCoordinates)
{
	ShootingEnemy* enemy = new ShootingEnemy(aLevelScene);
	enemy->InitEnemy(someCoordinates);
	return enemy;
}