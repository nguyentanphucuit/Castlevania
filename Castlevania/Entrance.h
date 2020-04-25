#pragma once
#include "HiddenObject.h"

class Entrance : public HiddenObject
{
public :
	Entrance() {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL) {};
};

