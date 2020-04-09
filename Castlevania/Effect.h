#pragma once

#include "GameObject.h"

#define EFFECT_TIME_LIFE 300
class Effect:public CGameObject
{
protected:
	DWORD time_exist = 0;
public:
	Effect() :CGameObject() {
		time_exist = GetTickCount();
	}
	
	virtual void Render() {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { l = t = r = b = 0; };
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
};

