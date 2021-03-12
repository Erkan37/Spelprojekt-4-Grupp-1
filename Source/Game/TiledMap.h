#pragma once
#include "Scene.h"

namespace tson
{
	class Layer;
}

class Scene; 

class TiledMap
{
public:
	bool Load(const std::string& aPath, Scene*);

private:
	void ParsePlatforms(tson::Layer*, Scene*);
};

