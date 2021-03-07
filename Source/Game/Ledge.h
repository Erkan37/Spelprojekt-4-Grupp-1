#pragma once
#include "GameObject.h"

class Scene;
class Player;

class Ledge : public GameObject
{
public:
	Ledge(Scene* aLevelScene);
	~Ledge();

	void Init(const v2f& aPosition, const v2f& aSize);

	void Update(const float& aDeltaTime) override;

	void OnCollision(GameObject* aGameObject) override;

private:
	Player* myPlayer;

	bool myPlayerEntered;
	bool myPlayerIsInThisFrame;

};

