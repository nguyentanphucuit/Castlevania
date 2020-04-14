#pragma once
#include "Weapon.h"

#define DAGGER_BBOX_WIDTH 32
#define DAGGER_BBOX_HEIGHT 18

#define DAGGER_VX 0.5f

class WDagger:public Weapon
{
public:
	WDagger() :Weapon() {
		AddAnimation("DAGGER_ITEM_ANI");
	}

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
};

