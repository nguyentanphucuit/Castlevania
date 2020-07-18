#pragma once
#include"Enemy.h"

#define AXE_GRAVITY 0.001f
#define AXE_SPEED_VX 0.15f
#define AXE_SPEED_VY 0.45f

#define AXE_BBOX_WIDTH 30
#define AXE_BBOX_HEIGHT 28


class Bone :public Enemy
{
public:
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	Bone();
};

