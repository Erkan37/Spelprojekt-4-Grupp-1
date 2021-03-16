#include "stdafx.h"
#include "UIButton.h"
#include "GameObject.h"
#include "SpriteComponent.h"


UIButton::UIButton()
{
}

UIButton::~UIButton()
{
}

void UIButton::Init(Scene* aLevelScene)
{
	GameObject button = GameObject(aLevelScene);
	SpriteComponent* sprite = button.AddComponent<SpriteComponent>();
	sprite->SetSpritePath("Sprites/UI/UI_PauseMenu_Text_Continue_Unmarked_64x16px.dds");


}
