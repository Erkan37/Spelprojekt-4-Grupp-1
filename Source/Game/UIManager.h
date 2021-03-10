#pragma once
#include "GameObject.h"
#include <vector>

class UIManager
	: public GameObject
{
public:
	UIManager(Scene* aScene = nullptr);
	~UIManager();

	void Init();
	void Render();
	void Update(const float& aDeltaTime);
	void UpdateIndex(const int aModifier);
	void UpdateButtonPosition();
	void AddButton(GameObject* aMenuButton);
	void NextRow(const int aModifier);
	void SetColumns(const int aColumn);
	void SetDistance(const float aTop, const float aBot, const float aLeft, const float aRight);

	int GetIndex();

	GameObject* SelectButton();


private:
	float myMaxX;
	float myMaxY;
	float myMinX;
	float myMinY;

	int myColumns;
	int myIndex;
	
	std::vector<GameObject*> myButtons;
};

