#include "stdafx.h"
#include "BashableObjectFactory.hpp"

#include "BashableObject.hpp"

#include "../External/Headers/rapidjson/document.h"
#include "../External/Headers/rapidjson/istreamwrapper.h"
#include <fstream>

void BashableObjectFactory::ReadBashableObjects(Scene* aLevelScene, const std::string& aFilePath)
{
	std::ifstream bashableObjectsFile(aFilePath);
	rapidjson::IStreamWrapper bashableObjectsStream(bashableObjectsFile);

	rapidjson::Document bashableObjects;
	bashableObjects.ParseStream(bashableObjectsStream);

	for (rapidjson::Value::ConstValueIterator bashableObject = bashableObjects["BashableObjects"].Begin(); bashableObject != bashableObjects["BashableObjects"].End(); ++bashableObject)
	{
		const v2f position = v2f((*bashableObject)["Position"]["X"].GetFloat(), (*bashableObject)["Position"]["Y"].GetFloat());
		const float radius = (*bashableObject)["Radius"].GetFloat();

		CreateBashableObject(aLevelScene, position, radius);
	}

	bashableObjectsFile.close();
}

BashableObject* BashableObjectFactory::CreateBashableObject(Scene* aLevelScene, const v2f& aPosition, const float& aRadius)
{
	BashableObject* bashableObject = new BashableObject(aLevelScene);
	bashableObject->Init(aPosition, aRadius);
	return bashableObject;
}