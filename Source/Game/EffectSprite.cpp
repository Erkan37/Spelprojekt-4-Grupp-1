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
	mySprite = nullptr;
}

void EffectSprite::Update(const float& aDeltatime)
{
	myTotalTimer += aDeltatime;
	v2f position = { myPosition.x + 1.f * mySpawnAngle, mySprite->GetRelativePositionY() - 1.f * mySpeedInterval };

	mySprite->SetRelativePosition(position);
	mySprite->SetRelativeRotation(mySprite->GetRelativeRotation() + 1.f * myRotation);
	
	if (myTotalTimer > myLifeTime)
	{
		myIsAlive = false;
	}


}

void EffectSprite::AddSprite(SpriteComponent* aSprite)
{
	mySprite = aSprite;
	mySprite->SetSpritePath(myPathString);
	
	v2f size = mySprite->GetSize() * myMinScale;

	float width = mySprite->GetSize().x * myEmitterWidth;
	myPosition.x = Utils::RandomFloat(-width, width);

	mySprite->SetSize(size);
	mySprite->SetRelativePosition({ mySprite->GetRelativePosition().x + myPosition.x , mySprite->GetRelativePosition().y});
	mySprite->SetRelativeRotation(myRotation);
}

bool EffectSprite::IsAlive()
{
	return myIsAlive;
}
