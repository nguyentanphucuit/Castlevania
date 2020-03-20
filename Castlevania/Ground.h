#pragma once
#include"HiddenObject.h"
class Ground:public HiddenObject
{
public:
	Ground() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
};

