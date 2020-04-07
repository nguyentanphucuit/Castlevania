#pragma once
#include"HiddenObject.h"
class Ground:public HiddenObject
{
public:
	Ground() {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
};

