#include "stdafx.h"
#include "DataManager.h"
#include <fstream>
#include <sstream>
#include <cassert>

#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <iostream>

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
	switch (aDataEnum)
	{
	case DataEnum::player:
	{
		std::string playerDataPath = myMasterDoc["PlayerData"].GetString();
		rapidjson::Document myPlayerDoc;
		ReadFileIntoDocument(playerDataPath, myPlayerDoc);

		rapidjson::StringBuffer buffer{};
		rapidjson::Writer<rapidjson::StringBuffer> writer{ buffer };
		myPlayerDoc.Accept(writer);

		myPlayerDoc["MaxSpeed"].SetFloat(myPlayerData.myMaxSpeed);

		std::ofstream ofs{ playerDataPath };
		if (!ofs.is_open())
		{
			std::cout << "Could not open file for writing!\n";
		}

		rapidjson::OStreamWrapper osw{ ofs };
		rapidjson::Writer<rapidjson::OStreamWrapper> writer2{ osw };
		myPlayerDoc.Accept(writer2);


		//rapidjson::Value v = rapidjson::Value(myPlayerDoc.GetObjectW());
		//v["MaxSpeed"].SetFloat(myPlayerData.myMaxSpeed);
		//std::ofstream o(playerDataPath);

		//rapidjson::Writer writer = rapidjson::Writer(myPlayerDoc);
		//writer.

		//myPlayerDoc["Acceleration"].SetFloat(myPlayerData.myAcceleration);
		//myPlayerDoc["MaxSpeed"].SetFloat(myPlayerData.myMaxSpeed);
	}
	break;


	default:
		break;
	}
}
PlayerData& DataManager::GetDataStruct(const DataEnum aDataEnum)
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
