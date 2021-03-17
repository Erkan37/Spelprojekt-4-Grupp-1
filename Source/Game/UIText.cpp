#include "stdafx.h"
#include "UIText.h"
#include "TextComponent.h"

UIText::UIText(Scene* aLevelScene)
	:
	GameObject(aLevelScene)
{
}

void UIText::Init(const char* aPathAndName, EFontSize aFontSize, unsigned char aBorderSize)
{
	TextComponent* text = AddComponent<TextComponent>();
	text->CreateText(aPathAndName, static_cast<EFontSize>(aFontSize), aBorderSize);
	text->SetText("YOYOoyoyooyYOOY");
	text->SetRelativePosition( 300.f, 50.f );
	text->Activate();
}

