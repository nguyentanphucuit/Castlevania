#pragma once
#include "GameObject.h"

#define PLATFORM_BBOX_WIDTH  64
#define PLATFORM_BBOX_HEIGHT 16

class CPlatform : public CGameObject
{
public:
	CPlatform() {
		AddAnimation("PLATFORM_ANI");

	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};