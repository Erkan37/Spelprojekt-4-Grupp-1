#include "stdafx.h"
#include "UIManager.h"
#include "Game.h"

UIManager::UIManager(Scene* aScene)
	: GameObject(aScene)
	, myIndex(0)
	, myColumns(1)
{}

UIManager::~UIManager()
{
	for (int i = myButtons.size() - 1; i >= 0; --i)
	{
		delete myButtons[i];
		myButtons[i] = nullptr;
	}
	myButtons.clear();
}

void UIManager::Init()
{
	GameObject::Init();
}

void UIManager::Render()
{
	if (!myIsActive) return;

	for (int i = 0; i < myButtons.size(); ++i)
	{
		myButtons[i]->Render();
	}

	GameObject::Render();
}

void UIManager::Update(const float& aDeltaTime)
{
	if (!myIsActive) return;

	GameObject::Update(aDeltaTime);
}

void UIManager::UpdateIndex(const int aModifier)
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
}

void UIManager::UpdateButtonPosition()
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
		if (rows <= 1)
		{
			myButtons[i]->SetPositionY(myMinY + ((Config::height - myMaxY - myMinY) / 2));
		}
		else
		{
			const int currentRow = i / myColumns;
			const float diff = Config::height - myMaxY - myMinY;
			const float chunk = diff / (rows - 1);
			const float curChunk = chunk * currentRow;
			const float y = myMinY + curChunk;
			myButtons[i]->SetPositionY(y);
		}
	}

}

void UIManager::AddButton(GameObject* aMenuButton)
{
	myButtons.push_back(aMenuButton);
	UpdateIndex(0);
	UpdateButtonPosition();
}

void UIManager::NextRow(const int aModifier)
{
	int potIndex = myIndex + (aModifier * myColumns);

	if (potIndex < 0)
	{
		if (myColumns > 0)
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
}

void UIManager::SetColumns(const int aColumn)
{
	myColumns = aColumn;
	if (myColumns < 1)
	{
		myColumns = 1;
	}
	UpdateButtonPosition();
}

void UIManager::SetDistance(const float aTop, const float aBot, const float aLeft, const float aRight)
{
	myMinY = aTop;
	myMaxX = aBot;
	myMinX = aLeft;
	myMaxX = aRight;
	UpdateButtonPosition();
}

int UIManager::GetIndex()
{
	return myIndex;
}

GameObject* UIManager::SelectButton()
{
	return myButtons[myIndex];
}
