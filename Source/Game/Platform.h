#pragma once
#include "../External/Headers/CU/Vector2.hpp"
#include "GameObject.h"

class Scene;

class Platform : public GameObject
{
public:
	Platform(Scene* aScene);
	~Platform();

	void Init(const v2f& aSize, const v2f& aSpriteSize, const v2f& aPosition);

private:


};

