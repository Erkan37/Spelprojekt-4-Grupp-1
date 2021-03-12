#include "stdafx.h"
#include "DataManager.h"
#include <fstream>
#include <sstream>
#include <cassert>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>

DataManager::DataManager()
{
	//Assign MasterDoc
	ReadFileIntoDocument("Master.json", myMasterDoc);

	//Assign PlayerDoc
	std::string playerDataPath = myMasterDoc["PlayerData"].GetString();
	rapidjson::Document myPlayerDoc;
	ReadFileIntoDocument(playerDataPath, myPlayerDoc);
	//Assign Player Values
	myPlayerData.myAcceleration = myPlayerDoc["Acceleration"].GetFloat();
	myPlayerData.myMaxSpeed = myPlayerDoc["MaxSpeed"].GetFloat();
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

		// Lägg till alla varibler som ska uppdateras här:
		tempDoc["MaxSpeed"].SetFloat(myPlayerData.myMaxSpeed);
	}
	break;
	case DataEnum::enemy:
	{
		tempDataPath = myMasterDoc["EnemyData"].GetString();
		ReadFileIntoDocument(tempDataPath, tempDoc);

		// Lägg till alla varibler som ska uppdateras här:

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

void DataManager::ReadFileIntoDocument(std::string aFilePath, rapidjson::Document& anOutDoc)
{
	std::ifstream dataFile(aFilePath);
	std::ostringstream outStringStream;
	outStringStream << dataFile.rdbuf();
	std::string outString = outStringStream.str();
	anOutDoc.Parse(outString.c_str());
	dataFile.close();
}

// Constructors är bara här för att undvika varningar. Initializera gärna variablerna här.
PlayerData::PlayerData()
{
	myMaxSpeed = 0.0f;
	myAcceleration = 0.0f;
}
EnemyData::EnemyData()
{
	myMoveSpeed = 0.0f;
}
