#include "stdafx.h"
#include "ButtonManager.h"
#include "Game.h"



ButtonManager::ButtonManager(Scene* aScene)
	: GameObject(aScene)
	, myMaxX(0)
	, myMaxY(0)
	, myMinX(0)
	, myMinY(0)
	, myIndex(0)
{}

ButtonManager::~ButtonManager()
{
	for (int i = myButtons.size() - 1; i >= 0; --i)
	{
		delete myButtons[i];
		myButtons[i] = nullptr;
	}
}

void ButtonManager::Init()
{
	//myHighlight = new GameObject();
	//SpriteComponent* spriteHighlight = myHighlight->AddComponent<SpriteComponent>();
	//spriteHighlight->SetSpritePath("Sprites/tempUI/tempHighlight.dds");
	//myHighlight->SetPosition(myButtons[myIndex]->GetPosition());
	//AddButton(myHighlight);

	GameObject::Init();
}

void ButtonManager::Render()
{
	if (!myIsActive) return;

	for (int i = 0; i < myButtons.size(); ++i)
	{
		myButtons[i]->Render();
	}

	//myHighlight->Render();
	GameObject::Render();
}

void ButtonManager::Update(const float& aDeltaTime)
{
	if (!myIsActive) return;

	GameObject::Update(aDeltaTime);
}

void ButtonManager::NextColumn(const int aModifier)
{
	if (aModifier == myColumns ||
		myColumns <= 1 ||
		myIndex + aModifier >= myButtons.size() ||
		myIndex + aModifier < 0)
	{
		return;
	}

	int modifier = aModifier;
	int curPos = myIndex % myColumns;
	int curRow = myIndex / myColumns;

	if (curPos + modifier >= myColumns ||
		curPos + modifier < 0)
	{
		return;
	}

	int potRow = (myIndex + modifier) / myColumns;
	int diff = curRow - potRow;

	if (diff == 0)
	{
		myIndex += modifier;

		//myHighlight->SetPosition(myButtons[myIndex]->GetPosition());
		return;
	}

	while (diff != 0)
	{
		diff = curRow - potRow;
		if (modifier < 0)
		{
			modifier += myColumns;
		}
		else
		{
			modifier -= myColumns;
		}
		potRow = (myIndex + modifier) / myColumns;
		diff = curRow - potRow;
	}

	myIndex += modifier;
	//myHighlight->SetPosition(myButtons[myIndex]->GetPosition());

}

void ButtonManager::NextRow(const int aModifier)
{
	int potIndex = myIndex + (aModifier * myColumns);

	if (potIndex < 0)
	{
		if (myColumns > 1)
		{
			return;
		}
		else
		{
			while (potIndex < 0)
			{
				potIndex += myButtons.size();
			}
		}
	}

	else if (potIndex >= myButtons.size())
	{
		if (myColumns > 1)
		{
			return;
		}
		else
		{
			while (potIndex >= myButtons.size())
			{
				potIndex -= myButtons.size();
			}
		}
	}

	myIndex = potIndex;
	//myHighlight->SetPosition(myButtons[myIndex]->GetPosition());
}

void ButtonManager::SetButtonZIndex(const int aZ)
{
	SetZIndex(aZ);
	for (int i = 0; i < myButtons.size(); i++)
	{
		myButtons[i]->SetZIndex(aZ);
	}

}

void ButtonManager::SetColumns(const int aColumn)
{
	myColumns = aColumn;
	if (myColumns < 1)
	{
		myColumns = 1;
	}
	UpdatePosition();

}

void ButtonManager::SetDistance(const float aTop, const float aBot, const float aLeft, const float aRight)
{
	myMinY = aTop;
	myMaxX = aBot;
	myMinX = aLeft;
	myMaxX = aRight;
	UpdatePosition();
}

void ButtonManager::SetSize(const Tga2D::Vector2f& aSize)
{
	for (int i = 0; i < myButtons.size(); i++)
	{
		//myButtons[i]->SetSize(aSize);
	}
}

void ButtonManager::UpdatePosition()
{
	if (myButtons.empty()) return;

	const int rows = ceil(static_cast<float>(myButtons.size()) / static_cast<float>(myColumns));

	for (int i = 0; i < myButtons.size(); ++i)
	{
		if (myColumns <= 1)
		{
			myButtons[i]->SetPositionX(myMinX + ((Config::width - myMaxX - myMinX) / 2));
		}
		else
		{
			const int currentColumn = i % myColumns;
			const float diff = Config::width - myMaxX - myMinX;
			const int columnMinOne = myColumns - 1;
			const float chunk = diff / columnMinOne;
			const float currentChunk = chunk * currentColumn;
			const float x = myMinX + currentChunk;
			myButtons[i]->SetPositionX(x);
		}
		//if (rows <= 1)
		//{
		//	myButtons[i]->SetPositionY(myMinY + ((Config::height - myMaxY - myMinY) / 2));
		//}
		//else
		//{
		//	const int currentRow = i / myColumns;
		//	const float diff = Config::height - myMaxY - myMinY;
		//	const float chunk = diff / (rows - 1);
		//	const float curChunk = chunk * currentRow;
		//	const float y = myMinY + curChunk;
		//	myButtons[i]->SetPositionY(y);
		//}

		if (i == 0)
		{
			myButtons[i]->SetPositionY(myMinY + ((Config::height - myMaxY - myMinY) / 2));
		}

		else
		{
			int buttonpos = myButtons[i - 1]->GetPositionY();
			buttonpos += myMinY;
			myButtons[i]->SetPositionY(buttonpos);
		}
	}
	//myHighlight->SetPosition(myButtons[myIndex]->GetPosition());
}

void ButtonManager::AddButton(GameObject* aMenuButton)
{
	myButtons.push_back(aMenuButton);
	UpdateIndex(0);
	UpdatePosition();
}

void ButtonManager::UpdateIndex(const int aModifier)
{
	if (myButtons.empty()) return;

	myIndex += aModifier;
	if (myIndex < 0)
	{
		myIndex = myButtons.size() - 1;
	}
	else if (myIndex >= myButtons.size())
	{
		myIndex = 0;
	}
	
	//myHighlight->SetPosition(myButtons[myIndex]->GetPosition());
}

int ButtonManager::GetIndex()
{
	return myIndex;
}

GameObject* ButtonManager::SelectButton()
{
	return myButtons[myIndex];
}
