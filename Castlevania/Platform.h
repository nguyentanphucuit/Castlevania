#pragma once
#include "GameObject.h"

#define PLATFORM_BBOX_WIDTH  64
#define PLATFORM_BBOX_HEIGHT 16

#define PLATFORM_SPEED  0.02f

class CPlatform : public CGameObject
{
public:
	CPlatform() {
		AddAnimation("PLATFORM_ANI");
		vx = PLATFORM_SPEED;
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects);
};