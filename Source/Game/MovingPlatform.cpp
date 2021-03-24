#include "stdafx.h"
#include "MovingPlatform.hpp"
#include "Player.hpp"
#include "Button.h"
#include "AudioComponent.h"
#include "WaypointComponent.hpp"
#include "SpriteComponent.h"
#include "ColliderComponent.h"

MovingPlatform::MovingPlatform(Scene* aLevelScene)
	:
	Platform(aLevelScene),
	myButton(new Button(aLevelScene)),
	myWaypointComponent(nullptr)
{
	SetZIndex(93);
	myTypeIndex = 1;
	myWaypointComponent = AddComponent<WaypointComponent>();
	myWaypointComponent->SetOwner(this);
	myAddedButton = false;
	AudioComponent* audio = AddComponent<AudioComponent>();
	audio->AddAudio(AudioList::MovingPlatform);
	audio->SetRadius(200);
	audio->PlayAudio();
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
	if (!myAddedButton)
		myWaypointComponent->Move(aDeltaTime);
	else
	{
		if (myButton->GetActiveButton())
			myWaypointComponent->Move(aDeltaTime);
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
	if (!myAddedButton || myButton->GetActiveButton())
	{
		Player* player = dynamic_cast<Player*>(aGameObject);
		if (player)
		{
			player->SetGroundIndex(myTypeIndex);
			player->SetPlatformVelocity(myWaypointComponent->GetVelocity());
		}
	}
}