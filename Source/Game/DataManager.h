#pragma once
#include "rapidjson/document.h"
#include <map>

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
	~PlayerData() override {}

	// Float Components
	enum class PlayerFloatEnum
	{
		Max_Speed,
		Acceleration,
		Retardation,
		Lerp_Acceleration,
		Platform_Velocity_Retardation,
		Coyote_Time,
		Jump_Velocity,
		Double_Jump_Velocity,
		Max_Fall_Speed,
		Ledge_Jump_Velocity,
		Jump_When_Falling_Time,
		Trigger_Falling_Speed,
		Die_Vibration_Strength,
		Land_Vibration_Strength,
		Springs_Vibration_Strength,
		Die_Vibration_Length,
		Land_Vibration_Length,
		Springs_Vibration_Length,
		Die_Shake_Duration,
		Die_Shake_Intensity,
		Die_Shake_DropOff,
		Land_Shake_Duration,
		Land_Shake_Intensity,
		Land_Shake_DropOff,
		Spring_Shake_Duration,
		Spring_Shake_Intensity,
		Spring_Shake_DropOff,

		Player_FloatEnum_Size
	};
	std::map<PlayerFloatEnum, std::string> myFloatNameMap;
	std::map<PlayerFloatEnum, float> myFloatValueMap;
};
struct EnemyData : public Data
{
	EnemyData();
	~EnemyData() override {}

	// Float Components
	enum class EnemyFloatEnum
	{
		NE_SpriteSizeX,
		NE_SpriteSizeY,
		NE_CollisionSizeX,
		NE_CollisionSizeY,
		SE_SpriteSizeX,
		SE_SpriteSizeY,
		SE_CollisionSizeX,
		SE_CollisionSizeY,
		FireRate,
		FireRadius,
		P_SpriteSizeX,
		P_SpriteSizeY,
		P_CollisionSizeX,
		P_CollisionSizeY,
		Speed,

		Enemy_FloatEnum_Size
	};
	std::map<EnemyFloatEnum, std::string> myFloatNameMap;
	std::map<EnemyFloatEnum, float> myFloatValueMap;
};
struct SaveFile: public Data
{
	SaveFile();
	~SaveFile() override {}

	// Float Components
	enum class SaveFileEnum
	{


		SaveFile_Size
	};
	std::map<SaveFileEnum, std::string> myFloatNameMap;
	std::map<SaveFileEnum, float> myFloatValueMap;
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

	const rapidjson::Document& GetLevel(const unsigned int aLevelIndex) const;
	const int GetLevelCount();



private:
	//Private Methods
	DataManager();
	void ReadFileIntoDocument(std::string aFilePath, rapidjson::Document& anOutDoc);
	void AssignValues(const DataEnum anEnum, const rapidjson::Document& aDoc);

	//Master Documents
	rapidjson::Document myMasterDoc;
	rapidjson::Document myLevelMasterDoc;

	//Data Structs
	PlayerData myPlayerData;
	EnemyData myEnemyData;
	std::vector<rapidjson::Document> myLevelVector;

};
