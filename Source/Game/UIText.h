#pragma once
#include "GameObject.h"
#include "EFontsSizes.hpp"

class TextComponent;
class Scene;

class UIText : public GameObject
{
public:



	UIText(Scene* aLevelScene);

	void Init(const std::string aTextString, const char* aPathAndName = "Text/Peepo.ttf", EFontSize aFontSize = EFontSize::EFontSize_36, unsigned char aBorderSize = 0);

	void SetPosition(const v2f aPosition);


private:
	TextComponent* myText;

	
};

