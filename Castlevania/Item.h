#pragma once

#include"GameObject.h"

class Item :public CGameObject
{
private:


public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};


};

