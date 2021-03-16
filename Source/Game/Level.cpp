#include "stdafx.h"
#include "Level.hpp"

Level::Level(Scene* aScene, const int aID)
{
	myScene = aScene;
	myID = aID;
	myIsActive = false;
}

Level::~Level()
{

}

void Level::Activate()
{
	myIsActive = true;
}

void Level::Deactivate()
{
	myIsActive = false;
}

Scene* Level::GetScene()
{
	return myScene;
}

const int& Level::GetID()
{
	return myID;
}

const bool Level::GetIsActive()
{
	return myIsActive;
}