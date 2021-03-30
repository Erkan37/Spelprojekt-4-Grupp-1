#include "stdafx.h"
#include "DataManager.h"
#include <fstream>
#include <sstream>
#include <cassert>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>

DataManager::DataManager()
{
	//Assign MasterDoc & SaveFile
	ReadFileIntoDocument("Master.json", myMasterDoc);
	ReadFileIntoDocument("JSON/SaveFile.json", mySaveFile);

	//Assign LevelDocs
	ReadFileIntoDocument("Levels/LevelMaster.json", myLevelMasterDoc);
	assert(myLevelMasterDoc["FilePathArray"].IsArray());
	for (size_t i = 0; i < myLevelMasterDoc["FilePathArray"].GetArray().Size(); i++)
	{
		myLevelVector.push_back(rapidjson::Document());
		ReadFileIntoDocument(myLevelMasterDoc["FilePathArray"].GetArray()[i]["FilePath"].GetString(), myLevelVector.back());
	}

	//Assign PlayerDoc
	std::string playerDataPath = myMasterDoc["PlayerData"].GetString();
	rapidjson::Document playerDoc;
	ReadFileIntoDocument(playerDataPath, playerDoc);
	//Assign Player Values
	AssignValues(DataEnum::player, playerDoc);

	//Assign EnemyDoc
	std::string enemyDataPath = myMasterDoc["EnemyData"].GetString();
	rapidjson::Document enemyDoc;
	ReadFileIntoDocument(enemyDataPath, enemyDoc);
	//Assign Enemy Values
	AssignValues(DataEnum::enemy, enemyDoc);
}

void DataManager::SetDataStruct(const DataEnum aDataEnum)
{
	rapidjson::Document tempDoc;
	std::string tempDataPath;

	switch (aDataEnum)
	{
	case DataEnum::player:
	{
		tempDataPath = myMasterDoc["PlayerData"].GetString();
		ReadFileIntoDocument(tempDataPath, tempDoc);

		for (size_t i = 0; i < static_cast<size_t>(PlayerData::PlayerFloatEnum::Player_FloatEnum_Size); i++)
		{
			PlayerData::PlayerFloatEnum enumValue = static_cast<PlayerData::PlayerFloatEnum>(i);
			tempDoc[myPlayerData.myFloatNameMap[enumValue].data()].SetFloat(myPlayerData.myFloatValueMap[enumValue]);
		}
	}
	break;
	case DataEnum::enemy:
	{
		tempDataPath = myMasterDoc["EnemyData"].GetString();
		ReadFileIntoDocument(tempDataPath, tempDoc);

		for (size_t i = 0; i < static_cast<size_t>(EnemyData::EnemyFloatEnum::Enemy_FloatEnum_Size); i++)
		{
			EnemyData::EnemyFloatEnum enumValue = static_cast<EnemyData::EnemyFloatEnum>(i);
			tempDoc[myEnemyData.myFloatNameMap[enumValue].data()].SetFloat(myEnemyData.myFloatValueMap[enumValue]);
		}
	}
	break;
	default:
		assert((false) && "Invalid Enum given to DataManager::SetDataStruct().");
		break;
	}

	//Accepterar Input till Json filen.
	std::ofstream ofs{ tempDataPath };
	rapidjson::OStreamWrapper osw{ ofs };
	rapidjson::Writer<rapidjson::OStreamWrapper> writer{ osw };
	tempDoc.Accept(writer);
}
Data& DataManager::GetDataStruct(const DataEnum aDataEnum)
{
	switch (aDataEnum)
	{
	case DataEnum::player:
	{
		return myPlayerData;
	}
	break;
	case DataEnum::enemy:
	{
		return myEnemyData;
	}
	break;
	default:
	{
		assert((false) && "Invalid Enum given to DataManager::GetDataStruct().");
		return Data();
	}
	break;
	}
}
const rapidjson::Document& DataManager::GetLevel(const unsigned int aLevelIndex) const
{
	if (aLevelIndex < 0 || aLevelIndex >= myLevelVector.size())
	{
		return myLevelVector[0];
	}

	return myLevelVector[aLevelIndex];
}

void DataManager::ReadFileIntoDocument(std::string aFilePath, rapidjson::Document& anOutDoc)
{
	std::ifstream dataFile(aFilePath);
	std::ostringstream outStringStream;
	outStringStream << dataFile.rdbuf();
	std::string outString = outStringStream.str();
	anOutDoc.Parse(outString.c_str());
	dataFile.close();
}

// Constructors är bara här för att undvika varningar.
PlayerData::PlayerData()
{
	for (size_t i = 0; i < static_cast<size_t>(PlayerData::PlayerFloatEnum::Player_FloatEnum_Size); i++)
	{
		myFloatValueMap[static_cast<PlayerData::PlayerFloatEnum>(i)] = 0.0f;
	}
}
EnemyData::EnemyData()
{
	for (size_t i = 0; i < static_cast<size_t>(EnemyData::EnemyFloatEnum::Enemy_FloatEnum_Size); i++)
	{
		myFloatValueMap[static_cast<EnemyData::EnemyFloatEnum>(i)] = 0.0f;
	}
}

// Assign Methods
void DataManager::AssignValues(const DataEnum anEnum, const rapidjson::Document &aDoc)
{
	switch (anEnum)
	{
	case DataEnum::player:
	{
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Acceleration] = "Acceleration";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Max_Speed] = "MaxSpeed";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Retardation] = "Retardation";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Lerp_Acceleration] = "Lerp Acceleration";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Platform_Velocity_Retardation] = "Platform Velocity Retardation";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Coyote_Time] = "Coyote Time";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Jump_Velocity] = "Jump Velocity";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Double_Jump_Velocity] = "Double Jump Velocity";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Max_Fall_Speed] = "Max Fall Speed";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Ledge_Jump_Velocity] = "Ledge Jump Velocity";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Jump_When_Falling_Time] = "Jump When Falling Time";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Trigger_Falling_Speed] = "Trigger Falling Speed";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Die_Vibration_Strength] = "Die Vibration Strength";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Land_Vibration_Strength] = "Land Vibration Strength";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Springs_Vibration_Strength] = "Springs Vibration Strength";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Die_Vibration_Length] = "Die Vibration Length";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Land_Vibration_Length] = "Land Vibration Length";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Springs_Vibration_Length] = "Springs Vibration Length";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Die_Shake_Duration] = "Die Shake Duration";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Die_Shake_Intensity] = "Die Shake Intensity";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Die_Shake_DropOff] = "Die Shake DropOff";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Land_Shake_Duration] = "Land Shake Duration";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Land_Shake_Intensity] = "Land Shake Intensity";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Land_Shake_DropOff] = "Land Shake DropOff";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Spring_Shake_Duration] = "Spring Shake Duration";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Spring_Shake_Intensity] = "Spring Shake Intensity";
		myPlayerData.myFloatNameMap[PlayerData::PlayerFloatEnum::Spring_Shake_DropOff] = "Spring Shake DropOff";

		for (size_t i = 0; i < static_cast<size_t>(PlayerData::PlayerFloatEnum::Player_FloatEnum_Size); i++)
		{
			PlayerData::PlayerFloatEnum enumValue = static_cast<PlayerData::PlayerFloatEnum>(i);
			myPlayerData.myFloatValueMap[enumValue] = aDoc[myPlayerData.myFloatNameMap[enumValue].data()].GetFloat();
		}
	}
	break;
	case DataEnum::enemy:
	{
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::NE_SpriteSizeX] = "NE_SpriteSizeX";
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::NE_SpriteSizeY] = "NE_SpriteSizeY";
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::NE_CollisionSizeX] = "NE_CollisionSizeX";
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::NE_CollisionSizeY] = "NE_CollisionSizeY";
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::SE_SpriteSizeX] = "SE_SpriteSizeX";
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::SE_SpriteSizeY] = "SE_SpriteSizeY";
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::SE_CollisionSizeX] = "SE_CollisionSizeX";
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::SE_CollisionSizeY] = "SE_CollisionSizeY";
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::FireRate] = "FireRate";
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::FireRadius] = "FireRadius";
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::P_SpriteSizeX] = "P_SpriteSizeX";
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::P_SpriteSizeY] = "P_SpriteSizeY";
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::P_CollisionSizeX] = "P_CollisionSizeX";
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::P_CollisionSizeY] = "P_CollisionSizeY";
		myEnemyData.myFloatNameMap[EnemyData::EnemyFloatEnum::Speed] = "Speed";

		for (size_t i = 0; i < static_cast<size_t>(EnemyData::EnemyFloatEnum::Enemy_FloatEnum_Size); i++)
		{
			EnemyData::EnemyFloatEnum enumValue = static_cast<EnemyData::EnemyFloatEnum>(i);
			myEnemyData.myFloatValueMap[enumValue] = aDoc[myEnemyData.myFloatNameMap[enumValue].data()].GetFloat();
		}
	}
	break;
	default:
		assert((false) && "Invalid Enum given to DataManager::AssignValues().");
		break;
	}
}

const int DataManager::GetLevelCount()
{
	return static_cast<int>(myLevelVector.size());
}

void DataManager::SaveBonfireState(const unsigned int anIndex, const bool aState)
{
	assert((mySaveFile["Bonfires"].IsArray()) && "Bonfires is not Array.");
	assert((mySaveFile["Bonfires"][anIndex]["Bonfire"].IsObject()) && "Bonfire is not Object.");
	assert((mySaveFile["Bonfires"][anIndex]["Bonfire"]["IsActive"].IsBool()) && "IsActive is not Boolean.");

	std::string dataPath = "JSON/SaveFile.json";

	mySaveFile["Bonfires"].GetArray()[anIndex]["Bonfire"]["IsActive"].SetBool(aState);

	std::ofstream ofs{ dataPath };
	rapidjson::OStreamWrapper osw{ ofs };
	rapidjson::Writer<rapidjson::OStreamWrapper> writer{ osw };
	mySaveFile.Accept(writer);
}
const bool DataManager::GetBonfireState(const unsigned int anIndex) const
{
	return mySaveFile["Bonfires"].GetArray()[anIndex]["Bonfire"]["IsActive"].GetBool();
}
void DataManager::ResetBonfires()
{
	for (size_t i = 0; i < mySaveFile["Bonfires"].GetArray().Size(); i++)
	{
		mySaveFile["Bonfires"].GetArray()[i]["Bonfire"]["IsActive"].SetBool(false);
	}
}
