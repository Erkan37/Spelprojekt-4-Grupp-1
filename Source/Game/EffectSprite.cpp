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

	v2f direction = { std::cosf(myEmitterAngle * myPI / 180.f), -std::sinf(myEmitterAngle * myPI / 180.f) };

	const float timer = myTotalTimer / myLifeTime;

	myScale.x = Utils::Lerp(mySprite->GetSize().x, myMaxVectorScale.x, timer);
	myScale.y = Utils::Lerp(mySprite->GetSize().y, myMaxVectorScale.y, timer);

	v2f position = {};

	if (!myIsLockedPos)
	{
		position.x = mySprite->GetRelativePositionX() + direction.x * mySpeedInterval * aDeltatime;
		position.y = mySprite->GetRelativePositionY() + direction.y * mySpeedInterval * aDeltatime;
	}
	else
	{
		position.x = mySprite->GetRelativePositionX() + myDirection.x * mySpeedInterval * aDeltatime;
		position.y = mySprite->GetRelativePositionY() + myDirection.y * mySpeedInterval * aDeltatime;
	}

	mySprite->SetRelativePosition(position);
	mySprite->SetRelativeRotation(mySprite->GetRelativeRotation() + myRotation * aDeltatime);
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

	v2f position = {};

	float width = myEmitterWidth;
	position.x = Utils::RandomFloat(-width, width);

	float height = myEmitterHeigth;
	position.y = Utils::RandomFloat(0, -height);

	if (myIsLockedPos)
	{
		v2f rotationDirection = {};
		v2f rotationDirection2 = {};

		rotationDirection = { std::cosf((myEmitterStartAngle * myPI) / 180.f), std::sinf((myEmitterStartAngle * myPI) / 180.f) };
		rotationDirection2 = { std::cosf((myEmitterEndAngle * myPI) / 180.f), std::sinf((myEmitterEndAngle * myPI) / 180.f) };

		myDirection.x = Utils::RandomFloat(rotationDirection.x, rotationDirection2.x);
		myDirection.y = Utils::RandomFloat(rotationDirection.y, rotationDirection2.y);
	}
	
	mySprite->SetSize(size);
	mySprite->SetRelativePosition({ mySprite->GetRelativePosition().x + position.x , mySprite->GetRelativePosition().y + position.y});
	mySprite->SetRelativeRotation(myRotation);
	mySprite->Activate();

}

bool EffectSprite::IsAlive()
{
	return myIsAlive;
}
