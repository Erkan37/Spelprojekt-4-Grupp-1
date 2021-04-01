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

const void Background::UpdateBackground(const float& aDeltaTime)
{
	if (myCamera->GetActive() && myAddedCameraPos == false)
	{
		myStartingCameraPos = { 0.f, myCamera->GetPosition().y };
		myAddedCameraPos = true;
	}

	MoveBackground(aDeltaTime);
}

const void Background::ResizeBackground()
{
	myCurrentRenderSize.x = myBackgroundSprite1->GetComponent<SpriteComponent>()->GetSize().x;
	myCurrentRenderSize.y = Config::ourReferenceSize.y;

}

const void Background::MoveBackground(const float& aDeltaTime)
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


	myBackgroundSprite1->SetPosition(myCamera->GetPosition() + backgroundSpeedOne + GetHalfImageSize(myBackgroundSprite1) + myOffsetBackground1);
	myBackgroundSprite3->SetPosition(myCamera->GetPosition() + backgroundSpeedThree + GetHalfImageSize(myBackgroundSprite3) + myOffsetBackground3);
	myBackgroundSprite4->SetPosition(myCamera->GetPosition() + backgroundSpeedFour + GetHalfImageSize(myBackgroundSprite4) + myOffsetBackground4);
	myBackgroundSprite5->SetPosition(myCamera->GetPosition() + backgroundSpeedFive + GetHalfImageSize(myBackgroundSprite5) + myOffsetBackground5);
	myBackgroundSprite6->SetPosition(myCamera->GetPosition() + backgroundSpeedSix + GetHalfImageSize(myBackgroundSprite6) + myOffsetBackground6);

	myCloudDistance = myCloudDistance + (aDeltaTime * myCloudSpeed);

	v2f backgroundSpeedTwo;
	backgroundSpeedTwo = { (myStartingCameraPos.x - myCamera->GetPosition().x) * myBackgroundSpeedTwoX,
						   (myStartingCameraPos.y - myCamera->GetPosition().y) * myBackgroundSpeedTwoX };

	backgroundSpeedTwo.x = backgroundSpeedTwo.x + myCloudDistance;


	myBackgroundSprite2->SetPosition(myCamera->GetPosition() + backgroundSpeedTwo + GetHalfImageSize(myBackgroundSprite2) + myOffsetBackground2);
}

const void Background::LoadJson(Scene* aLevelScene)
{
	myOriginalSpeed = 0.2f;

	std::ifstream backgroundObjectFile("JSON/Background.json");
	rapidjson::IStreamWrapper backgroundObjectStream(backgroundObjectFile);

	rapidjson::Document backgroundDocuments;
	backgroundDocuments.ParseStream(backgroundObjectStream);


	std::ifstream backgroundPathObjectsFile(backgroundDocuments["BackgroundArray"][0]["FilePath"].GetString());
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

const void Background::LoadBackgrounds(Scene* aLevelScene, rapidjson::Document& someDocuments)
{
	int backgroundSizeArray = someDocuments["BackgroundPaths"].Size();

	for (int i = 0; i < backgroundSizeArray; i++)
	{
		v2f offset = { someDocuments["OffSets"][i]["PositionX"].GetFloat() , someDocuments["OffSets"][i]["PositionY"].GetFloat() };
		CreateBackgrounds(aLevelScene, someDocuments["BackgroundPaths"][i]["FilePath"].GetString(), i, offset);
	}

	ResizeBackground();
}

const void Background::CreateBackgrounds(Scene* aLevelScene, const std::string aPath, const int aIndex, const v2f anOffset)
{
	switch (aIndex)
	{
	case 0:
	{
		myBackgroundSprite1 = new GameObject(aLevelScene);
		SpriteComponent* sprite = myBackgroundSprite1->AddComponent<SpriteComponent>();
		sprite->SetSpritePath(aPath);
		myBackgroundSprite1->SetZIndex(1);
		myOffsetBackground1 = anOffset;
		break;
	}

	case 1:
	{
		myBackgroundSprite2 = new GameObject(aLevelScene);
		SpriteComponent* sprite = myBackgroundSprite2->AddComponent<SpriteComponent>();
		sprite->SetSpritePath(aPath);
		myBackgroundSprite2->SetZIndex(2);
		myOffsetBackground2 = anOffset;
		break;
	}

	case 2:
	{
		myBackgroundSprite3 = new GameObject(aLevelScene);
		SpriteComponent* sprite = myBackgroundSprite3->AddComponent<SpriteComponent>();
   		sprite->SetSpritePath(aPath);
		myBackgroundSprite3->SetZIndex(3);
		myOffsetBackground3 = anOffset;
		break;
	}

	case 3:
	{
		myBackgroundSprite4 = new GameObject(aLevelScene);
		SpriteComponent* sprite = myBackgroundSprite4->AddComponent<SpriteComponent>();
		sprite->SetSpritePath(aPath);
		myBackgroundSprite4->SetZIndex(4);
		myOffsetBackground4 = anOffset;
		break;
	}

	case 4:
	{
		myBackgroundSprite5 = new GameObject(aLevelScene);
		SpriteComponent* sprite = myBackgroundSprite5->AddComponent<SpriteComponent>();
		sprite->SetSpritePath(aPath);
		myBackgroundSprite5->SetZIndex(5);
		myOffsetBackground5 = anOffset;
		break;
	}

	case 5:
	{
		myBackgroundSprite6 = new GameObject(aLevelScene);
		SpriteComponent* sprite = myBackgroundSprite6->AddComponent<SpriteComponent>();
		sprite->SetSpritePath(aPath);
		myBackgroundSprite6->SetZIndex(6);
		myOffsetBackground6 = anOffset;
		break;
	}

	default:
	{
		break;

	}
	}

}

const void Background::SetSpeedVariables(const std::string aPath)
{
}

const v2f Background::GetHalfImageSize(GameObject* aSprite)
{
	assert(aSprite->GetComponent<SpriteComponent>() != NULL);

	v2f spriteSize = aSprite->GetComponent<SpriteComponent>()->GetImageSize() / 2.f;

	return spriteSize;
}
