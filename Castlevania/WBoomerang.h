#pragma once
#include"Weapon.h"

#define BOOMERANG_GRAVITY 0.001f
#define BOOMERANG_SPEED_VX 0.45f
#define BOOMERANG_SPEED_VY 0.45f

#define BOOMERANG_BBOX_WIDTH 30
#define BOOMERANG_BBOX_HEIGHT 28


class WBoomerang :public Weapon
{
public:
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	WBoomerang();
};

