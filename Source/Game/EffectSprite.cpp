#include "stdafx.h"
#include "EffectSprite.h"
#include "SpriteComponent.h"
#include "Random.hpp"
#include "../External/Headers/CU/Utilities.h"

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

	myScale.x = Utils::Lerp(mySprite->GetSize().x, myMaxVectorScale.x, 0.002f);
	myScale.y = Utils::Lerp(mySprite->GetSize().y, myMaxVectorScale.y, 0.002f);

	v2f position = { myPosition.x, mySprite->GetRelativePositionY() - 1.f * mySpeedInterval };

	mySprite->SetRelativePosition(position);
	mySprite->SetRelativeRotation(mySprite->GetRelativeRotation() + 1.f * myRotation);
	mySprite->SetSize(myScale);
	
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
	myMaxVectorScale = mySprite->GetSize() * myMaxScale;

	float width = mySprite->GetSize().x * myEmitterWidth;
	myPosition.x = Utils::RandomFloat(-width, width);

	mySprite->SetSize(size);
	mySprite->SetRelativePosition({ mySprite->GetRelativePosition().x + myPosition.x , mySprite->GetRelativePosition().y});
	mySprite->SetRelativeRotation(myRotation);
	mySprite->Activate();
	mySprite->SetZIndex(2000.f);

}

bool EffectSprite::IsAlive()
{
	return myIsAlive;
}
