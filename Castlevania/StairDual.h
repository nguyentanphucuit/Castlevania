#pragma once
#include "HiddenObject.h"

class StairDual : public HiddenObject
{
public:
	StairDual() {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL) {};
};

