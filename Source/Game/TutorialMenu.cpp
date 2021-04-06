#include "stdafx.h"
#include "TutorialMenu.h"
#include "../External/Headers/CU/Utilities.h"
#include "InputWrapper.h"

#include "GameWorld.h"

#include "SpriteComponent.h"
#include "AnimationComponent.hpp"

TutorialMenu::TutorialMenu(Scene* aScene)
	:
	GameObject(aScene)
{
	SpriteComponent* background = AddComponent<SpriteComponent>();
	SpriteComponent* tutorial = AddComponent<SpriteComponent>();
	SpriteComponent* tutorialFlame = AddComponent<SpriteComponent>();

	background->SetSpritePath("Sprites/UI/tutorialMenu/UI_tutorialMenu_Background.dds");
	tutorial->SetSpritePath("Sprites/UI/tutorialMenu/UI_tutorialMenu_Controller_252x133px.dds");
	tutorialFlame->SetSpritePath("Sprites/UI/tutorialMenu/UI_tutorialMenu_Flame_16x16px.dds");

	SetPivot(v2f(0.0f, 0.0f));

	tutorialFlame->SetSize(v2f(16.0f, 16.0f));

	Animation flameAnimation = Animation(false, false, false, 0, 7, 7, 0.125f, tutorialFlame, 16, 16);

	AnimationComponent* animation = AddComponent<AnimationComponent>();
	animation->SetSprite(tutorialFlame);
	animation->SetAnimation(&flameAnimation);

	background->SetRelativePosition(v2f(0.0f, 0.0f));
	tutorial->SetRelativePosition(v2f(24.0f, 24.0f));
	tutorialFlame->SetRelativePosition(v2f(202.0f, 142.0f));
}

TutorialMenu::~TutorialMenu()
{

}