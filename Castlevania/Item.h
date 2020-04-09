#pragma once

#include"GameObject.h"

#define ITEM_GRAVITY    0.002f
#define ITEM_HIDING		300 

enum class ITEMSTATE
{
	HIDE,
	SHOW,
	DISTROYING,
	DISTROYED
};

class Item :public CGameObject
{
protected:
	DWORD time_exist;
	DWORD time_wait;

public:

	Item() : CGameObject() {
		time_exist = GetTickCount();
	}

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);

};

