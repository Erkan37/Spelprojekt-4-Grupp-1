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
	rapidjson::Document playerDoc;
	ReadFileIntoDocument(playerDataPath, playerDoc);
	//Assign Player Values
	AssignPlayerValues(playerDoc);
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
		tempDoc["Acceleration"].SetFloat(myPlayerData.myAcceleration);
		tempDoc["MaxSpeed"].SetFloat(myPlayerData.myMaxSpeed);
		tempDoc["Retardation"].SetFloat(myPlayerData.myRetardation);
		tempDoc["Lerp Acceleration"].SetFloat(myPlayerData.myLerpAcceleration);
		tempDoc["Platform Velocity Retardation"].SetFloat(myPlayerData.myPlatformVelocityRetardation);
		tempDoc["Coyote Time"].SetFloat(myPlayerData.myCoyoteTime);
		tempDoc["Jump Velocity"].SetFloat(myPlayerData.myJumpVelocity);
		tempDoc["Double Jump Velocity"].SetFloat(myPlayerData.myDoubleJumpVelocity);
		tempDoc["Max Fall Speed"].SetFloat(myPlayerData.myMaxFallSpeed);
		tempDoc["Ledge Jump Velocity"].SetFloat(myPlayerData.myLedgeJumpVelocity);
		tempDoc["Jump When Falling Time"].SetFloat(myPlayerData.myJumpWhenFallingTime);
		tempDoc["Trigger Falling Speed"].SetFloat(myPlayerData.myTriggerFallingSpeed);

		tempDoc["Die Vibration Strength"].SetFloat(myPlayerData.myDieVibrationStrength);
		tempDoc["Land Vibration Strength"].SetFloat(myPlayerData.myLandVibrationStrength);
		tempDoc["Springs Vibration Strength"].SetFloat(myPlayerData.mySpringsVibrationStrength);
		tempDoc["Die Vibration Length"].SetFloat(myPlayerData.myDieVibrationLength);
		tempDoc["Land Vibration Length"].SetFloat(myPlayerData.myLandVibrationLength);
		tempDoc["Springs Vibration Length"].SetFloat(myPlayerData.mySpringsVibrationLength);

		tempDoc["Die Shake Duration"].SetFloat(myPlayerData.myDieShakeDuration);
		tempDoc["Die Shake Intensity"].SetFloat(myPlayerData.myDieShakeIntensity);
		tempDoc["Die Shake DropOff"].SetFloat(myPlayerData.myDieShakeDropOff);
		tempDoc["Land Shake Duration"].SetFloat(myPlayerData.myLandShakeDuration);
		tempDoc["Land Shake Intensity"].SetFloat(myPlayerData.myLandShakeIntensity);
		tempDoc["Land Shake DropOff"].SetFloat(myPlayerData.myLandShakeDropOff);
		tempDoc["Spring Shake Duration"].SetFloat(myPlayerData.mySpringShakeDuration);
		tempDoc["Spring Shake Intensity"].SetFloat(myPlayerData.mySpringShakeIntensity);
		tempDoc["Spring Shake DropOff"].SetFloat(myPlayerData.mySpringShakeDropOff);
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
	myRetardation = 0.0f;
	myLerpAcceleration = 0.0f;
	myPlatformVelocityRetardation = 0.0f;
	myCoyoteTime = 0.0f;
	myJumpVelocity = 0.0f;
	myDoubleJumpVelocity = 0.0f;
	myMaxFallSpeed = 0.0f;
	myLedgeJumpVelocity = 0.0f;
	myJumpWhenFallingTime = 0.0f;
	myTriggerFallingSpeed = 0.0f;

	myDieVibrationStrength = 0.0f;
	myLandVibrationStrength = 0.0f;
	mySpringsVibrationStrength = 0.0f;
	myDieVibrationLength = 0.0f;
	myLandVibrationLength = 0.0f;
	mySpringsVibrationLength = 0.0f;

	myDieShakeDuration = 0.0f;
	myDieShakeIntensity = 0.0f;
	myDieShakeDropOff = 0.0f;
	myLandShakeDuration = 0.0f;
	myLandShakeIntensity = 0.0f;
	myLandShakeDropOff = 0.0f;
	mySpringShakeDuration = 0.0f;
	mySpringShakeIntensity = 0.0f;
	mySpringShakeDropOff = 0.0f;
}
EnemyData::EnemyData()
{
	myMoveSpeed = 0.0f;
}

// Assign Methods
void DataManager::AssignPlayerValues(const rapidjson::Document &aDoc)
{
	myPlayerData.myAcceleration = aDoc["Acceleration"].GetFloat();
	myPlayerData.myMaxSpeed = aDoc["MaxSpeed"].GetFloat();
	myPlayerData.myRetardation = aDoc["Retardation"].GetFloat();
	myPlayerData.myLerpAcceleration = aDoc["Lerp Acceleration"].GetFloat();
	myPlayerData.myPlatformVelocityRetardation = aDoc["Platform Velocity Retardation"].GetFloat();
	myPlayerData.myCoyoteTime = aDoc["Coyote Time"].GetFloat();
	myPlayerData.myJumpVelocity = aDoc["Jump Velocity"].GetFloat();
	myPlayerData.myDoubleJumpVelocity = aDoc["Double Jump Velocity"].GetFloat();
	myPlayerData.myMaxFallSpeed = aDoc["Max Fall Speed"].GetFloat();
	myPlayerData.myLedgeJumpVelocity = aDoc["Ledge Jump Velocity"].GetFloat();
	myPlayerData.myJumpWhenFallingTime = aDoc["Jump When Falling Time"].GetFloat();
	myPlayerData.myTriggerFallingSpeed = aDoc["Trigger Falling Speed"].GetFloat();

	myPlayerData.myDieVibrationStrength = aDoc["Die Vibration Strength"].GetFloat();
	myPlayerData.myLandVibrationStrength = aDoc["Land Vibration Strength"].GetFloat();
	myPlayerData.mySpringsVibrationStrength = aDoc["Springs Vibration Strength"].GetFloat();
	myPlayerData.myDieVibrationLength = aDoc["Die Vibration Length"].GetFloat();
	myPlayerData.myLandVibrationLength = aDoc["Land Vibration Length"].GetFloat();
	myPlayerData.mySpringsVibrationLength = aDoc["Springs Vibration Length"].GetFloat();

	myPlayerData.myDieShakeDuration = aDoc["Die Shake Duration"].GetFloat();
	myPlayerData.myDieShakeIntensity = aDoc["Die Shake Intensity"].GetFloat();
	myPlayerData.myDieShakeDropOff = aDoc["Die Shake DropOff"].GetFloat();
	myPlayerData.myLandShakeDuration = aDoc["Land Shake Duration"].GetFloat();
	myPlayerData.myLandShakeIntensity = aDoc["Land Shake Intensity"].GetFloat();
	myPlayerData.myLandShakeDropOff = aDoc["Land Shake DropOff"].GetFloat();
	myPlayerData.mySpringShakeDuration = aDoc["Spring Shake Duration"].GetFloat();
	myPlayerData.mySpringShakeIntensity = aDoc["Spring Shake Intensity"].GetFloat();
	myPlayerData.mySpringShakeDropOff = aDoc["Spring Shake DropOff"].GetFloat();
}
