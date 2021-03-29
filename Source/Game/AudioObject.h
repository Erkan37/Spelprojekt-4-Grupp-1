#pragma once
#include "GameObject.h"

enum class AudioList;

class AudioObject : public GameObject
{
public:
	AudioObject(Scene* aScene, const int aType);

private:
	AudioList myType;
};

