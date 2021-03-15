#include "stdafx.h"
#include "EffectSprite.h"
#include "SpriteComponent.h"
#include "Random.hpp"


EffectSprite::EffectSprite()
{
}

EffectSprite::~EffectSprite()
{
	mySprite->Deactivate();
}

void EffectSprite::Update(const float& aDeltatime)
{
	myTotalTimer += aDeltatime;

	//v2f movement = {mySprite->GetRelativePosition().x, mySprite->GetRelativePosition().y + -1.f};

	//mySprite->SetRelativePosition(movement);
	mySprite->SetRelativePosition({ mySprite->GetRelativePositionX(), mySprite->GetRelativePositionY() - 1.f * mySpeedInterval});
	
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
	float width = mySprite->GetSize().x * myEmitterWidth;
	
	mySprite->SetSize(size);
	mySprite->SetRelativePosition({ mySprite->GetRelativePosition().x - Utils::RandomFloat(-width, width) , mySprite->GetRelativePosition().y});
}

bool EffectSprite::IsAlive()
{
	return myIsAlive;
}
