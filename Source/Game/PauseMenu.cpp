#include "stdafx.h"
#include "PauseMenu.h"
#include "SpriteComponent.h"
#include "UIButton.h"
#include "GameWorld.h"
#include "InputWrapper.h"
#include "Scene.h"
#include "Camera.h"

PauseMenu::PauseMenu(Scene* aLevelScene)
	:
	GameObject(aLevelScene),
	myCamera(aLevelScene->GetCamera())
{
	myScene = aLevelScene;
}

void PauseMenu::Init()
{
	myInput = CGameWorld::GetInstance()->Input();

	int renderSizeX = Tga2D::CEngine::GetInstance()->GetRenderSize().x;
	int renderSizeY = Tga2D::CEngine::GetInstance()->GetRenderSize().y;

	v2i renderSize = { renderSizeX, renderSizeY };

	myPosition = { 50.f, 50.f };

	//SpriteComponent* sprite = AddComponent<SpriteComponent>();
	//sprite->SetSpritePath("Sprites/UI/UI_PauseMenu_Bakground.dds");
	//sprite->SetSize({ 10.f, 1.f });

	//myBackground = AddComponent<SpriteComponent>();
	//myBackground->SetSpritePath("Sprites/UI/UI_PauseMenu_Bakground.dds");
	//myBackground->SetSize({320.f, 220.f});

	myContinueBtn = std::make_unique<UIButton>(myScene);
	v2f continuePos = { 50.f, 50.f };
	myLevelSelectBtn = std::make_unique<UIButton>(myScene);
	v2f levelSelectPos = { 50.f, 100.f };
	myMainMenuBtn = std::make_unique<UIButton>(myScene);
	v2f mainMenuPos = { 50.f, 150.f };

	myContinueBtn->Init("Sprites/UI/UI_PauseMenu_Text_Continue_Unmarked_64x16px.dds", { 64.f,16.f }, continuePos);
	myLevelSelectBtn->Init("Sprites/UI/UI_PauseMenu_Text_LevelSelect_Unmarked_72x16px.dds", { 72.f,16.f }, levelSelectPos);
	myMainMenuBtn->Init("Sprites/UI/UI_PauseMenu_Text_MainMenu_Unmarked_64x16px.dds", { 64.f,16.f }, mainMenuPos);

	myButtons.clear();

	myButtons.push_back(myContinueBtn.get());
	myButtons.push_back(myLevelSelectBtn.get());
	myButtons.push_back(myMainMenuBtn.get());

	GameObject::Init();

}

void PauseMenu::Update(const float& aDeltaTime)
{
	float renderSizeX = static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x);
	float renderSizeY = static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().y);

	v2f position = myCamera.GetPosition();

	SetPosition(myCamera.GetPosition() + myPosition);

	if (myInput->GetInput()->GetKeyJustDown(Keys::RKey))
		std::cout << "R KEY PUSHED" << std::endl;
}

void PauseMenu::Render()
{
	GameObject::Render();
}
