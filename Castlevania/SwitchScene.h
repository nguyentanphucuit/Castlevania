#pragma once
#include "HiddenObject.h"
class SwitchScene :public HiddenObject
{
	int sceneID;
	std::string border;

public:
	int GetSceneID() { return this->sceneID; }
	SwitchScene(int sceneID) : sceneID(sceneID) {};
};

