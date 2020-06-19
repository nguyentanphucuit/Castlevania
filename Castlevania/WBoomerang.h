#pragma once
#include"Weapon.h"

#define BOOMERANG_GRAVITY 0.001f
#define BOOMERANG_SPEED_VX 0.67f
#define BOOMERANG_SPEED_VY 0.45f

#define BOOMERANG_BBOX_WIDTH 30
#define BOOMERANG_BBOX_HEIGHT 28

#define DISTANCE		32
#define VX_LEFT			0.0012f
#define VX_RIGHT		0.0009f
class WBoomerang :public Weapon
{
private:
	bool isFly = false;
	bool isReturn = false;
	bool setVelocyet=false;
public:
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	WBoomerang();
};

