#include "stdafx.h"
#include "BashComponent.hpp"

BashComponent::BashComponent()
	:
	myRadius(0.0f)
{
	
}

BashComponent::~BashComponent()
{

}

void BashComponent::SetRadius(const float& aRadius)
{
	myRadius = aRadius;
}

const float BashComponent::GetRadius()
{
	return myRadius;
}