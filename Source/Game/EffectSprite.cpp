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

	

	LerpSpeed(aDeltatime);
	LerpScale(aDeltatime);
	LerpColor(aDeltatime);

	v2f position = {};

	if (!myIsLockedPos)
	{
		position.x = mySprite->GetRelativePositionX() + direction.x * mySpeedInterval * aDeltatime;
		position.y = mySprite->GetRelativePositionY() + direction.y * mySpeedInterval * aDeltatime;
	}
	else
	{
		float speedX = myDirection.x * mySpeedInterval * aDeltatime;
		float speedY = myDirection.y * mySpeedInterval * aDeltatime;

		position.x = mySprite->GetRelativePositionX() + speedX;
		position.y = mySprite->GetRelativePositionY() + speedY;
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
	myCurrentColor = myStartColor;

	ResetColor();
	
	v2f size = mySprite->GetSize() * myMinScale;
	myMaxVectorScale = mySprite->GetSize() * myMaxScale;

	v2f position = {};

	float width = myEmitterWidth;
	position.x = Utils::RandomFloat(-width, width);

	float height = myEmitterHeigth;
	position.y = Utils::RandomFloat(0, -height);

	if (myIsLockedPos)
	{
		myDirection.x = Utils::RandomFloat(myEmitterAngular.x, myEmitterAngular.z);
		myDirection.y = Utils::RandomFloat(myEmitterAngular.y, myEmitterAngular.w);
	}

	position = mySprite->GetRelativePosition() + position + myOffset;
	
	mySprite->SetSize(size);
	mySprite->SetRelativePosition(position);
	mySprite->SetRelativeRotation(myRotation);
	mySprite->Activate();

}

bool EffectSprite::IsAlive()
{
	return myIsAlive;
}

void EffectSprite::SetInactive()
{
	myIsAlive = false;
}

void EffectSprite::LerpSpeed(const float& aDeltatime)
{
	myMinSpeed = Utils::Lerp(myMinSpeed, myMaxSpeed, mySpeedAcceleration * aDeltatime);
	mySpeedInterval = myMinSpeed;
}

void EffectSprite::LerpScale(const float& aDeltatime)
{
	myScale.x = Utils::Lerp(mySprite->GetSize().x, myMaxVectorScale.x, myGrowthAcceleration * aDeltatime);
	myScale.y = Utils::Lerp(mySprite->GetSize().y, myMaxVectorScale.y, myGrowthAcceleration * aDeltatime);

}

void EffectSprite::LerpColor(const float& aDeltaTime)
{
	float speed = 0.f;
	const float timer = myTotalTimer / myLifeTime;

	myCurrentColor.myR = Utils::Lerp(myCurrentColor.myR, myEndColor.myR, speed * aDeltaTime);
	myCurrentColor.myG = Utils::Lerp(myCurrentColor.myG, myEndColor.myG, aDeltaTime);
	myCurrentColor.myB = Utils::Lerp(myCurrentColor.myB, myEndColor.myB, aDeltaTime);

	ResetColor();
}

void EffectSprite::ResetColor()
{
	mySprite->SetColor({ myCurrentColor.myR, myCurrentColor.myG, myCurrentColor.myB, myCurrentColor.myA});
}
