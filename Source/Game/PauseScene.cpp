#include "stdafx.h"
#include "PauseScene.h"
#include "InputWrapper.h"
#include "GameWorld.h"
#include "SpriteComponent.h"
#include "imgui.h"
#include "tga2d\text\text.h"
#include "ButtonManager.h"
#include "Game.h"


PauseScene::PauseScene()
	: myUIManager(nullptr)
	, myInputHandler(nullptr)
	, myPauseTitle(nullptr)
	, myTitlePositionX(1000.0f)
	, myTitlePositionY(300.0f)
	, myBackGround(nullptr)
	, myButtonManager(nullptr)
{}

PauseScene::~PauseScene()
{
	Unload();
}

void PauseScene::Load()
{
	CGameWorld* world = CGameWorld::GetInstance();
	myInputHandler = world->Input();

	myBackGround = new GameObject(this);
	myPauseTitle = new GameObject(this);

	myBackGround->SetPosition({ static_cast<float>(Config::width) / 5.5f, static_cast<float>(Config::height) / 5.5f });
	SpriteComponent* spriteBackground = myBackGround->AddComponent<SpriteComponent>();
	spriteBackground->SetSpritePath("Sprites/tempUI/UI_PauseMenu_Bakground.dds");

	myPauseTitle->SetPositionX(myTitlePositionX);
	myPauseTitle->SetPositionY(myTitlePositionY);
	SpriteComponent* spriteTitle = myPauseTitle->AddComponent<SpriteComponent>();
	spriteTitle->SetSpritePath("Sprites/tempUI/tempPauseMenu.dds");
	//spriteTitle->SetSize({ 350.0f, 100.0f });


	//Buttons
	myButtonManager = new ButtonManager(this);
	GameObject* continueButton = new GameObject(this);
	GameObject* levelSelectButton = new GameObject(this);
	GameObject* mainMenuButton = new GameObject(this);

	SpriteComponent* spriteContinue = continueButton->AddComponent<SpriteComponent>();
	spriteContinue->SetSpritePath("Sprites/tempUI/UI_PauseMenu_Text_Continue_Unmarked_64x16px.dds");
	
	SpriteComponent* spriteLevelSelect = levelSelectButton->AddComponent<SpriteComponent>();
	spriteLevelSelect->SetSpritePath("Sprites/tempUI/UI_PauseMenu_Text_LevelSelect_Unmarked_72x16px.dds");

	SpriteComponent* spriteMainMenu = mainMenuButton->AddComponent<SpriteComponent>();
	spriteMainMenu->SetSpritePath("Sprites/tempUI/UI_PauseMenu_Text_MainMenu_Unmarked_64x16px.dds");


	myButtonManager->AddButton(continueButton);
	myButtonManager->AddButton(levelSelectButton);
	myButtonManager->AddButton(mainMenuButton);
	myButtonManager->SetZIndex(-1500);
	myButtonManager->SetColumns(1);
	myButtonManager->SetDistance(550.0f, 20.0f, -850.0f, 0.0f);

	myButtonManager->Init();
	myBackGround->Init();

	Scene::Load();

	//Load in data from DataManager?
}


void PauseScene::Unload()
{

	myButtonManager->Destroy();

	myInputHandler = nullptr;
	myButtonManager = nullptr;


	Scene::Unload();
}

void PauseScene::Activate()
{
	if (IsActive()) return;
	if (!IsLoaded()) Load();
	myButtonManager->Activate();
	myBackGround->Activate();

	GetCamera().SetBounds(v2f(-840.0f, -540.0f), v2f(3840.0f, 2160.0f));
	GetCamera().SetZoom(4.0f);


	Scene::Activate();
}

void PauseScene::Deactivate()
{
	if (!IsActive()) return;

	myButtonManager->Deactivate();

	Scene::Deactivate();
}

void PauseScene::Update(const float& aDeltaTime, const float& aTotalTime)
{
	if (!IsActive()) return;

	if (myInputHandler->IsMovingDown())
	{
		myButtonManager->NextRow(1);
	}
	if (myInputHandler->IsMovingUp())
	{
		myButtonManager->NextRow(-1);
	}

	Scene::Update(aDeltaTime);
}

void PauseScene::SelectButton()
{
	if (myButtonManager->GetIndex() <= 0)
	{
		return;
	}
	if (myButtonManager->GetIndex() == 1)
	{
		return;
	}
	if (myButtonManager->GetIndex() >= 2)
	{
		return;
	}

}
