#pragma once
#include "../External/Headers/CU/Vector2.hpp"

class BashableObject;
class Scene;

class BashableObjectFactory
{
public:
	void ReadBashableObjects(Scene* aLevelScene, const std::string& aFilePath);

	BashableObject* CreateBashableObject(Scene* aLevelScene, const v2f& aPosition, const float& aRadius, const float& aSpeed, const std::vector<v2f>& aWaypoints);

private:

};

