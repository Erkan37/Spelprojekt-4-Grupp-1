#pragma once
#include "GameObject.h"
#include "Animation.hpp"

class Scene;

class Glide : public GameObject
{
public:
	Glide(Scene* aScene);
	~Glide();

	void Init(const v2f& aPosition);

	void Update(const float& aDeltaTime) override;

	void OnCollision(GameObject* aGameObject) override;

private:
	Animation myAnimations[1];

	float myTimer;
	float myDisappearTime;

	bool myIsTaken;
};

