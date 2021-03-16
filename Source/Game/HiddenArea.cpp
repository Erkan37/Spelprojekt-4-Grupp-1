#include "stdafx.h"
#include "HiddenArea.hpp"
#include "Player.hpp"

#include "SpriteComponent.h"

#include "Scene.h"

HiddenArea::HiddenArea(Scene* aLevelScene, const v2f& aPosition, const v2f& aSize)
	:
	GameObject(aLevelScene)
{
	SetPosition(aPosition);

	myHiddenSprite = AddComponent<SpriteComponent>();
	myHiddenSprite->SetSpritePath("Sprites/Temp/HiddenArea.dds");
	myHiddenSprite->SetSize(aSize);
}

HiddenArea::~HiddenArea()
{

}

void HiddenArea::Update(const float& aDeltaTime)
{
	if (myPlayerCollided)
	{

	}
	else
	{

	}

	myPlayerCollided = false;
}

void HiddenArea::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);
	if (player)
	{
		myHiddenSprite->SetColor(v4f(1.0f, 1.0f, 1.0f, myOpacity));
	}
}