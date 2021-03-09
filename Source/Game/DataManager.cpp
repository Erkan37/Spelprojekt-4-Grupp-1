#include "stdafx.h"
#include "DataManager.h"
#include <fstream>
#include <sstream>
#include <cassert>

void DataManager::InitData()
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
	switch (aDataEnum)
	{
	case DataEnum::player:
	{
		std::string playerDataPath = myMasterDoc["PlayerData"].GetString();
		rapidjson::Document myPlayerDoc;
		ReadFileIntoDocument(playerDataPath, myPlayerDoc);

		myPlayerDoc["Acceleration"].Set(myPlayerData.myAcceleration);
	}
	break;


	default:
		break;
	}
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


	default:
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
