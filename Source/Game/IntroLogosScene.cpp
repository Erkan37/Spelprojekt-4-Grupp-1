#include "stdafx.h"
#include "IntroLogosScene.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "Game.h"

enum class eIntroLogo
{
	Tga2D_logo, //Temporär som test

	enum_intro_logo_size
};

IntroLogosScene::IntroLogosScene()
{
	mySpriteComponent = nullptr;
	myLogo = nullptr;
	myTimeSinceInited = 0.0f;
	myTotalLogoTime = 3.0f;
}
IntroLogosScene::~IntroLogosScene()
{

}

void IntroLogosScene::Update(const float &aDeltaTime)
{
	if (myTimeSinceInited > myTotalLogoTime)
	{
		CGameWorld::GetInstance()->GetLevelManager().SingleLoadScene(LevelManager::eScenes::MainMenu);
	}
	if (myTimeSinceInited < (myTotalLogoTime / static_cast<float>(eIntroLogo::enum_intro_logo_size)))
	{
		DisplayLogo(eIntroLogo::Tga2D_logo);
	}

	Scene::Update(aDeltaTime);
}

void IntroLogosScene::DisplayLogo(const eIntroLogo anEnum)
{
	switch (anEnum)
	{
	case eIntroLogo::Tga2D_logo:
	{
		if (!(mySpriteComponent->GetSpritePath() == "Sprites/tga_logo.dds"))
		{
			mySpriteComponent->SetSpritePath("Sprites/tga_logo.dds");
		}
	}
	break;

	default:
	{
		assert(false && "Invalid Enum passed to IntroLogosScene::DisplayLogo().");
	}
	break;
	}
}

void IntroLogosScene::Load()
{
	myLogo = new GameObject(this);
	mySpriteComponent = myLogo->AddComponent<SpriteComponent>();
	
	

	myLogo->SetPivot({ 0.5f, 0.5f });
	myLogo->SetPosition({ static_cast<float>(Config::width) / 2.0f, static_cast<float>(Config::height) / 2.0f });

	Scene::Load();
}
