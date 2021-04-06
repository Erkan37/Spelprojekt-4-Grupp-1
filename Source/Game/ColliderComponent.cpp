/*	
*	Author: Elia Rönning
*/

#include "stdafx.h"
#include "ColliderComponent.h"
#include "PhysicsManager.h"

#include "GameObject.h"
#include "Scene.h"

ColliderComponent::ColliderComponent()
	: myGameObject(nullptr)

	, myX(0.0f)
	, myY(0.0f)
	, myWidth(0.0f)
	, myHeight(0.0f)
	, myCollideOnlyWithPlayer(false)
{}

ColliderComponent::~ColliderComponent()
{
	Scene* scene = myGameObject->GetScene();
	if (scene)
	{
		PhysicsManager& phys = scene->GetPhysics();

		if (!myCollideOnlyWithPlayer)
		{
			for (size_t index = 0Ui64; index < phys.myColliders.size(); ++index)
			{
				if (phys.myColliders[index] == this)
				{
					phys.myColliders.erase(phys.myColliders.begin() + index);
					break;
				}
			}
		}
		else
		{
			for (size_t index = 0Ui64; index < phys.myOnlyPlayerCollisionColliders.size(); ++index)
			{
				if (phys.myOnlyPlayerCollisionColliders[index] == this)
				{
					phys.myOnlyPlayerCollisionColliders.erase(phys.myOnlyPlayerCollisionColliders.begin() + index);
					break;
				}
			}
		}
	}
}

void ColliderComponent::Init(Transform & aTransform, GameObject & aGameObject)
{
	aTransform;

	myGameObject = &aGameObject;

	Scene* scene = myGameObject->GetScene();
	if (scene)
	{
		if (!myCollideOnlyWithPlayer)
		{
			scene->GetPhysics().myColliders.push_back(this);
		}
		else
		{
			scene->GetPhysics().myOnlyPlayerCollisionColliders.push_back(this);
		}
	}
}

GameObject*& ColliderComponent::GetGameObject()
{
	return myGameObject;
}

const float& ColliderComponent::GetX() const
{
	return myX;
}
const float& ColliderComponent::GetY() const
{
	return myY;
}
const float& ColliderComponent::GetWidth() const
{
	return myWidth;
}
const float& ColliderComponent::GetHeight() const
{
	return myHeight;
}

const v2f ColliderComponent::GetPosition() const
{
	return { myX, myY };
}
const v2f ColliderComponent::GetSize() const
{
	return { myWidth, myHeight };
}

ColliderComponent& ColliderComponent::SetX(const float& anX)
{
	myX = anX;

	return *this;
}
ColliderComponent& ColliderComponent::SetY(const float& aY)
{
	myY = aY;

	return *this;
}
ColliderComponent& ColliderComponent::SetWidth(const float& aWidth)
{
	myWidth = aWidth;

	return *this;
}
ColliderComponent& ColliderComponent::SetHeight(const float& aHeight)
{
	myHeight = aHeight;

	return *this;
}

ColliderComponent& ColliderComponent::SetPosition(const v2f& aPosition)
{
	myX = aPosition.x;
	myY = aPosition.y;

	return *this;
}
ColliderComponent& ColliderComponent::SetPosition(const float& anX, const float& aY)
{
	myX = anX;
	myY = aY;

	return *this;
}
ColliderComponent& ColliderComponent::SetSize(const v2f& aSize)
{
	myWidth = aSize.x;
	myHeight = aSize.y;

	return *this;
}
ColliderComponent& ColliderComponent::SetSize(const float& aWidth, const float& aHeight)
{
	myWidth = aWidth;
	myHeight = aHeight;

	return *this;
}

void ColliderComponent::SetCollideOnlyWithPlayer(const bool aCollideWithPlayer)
{
	myCollideOnlyWithPlayer = aCollideWithPlayer;
}

const bool ColliderComponent::GetCollideOnlywithPlayer()
{
	return myCollideOnlyWithPlayer;
}