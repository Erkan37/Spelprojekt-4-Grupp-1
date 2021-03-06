#pragma once
#include "GameObject.h"

class Scene;

class Ledge : public GameObject
{
public:
	Ledge(Scene* aLevelScene);
	~Ledge();

	void Init(const v2f& aPosition, const v2f& aSize);

private:


};

