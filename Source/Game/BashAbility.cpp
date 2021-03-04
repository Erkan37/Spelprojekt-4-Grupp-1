#include "stdafx.h"
#include "Player.hpp"
#include "BashAbility.h"
#include "PhysicsComponent.h"

BashAbility::BashAbility()
{
}

void BashAbility::Init()
{
}

void BashAbility::Update()
{
	PhysicsComponent* physics = myPlayer->GetComponent<PhysicsComponent>();


	physics->SetVelocityX(physics->GetVelocity().x + 1.f);

}

void BashAbility::Render()
{
}

void BashAbility::AddPlayerPhysics(std::shared_ptr<Player> aPlayer)
{
	myPlayer = aPlayer;
}
