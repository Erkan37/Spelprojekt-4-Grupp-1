#include "stdafx.h"
#include "IntroLogosScene.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "Game.h"

enum class eIntroLogo
{
	Tga2D_logo, // Temporär som test
	de_e_nice, // Temporär som test

	enum_intro_logo_size
};

IntroLogosScene::IntroLogosScene()
{
	for (size_t i = 0; i < static_cast<size_t>(eIntroLogo::enum_intro_logo_size); i++)
	{
		mySpriteVector.push_back(nullptr);
	}
	myLogo = nullptr;
	myTimeSinceInited = 0.0f;
	myTotalLogoTime = 2.0f;
}
IntroLogosScene::~IntroLogosScene()
{

}

void IntroLogosScene::Update(const float &aDeltaTime)
{
	myLogo->SetPosition({ static_cast<float>(Config::windowWidth) / 2.0f, static_cast<float>(Config::windowHeight) / 2.0f });
	myTimeSinceInited += aDeltaTime;

	if (myTimeSinceInited > myTotalLogoTime)
	{
		CGameWorld::GetInstance()->GetLevelManager().SingleLoadScene(LevelManager::eScenes::MainMenu);
	}
	else if (myTimeSinceInited <= myTotalLogoTime)
	{
		DisplayLogo(myTimeSinceInited);
	}

	Scene::Update(aDeltaTime);
}

void IntroLogosScene::DisplayLogo(const float aTime)
{
	unsigned int timeInt = static_cast<int>(aTime);

	switch (timeInt)
	{
	case 0:
	{
		if (!(mySpriteVector[timeInt]->IsActive()))
		{
			mySpriteVector[timeInt]->Activate();
		}
	}
	break;
	case 1:
	{
		if (!(mySpriteVector[timeInt]->IsActive()))
		{
			mySpriteVector[timeInt - 1]->Deactivate();
			mySpriteVector[timeInt]->Activate();
		}
	}
	break;
	default:
	break;
	}
}

void IntroLogosScene::Load()
{
	myLogo = new GameObject(this);
	myLogo->SetPivot({ 0.5f, 0.5f });
	myLogo->SetPosition({ static_cast<float>(Config::windowWidth) / 2.0f, static_cast<float>(Config::windowHeight) / 2.0f });

	mySpriteVector[static_cast<size_t>(eIntroLogo::Tga2D_logo)] = myLogo->AddComponent<SpriteComponent>();
	mySpriteVector[static_cast<size_t>(eIntroLogo::Tga2D_logo)]->SetSpritePath("Sprites/tga_logo.dds");
	mySpriteVector[static_cast<size_t>(eIntroLogo::Tga2D_logo)]->Deactivate();

	mySpriteVector[static_cast<size_t>(eIntroLogo::de_e_nice)] = myLogo->AddComponent<SpriteComponent>();
	mySpriteVector[static_cast<size_t>(eIntroLogo::de_e_nice)]->SetSpritePath("Sprites/w.png");
	mySpriteVector[static_cast<size_t>(eIntroLogo::de_e_nice)]->Deactivate();

	Scene::Load();
}
