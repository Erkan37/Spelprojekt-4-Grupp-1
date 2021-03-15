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
	PlayerData();
	float myMaxSpeed;
	float myAcceleration;
	float myRetardation;
	float myLerpAcceleration;
	float myPlatformVelocityRetardation;
	float myCoyoteTime;
	float myJumpVelocity;
	float myDoubleJumpVelocity;
	float myMaxFallSpeed;
	float myLedgeJumpVelocity;
	float myJumpWhenFallingTime;
	float myTriggerFallingSpeed;

	float myDieVibrationStrength;
	float myLandVibrationStrength;
	float mySpringsVibrationStrength;
	float myDieVibrationLength;
	float myLandVibrationLength;
	float mySpringsVibrationLength;

	float myDieShakeDuration;
	float myDieShakeIntensity;
	float myDieShakeDropOff;
	float myLandShakeDuration;
	float myLandShakeIntensity;
	float myLandShakeDropOff;
	float mySpringShakeDuration;
	float mySpringShakeIntensity;
	float mySpringShakeDropOff;
	~PlayerData() override {}
};
struct EnemyData : public Data
{
	EnemyData();
	float myMoveSpeed;
	~EnemyData() override {}
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
	void AssignPlayerValues(const rapidjson::Document &aDoc);

	//Master Document
	rapidjson::Document myMasterDoc;

	//Data Structs
	PlayerData myPlayerData;
	EnemyData myEnemyData;
	std::vector<rapidjson::Document> myLevelVector;

};
