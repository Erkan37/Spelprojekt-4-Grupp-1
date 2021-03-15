#include "stdafx.h"
#include "EffectSprite.h"
#include "SpriteComponent.h"
#include "Random.hpp"


EffectSprite::EffectSprite()
{
}

EffectSprite::~EffectSprite()
{
}

void EffectSprite::Update(const float& aDeltatime)
{
	myTotalTimer += aDeltatime;

	v2f size = mySprite->GetSize() * 0.5f;
	//v2f movement = {mySprite->GetRelativePosition().x, mySprite->GetRelativePosition().y + -1.f};

	//mySprite->SetRelativePosition(movement);


	if (myTotalTimer > myLifeTime)
	{
		myIsAlive = false;
	}
}

void EffectSprite::AddSprite(SpriteComponent* aSprite)
{
	mySprite = aSprite;
	mySprite->SetSpritePath(myPathString);
	v2f size = mySprite->GetSize() * myScale;
	mySprite->SetSize(size);
	mySprite->SetRelativePosition({ mySprite->GetRelativePosition().x + 5 * myEmitterWidth , mySprite->GetRelativePosition().y});
}

bool EffectSprite::IsAlive()
{
	return myIsAlive;
}
