#pragma once
#include"Weapon.h"

#define FIREBOMB_GRAVITY 0.001f
#define FIREBOMB_SPEED_VX 0.2f
#define FIREBOMB_SPEED_VY 0.45f

#define FIREBOMB_BBOX_WIDTH 30
#define FIREBOMB_BBOX_HEIGHT 28


class WFireBomb :public Weapon
{
public:
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	WFireBomb();
};

