#include "stdafx.h"
#include "PauseScene.h"
#include "InputWrapper.h"
#include "GameWorld.h"
#include "SpriteComponent.h"
#include "imgui.h"
#include "tga2d\text\text.h"
#include "ButtonManager.h"


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


	myPauseTitle = new GameObject(this);

	myPauseTitle->SetPositionX(myTitlePositionX);
	myPauseTitle->SetPositionY(myTitlePositionY);
	SpriteComponent* spriteTitle = myPauseTitle->AddComponent<SpriteComponent>();
	spriteTitle->SetSpritePath("Sprites/tempUI/tempPauseMenu.dds");
	spriteTitle->SetSize({ 350.0f, 100.0f });


	//Buttons
	myButtonManager = new ButtonManager(this);
	GameObject* continueButton = new GameObject(this);
	GameObject* mainMenuButton = new GameObject(this);
	GameObject* levelSelectButton = new GameObject(this);

	SpriteComponent* spriteContinue = continueButton->AddComponent<SpriteComponent>();
	spriteContinue->SetSpritePath("Sprites/tempUI/UI_PauseMenu_Text_Continue_Unmarked_64x16px.dds");

	SpriteComponent* spriteMainMenu = mainMenuButton->AddComponent<SpriteComponent>();
	spriteMainMenu->SetSpritePath("Sprites/tempUI/UI_PauseMenu_Text_MainMenu_Unmarked_64x16px.dds");

	SpriteComponent* spriteLevelSelect = levelSelectButton->AddComponent<SpriteComponent>();
	spriteLevelSelect->SetSpritePath("Sprites/tempUI/UI_PauseMenu_Text_LevelSelect_Unmarked_72x16px.dds");

	myButtonManager->AddButton(continueButton);
	myButtonManager->AddButton(mainMenuButton);
	myButtonManager->AddButton(levelSelectButton);
	myButtonManager->SetZIndex(-1500);
	myButtonManager->SetColumns(1);
	myButtonManager->SetDistance(70.0f, 100.0f, 500.0f, 0.0f);

	myButtonManager->Init();


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

//void PauseScene::ImguiUpdate()
//{
//	ImGui::Begin("PauseScene", &myIsActive, ImGuiWindowFlags_AlwaysAutoResize);
//
//	ImGui::SliderFloat("Title Pos X:", &myTitlePositionX, 0.0f, 200.0f);
//	ImGui::SliderFloat("Title Pos X", &myTitlePositionY, 0.0f, 200.0f);
//
//
//	ImGui::End();
//}
