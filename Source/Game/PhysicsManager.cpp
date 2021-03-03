/*
*	Author: Elia Rönning
*/

#include "stdafx.h"
#include "PhysicsManager.h"
#include <vector>
#include "Transform.hpp"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "ColliderComponent.h"
#include "GameWorld.h"
#include "../External/Headers/CU/Utilities.h"

PhysicsManager::PhysicsManager()
	: myColliders(std::vector<ColliderComponent*>())
{}

void PhysicsManager::PhysicsUpdate(const float& aDeltaTime, std::vector<GameObject*>& gameObjects)
{
	for (GameObject* obj : gameObjects)
	{
		if (!obj || !obj->IsActive())
		{
			continue;
		}
		PhysicsComponent* physics = obj->GetComponent<PhysicsComponent>();
		if (!physics || physics->GetIsStatic())
		{
			continue;
		}

		if (physics->GetApplyGravity())
		{
			physics->SetVelocityY(physics->GetVelocityY() + ourGravity * aDeltaTime);
		}

		obj->SetPosition(obj->GetPosition() + (physics->GetVelocity() * aDeltaTime));
	}

	for (int index = 0U; index < static_cast<int>(myColliders.size()); ++index)
	{
		ColliderComponent*& collider1 = myColliders[index];
		GameObject* object1 = collider1->GetGameObject();
		if (!object1 || !object1->IsActive())
		{
			continue;
		}
		PhysicsComponent* physics = object1->GetComponent<PhysicsComponent>();
		if (physics == nullptr)
		{
			continue;
		}

		if (index < static_cast<int>(myColliders.size()) - 1)
		{
			for (int iterator = index + 1U; iterator < static_cast<int>(myColliders.size()); ++iterator)
			{
				ColliderComponent*& collider2 = myColliders[iterator];
				GameObject* object2 = collider2->GetGameObject();

				if (!object2 || !object2->IsActive())
				{
					continue;
				}

				PhysicsComponent* object2Physics = object2->GetComponent<PhysicsComponent>();
				if (object2Physics == nullptr)
				{
					continue;
				}

				if (physics->GetIsStatic() && object2Physics->GetIsStatic())
				{
					continue;
				}

				const v2f obj1size = collider1->GetSize();
				const v2f obj2size = collider2->GetSize();

				const v2f obj1min = object1->GetPosition() + collider1->GetPosition() - (obj1size * .5f);
				const v2f obj1max = obj1min + obj1size;
				const v2f obj2min = object2->GetPosition() + collider2->GetPosition() - (obj2size * .5f);
				const v2f obj2max = obj2min + obj2size;

				const bool xAxisOverlap = obj1min.x <= obj2max.x && obj1max.x >= obj2min.x;
				const bool yAxisOverlap = obj1min.y <= obj2max.y && obj1max.y >= obj2min.y;

				if (xAxisOverlap && yAxisOverlap)
				{
					object1->OnCollision(object2);
					object2->OnCollision(object1);

					if (!object2Physics->GetCanCollide() || !physics->GetCanCollide())
					{
						continue;
					}

					const float overlapX1 = obj1max.x - obj2min.x;
					const float overlapX2 = obj1min.x - obj2max.x;
					const float overlapX = Utils::Abs(overlapX1) < Utils::Abs(overlapX2) ? overlapX1 : overlapX2;

					const float overlapY1 = obj1min.y - obj2max.y;
					const float overlapY2 = obj1max.y - obj2min.y;
					const float overlapY = Utils::Abs(overlapY1) < Utils::Abs(overlapY2) ? overlapY1 : overlapY2;

					const bool& obj1Static = physics->GetIsStatic();
					const bool& obj2Static = object2Physics->GetIsStatic();

					if (Utils::Abs(overlapX) > Utils::Abs(overlapY))
					{
						object1->Landed();
						object2->Landed();

						if (!obj1Static)
						{
							object1->SetPositionY(object1->GetPositionY() - overlapY);
							physics->SetVelocityY(0.0f);
						}
						if (!obj2Static)
						{
							object2->SetPositionY(object2->GetPositionY() + overlapY);
							object2Physics->SetVelocityY(0.0f);
						}
					}
					else
					{
						if (!obj1Static)
						{
							object1->SetPositionX(object1->GetPositionX() - overlapX);
							physics->SetVelocityX(0.0f);
						}
						if (!obj2Static)
						{
							object2->SetPositionX(object2->GetPositionX() + overlapX);
							object2Physics->SetVelocityX(0.0f);
						}
					}
				}
			}
		}
	}
}