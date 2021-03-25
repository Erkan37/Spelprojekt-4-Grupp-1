#pragma once
#include "GameObject.h"

class Scene;

class Glide : public GameObject
{
public:
	Glide(Scene* aScene);
	~Glide();

	void Init(const v2f& aPosition);

	void OnCollision(GameObject* aGameObject) override;

private:


};

