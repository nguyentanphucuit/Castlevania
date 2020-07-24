#pragma once
#include "HiddenObject.h"

class Abyss : public HiddenObject
{
public:
	Abyss() {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL) {};
};

