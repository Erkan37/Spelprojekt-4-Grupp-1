#include "stdafx.h"
#include "EffectSprite.h"
#include "SpriteComponent.h"


EffectSprite::EffectSprite()
{
}

EffectSprite::~EffectSprite()
{
}

void EffectSprite::Update(const float& aDeltatime)
{
	myTotalTimer += aDeltatime;

	v2f size = mySprite->GetSize() * myScale;
	v2f movement = myPosition * mySpeedInterval;

	mySprite->SetSize(size);
	mySprite->SetRelativePosition(movement);


	if (myTotalTimer > myLifeTime)
	{
		myIsAlive = false;
	}
}

void EffectSprite::AddSprite(SpriteComponent* aSprite)
{
	mySprite = aSprite;
	mySprite->SetSpritePath(myPathString);
}

bool EffectSprite::IsAlive()
{
	return myIsAlive;
}
