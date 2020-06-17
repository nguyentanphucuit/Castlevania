#pragma once
#include"Weapon.h"

#define AXE_GRAVITY 0.001f
#define AXE_SPEED_VX 0.2f
#define AXE_SPEED_VY 0.45f

#define AXE_BBOX_WIDTH 30
#define AXE_BBOX_HEIGHT 28


class WAxe :public Weapon
{
public:
	virtual void Render();
	virtual void Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	WAxe();
};

