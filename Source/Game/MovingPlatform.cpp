#include "stdafx.h"
#include "MovingPlatform.hpp"
#include "Player.hpp"
#include "Button.h"
#include "AudioComponent.h"
#include "WaypointComponent.hpp"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "PhysicsComponent.h"

#include "GameWorld.h"
#include "Timer.h"

#include "../External/Headers/CU/Utilities.h"

MovingPlatform::MovingPlatform(Scene* aLevelScene)
	:
	Platform(aLevelScene),
	myButton(new Button(aLevelScene)),
	myWaypointComponent(nullptr)
{
	SetZIndex(93);
	myType = eMovingPlatformType::RegularPlatform;
	myMaterial = 3;
	myPercentageYValue = {};
	myWaypointComponent = AddComponent<WaypointComponent>();
	myWaypointComponent->SetOwner(this);
	myAddedButton = false;
	myRevertOn = {};
	AudioComponent* audio = AddComponent<AudioComponent>();
	audio->AddAudio(AudioList::MovingPlatform);
	audio->SetRadius(170);
}

MovingPlatform::~MovingPlatform()
{
	AudioComponent* audio = GetComponent<AudioComponent>();
	audio->StopAudio();
}

void MovingPlatform::AdjustXOffset()
{
	constexpr float xOffset = 4.0f;

	ColliderComponent* collider = GetComponent<ColliderComponent>();
	collider->SetPosition(v2f(collider->GetSize().x / 2.0f - xOffset, 4.0f));
	GetComponent<SpriteComponent>()->SetRelativePosition(v2f(-xOffset, 0.0f));
}

void MovingPlatform::Update(const float& aDeltaTime)
{
	if (myType == eMovingPlatformType::RegularPlatform || myType == eMovingPlatformType::ReversePlatform)
		myWaypointComponent->Move(aDeltaTime);

	if (myAddedButton)
	{
		if (myButton->GetActiveButton())
		{
			if (myType == eMovingPlatformType::MovingPlatform)
				myWaypointComponent->Move(aDeltaTime);
			else if (myType == eMovingPlatformType::ReversePlatform && !myRevertOn)
			{
				myRevertOn = true;
				myWaypointComponent->ReverseWaypoints();
			}
			else if (myType == eMovingPlatformType::PointAtoBPlatform)
			{
				if (!myWaypointComponent->IsAtLastCheckPoint())
					myWaypointComponent->Move(aDeltaTime);
				else
					myWaypointComponent->ResetVelocity();
			}
		}
	}

	Platform::Update(aDeltaTime);
}

void MovingPlatform::SetWaypoints(const std::vector<v2f>& aWaypoints)
{
	std::vector<v2f> adjustedWaypoints;

	for (const v2f& waypoint : aWaypoints)
	{
		adjustedWaypoints.push_back(waypoint);
	}

	myWaypointComponent->SetWaypoints(aWaypoints);

}

void MovingPlatform::AddButton(v2f aPosition, eMovingPlatformType aPlatformType)
{
	myAddedButton = true;
	myType = aPlatformType;
	myButton->Init(GetPosition(), aPosition);
}

void MovingPlatform::OnCollision(GameObject* aGameObject)
{
	Player* player = dynamic_cast<Player*>(aGameObject);

	if (player)
	{
		v2f velo = myWaypointComponent->GetVelocity();

		player->SetGroundIndex(myMaterial);
		player->SetPlatformVelocity(velo);

		float insensitivity = CGameWorld::GetInstance()->GetTimer()->GetDeltaTime() * velo.y;
		insensitivity = Utils::Min(1.8f, Utils::Abs(insensitivity));

		//Magic platform! Spooky wooh!
		const float platformPositionX = GetPosition().x + GetComponent<ColliderComponent>()->GetWidth() / 2;
		const float xOffset = 4.0f;

		if (Utils::Abs(player->GetPosition().x - platformPositionX + xOffset) <= GetComponent<ColliderComponent>()->GetWidth() / 2)
		{
			player->SetPositionY(GetPositionY() - (7.8f - insensitivity));
		}
	}
}
