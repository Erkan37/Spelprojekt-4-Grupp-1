#pragma once
#include "rapidjson/document.h"

enum class DataEnum
{
	player = 0,
	enemy = 1,

	data_enum_size = 2
};
struct Data
{
	Data() = default;
	virtual ~Data() {};
};
struct PlayerData : public Data
{
	PlayerData() = default;
	float myMaxSpeed;
	float myAcceleration;
	~PlayerData() override
	{}
};
struct EnemyData : public Data
{
	EnemyData() = default;
	float myMoveSpeed;
	int myHealth;
	~EnemyData() override
	{}
};

class DataManager
{
public:
	// Singleton Methods
	static DataManager& GetInstance()
	{
		static DataManager instance;
		return instance;
	}
	DataManager(DataManager& aDataManager) = delete;
	void operator=(const DataManager&) = delete;
	~DataManager() = default;

	Data& GetDataStruct(const DataEnum aDataEnum);
	void SetDataStruct(const DataEnum aDataEnum);

private:
	//Private Methods
	DataManager();
	void ReadFileIntoDocument(std::string aFilePath, rapidjson::Document& anOutDoc);

	//Master Document
	rapidjson::Document myMasterDoc;

	//Data Structs
	PlayerData myPlayerData;
	EnemyData myEnemyData;
	std::vector<rapidjson::Document> myLevelVector;

};
