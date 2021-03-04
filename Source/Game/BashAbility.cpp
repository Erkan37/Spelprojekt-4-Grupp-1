#include "stdafx.h"
#include "Player.hpp"
#include "BashAbility.h"
#include "PhysicsComponent.h"
#include "InputWrapper.h"

BashAbility::BashAbility()
{
}

void BashAbility::Init()
{
}

void BashAbility::Update()
{
	if (myInput->IsDashing())
	{
		myPhysics->SetVelocityX(myPhysics->GetVelocity().x + 10.f);
	}

}

void BashAbility::Render()
{
}

void BashAbility::AddPlayerPhysics(std::shared_ptr<PhysicsComponent> somePhysics)
{
	myPhysics = somePhysics;
}

void BashAbility::AddInputWrapper(const std::shared_ptr<InputWrapper> aInputWrapper)
{
	myInput = aInputWrapper;
}
