#pragma once
#include "HiddenObject.h"
class RetroGrade : public HiddenObject
{
public : 
	RetroGrade() {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL) {};
};

