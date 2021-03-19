#pragma once
#include "../External/Headers/CU/Vector2.hpp"

class BashableObject;
class Scene;

class BashableObjectFactory
{
public:
	BashableObject* CreateBashableObject(Scene* aLevelScene, const v2f& aPosition, const float& aRadius, const float& aSpeed, const std::vector<v2f>& aWaypoints);

private:

};

