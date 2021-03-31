#include "stdafx.h"
#include "Background.h"
#include "SpriteComponent.h"
#include "Camera.h"
#include "LevelScene.h"
#include "Player.hpp"
#include "AudioManager.h"
#include "rapidjson/istreamwrapper.h"

#include "Game.h"


Background::Background(Scene* aLevelScene) 
	:
	GameObject(aLevelScene)
{
	SetZIndex(0);

	myOriginalSpeed = {};
	myBackgroundSpeedOneX = {};
	myBackgroundSpeedTwoX = {};
	myBackgroundSpeedThreeX = {};
	myBackgroundSpeedOneY = {};
	myBackgroundSpeedTwoY = {};
	myBackgroundSpeedThreeY = {};
	myAddedCameraPos = {};
	myCloudSpeed = {};
	myCloudDistance = {};

	assert(&aLevelScene->GetCamera() != NULL);
	myCamera = &aLevelScene->GetCamera();
	LoadJson(aLevelScene);
		
}

void Background::Init(int /*someLevelIndex*/)
{
}

void Background::Update(const float& aDeltaTime)
{
	UpdateBackground(aDeltaTime);
}

void Background::UpdateBackground(const float& aDeltaTime)
{
	if (myCamera->GetActive() && myAddedCameraPos == false)
	{
		myStartingCameraPos = { 0.f, myCamera->GetPosition().y };
		myAddedCameraPos = true;
	}

	MoveBackground(aDeltaTime);
}

void Background::ResizeBackground()
{
	myCurrentRenderSize.x = myBackgroundSprite1->GetSizeX();
	myCurrentRenderSize.y = Config::ourReferenceSize.y;

	myBackground->SetPosition({ myCurrentRenderSize.x / 2.f, myCurrentRenderSize.y / 2.f });
}

void Background::MoveBackground(const float& aDeltaTime)
{
	v2f backgroundSpeedOne;
	backgroundSpeedOne = { (myStartingCameraPos.x - myCamera->GetPosition().x) * myBackgroundSpeedOneX,
						   (myStartingCameraPos.y - myCamera->GetPosition().y) * myBackgroundSpeedOneY };

	v2f backgroundSpeedThree;
	backgroundSpeedThree = { (myStartingCameraPos.x - myCamera->GetPosition().x) * myBackgroundSpeedThreeX,
						   (myStartingCameraPos.y - myCamera->GetPosition().y) * myBackgroundSpeedThreeY };

	v2f backgroundSpeedFour;
	backgroundSpeedFour = { (myStartingCameraPos.x - myCamera->GetPosition().x) * myBackgroundSpeedFourX,
						   (myStartingCameraPos.y - myCamera->GetPosition().y) * myBackgroundSpeedFourY };

	v2f backgroundSpeedFive;
	backgroundSpeedFive = { (myStartingCameraPos.x - myCamera->GetPosition().x) * myBackgroundSpeedFiveX,
						   (myStartingCameraPos.y - myCamera->GetPosition().y) * myBackgroundSpeedFiveY };

	v2f backgroundSpeedSix;
	backgroundSpeedSix = { (myStartingCameraPos.x - myCamera->GetPosition().x) * myBackgroundSpeedSixX,
						  (myStartingCameraPos.y - myCamera->GetPosition().y) * myBackgroundSpeedSixY };


	myBackgroundSprite1->SetRelativePosition(myCamera->GetPosition() + backgroundSpeedOne + myOffsetBackground1);
	myBackgroundSprite3->SetRelativePosition(myCamera->GetPosition() + backgroundSpeedThree + myOffsetBackground3);
	myBackgroundSprite4->SetRelativePosition(myCamera->GetPosition() + backgroundSpeedFour + myOffsetBackground4);
	myBackgroundSprite5->SetRelativePosition(myCamera->GetPosition() + backgroundSpeedFive + myOffsetBackground5);
	myBackgroundSprite6->SetRelativePosition(myCamera->GetPosition() + backgroundSpeedSix + myOffsetBackground6);

	myCloudDistance = myCloudDistance + (aDeltaTime * myCloudSpeed);

	v2f backgroundSpeedTwo;
	backgroundSpeedTwo = { (myStartingCameraPos.x - myCamera->GetPosition().x) * myBackgroundSpeedTwoX,
						   (myStartingCameraPos.y - myCamera->GetPosition().y) * myBackgroundSpeedTwoX };

	backgroundSpeedTwo.x = backgroundSpeedTwo.x + myCloudDistance;

	myBackgroundSprite2->SetRelativePosition(myCamera->GetPosition() + backgroundSpeedTwo + myOffsetBackground2);
}

void Background::LoadJson(Scene* aLevelScene)
{
	myOriginalSpeed = 0.2f;

	std::ifstream backgroundObjectFile("JSON/Background.json");
	rapidjson::IStreamWrapper backgroundObjectStream(backgroundObjectFile);

	rapidjson::Document backgroundDocuments;
	backgroundDocuments.ParseStream(backgroundObjectStream);


	std::ifstream backgroundPathObjectsFile(backgroundDocuments["BackgroundArray"][1]["FilePath"].GetString());
	rapidjson::IStreamWrapper backgroundPathObjectStream(backgroundPathObjectsFile);

	rapidjson::Document backgroundPathDocuments;
	backgroundPathDocuments.ParseStream(backgroundPathObjectStream);

	LoadBackgrounds(aLevelScene, backgroundPathDocuments);
	
	myBackgroundSpeedOneX = backgroundDocuments["SpeedVariables"][0]["SpeedOneX"].GetFloat();
	myBackgroundSpeedOneY = backgroundDocuments["SpeedVariables"][0]["SpeedOneY"].GetFloat();

	myBackgroundSpeedTwoX = backgroundDocuments["SpeedVariables"][1]["SpeedTwoX"].GetFloat();
	myBackgroundSpeedTwoY = backgroundDocuments["SpeedVariables"][1]["SpeedTwoY"].GetFloat();

	myBackgroundSpeedThreeX = backgroundDocuments["SpeedVariables"][2]["SpeedThreeX"].GetFloat();
	myBackgroundSpeedThreeY = backgroundDocuments["SpeedVariables"][2]["SpeedThreeY"].GetFloat();

	myBackgroundSpeedFourX = backgroundDocuments["SpeedVariables"][3]["SpeedFourX"].GetFloat();
	myBackgroundSpeedFourY = backgroundDocuments["SpeedVariables"][3]["SpeedFourY"].GetFloat();

	myBackgroundSpeedFiveX = backgroundDocuments["SpeedVariables"][4]["SpeedFiveX"].GetFloat();
	myBackgroundSpeedFiveY = backgroundDocuments["SpeedVariables"][4]["SpeedFiveY"].GetFloat();

	myBackgroundSpeedSixX = backgroundDocuments["SpeedVariables"][5]["SpeedSixX"].GetFloat();
	myBackgroundSpeedSixY = backgroundDocuments["SpeedVariables"][5]["SpeedSixY"].GetFloat();

	myCloudSpeed = backgroundDocuments["Cloud"][0]["SpeedX"].GetFloat();

	backgroundPathObjectsFile.close();
	backgroundObjectFile.close();
}

void Background::LoadBackgrounds(Scene* aLevelScene, rapidjson::Document& someDocuments)
{
	myBackground = std::make_unique<GameObject>(aLevelScene);

	int backgroundSizeArray = someDocuments["BackgroundPaths"].Size();

	for (int i = 0; i < backgroundSizeArray; i++)
	{
		v2f offset = { someDocuments["OffSets"][i]["PositionX"].GetFloat() , someDocuments["OffSets"][i]["PositionY"].GetFloat() };
		CreateBackgrounds(aLevelScene, someDocuments["BackgroundPaths"][i]["FilePath"].GetString(), i, offset);
	}

	myBackground->Init();
	ResizeBackground();
}

void Background::CreateBackgrounds(Scene* aLevelScene, const std::string aPath, const int aIndex, const v2f anOffset)
{
	switch (aIndex)
	{
	case 0:
		myBackgroundSprite1 = myBackground->AddComponent<SpriteComponent>();
		myBackgroundSprite1->SetSpritePath(aPath);
		myBackgroundSprite1->SetZIndex(1);
		myOffsetBackground1 = anOffset;
		break;
	case 1:
		myBackgroundSprite2 = myBackground->AddComponent<SpriteComponent>();
		myBackgroundSprite2->SetSpritePath(aPath);
		myBackgroundSprite2->SetZIndex(2);
		myOffsetBackground2 = anOffset;
		break;
	case 2:
		myBackgroundSprite3 = myBackground->AddComponent<SpriteComponent>();
		myBackgroundSprite3->SetSpritePath(aPath);
		myBackgroundSprite3->SetZIndex(3);
		myOffsetBackground3 = anOffset;
		break;
	case 3:
		myBackgroundSprite4 = myBackground->AddComponent<SpriteComponent>();
		myBackgroundSprite4->SetSpritePath(aPath);
		myBackgroundSprite4->SetZIndex(4);
		myOffsetBackground4 = anOffset;
		break;
	case 4:
		myBackgroundSprite5 = myBackground->AddComponent<SpriteComponent>();
		myBackgroundSprite5->SetSpritePath(aPath);
		myBackgroundSprite5->SetZIndex(5);
		myOffsetBackground5 = anOffset;
		break;
	case 5:
		myBackgroundSprite6 = myBackground->AddComponent<SpriteComponent>();
		myBackgroundSprite6->SetSpritePath(aPath);
		myBackgroundSprite6->SetZIndex(6);
		myOffsetBackground6 = anOffset;
		break;
	default:
		break;
	}
	
}

void Background::SetSpeedVariables(const std::string aPath)
{
}
