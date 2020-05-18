#pragma once
#include "HiddenObject.h"
class Stair : public HiddenObject
{
public:
	Stair() {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL) {};
};

