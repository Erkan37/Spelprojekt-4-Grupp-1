#pragma once
#include "GameObject.h"
#include "EFontsSizes.hpp"

class Scene;

class UIText : public GameObject
{
public:



	UIText(Scene* aLevelScene);

	void Init(const char* aPathAndName = "Text/Peepo.ttf", EFontSize aFontSize = EFontSize::EFontSize_36, unsigned char aBorderSize = 0);



private:


	
};

