#pragma once
#include "GameObject.h"
#include "Item.h"

#define WHIP_WIDTH 32
#define WHIP_HEIGHT 32

class IWhip: public Item
{
public:
	IWhip() {
		AddAnimation("MORNING_ANI_STAR");
	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT> * coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float &t, float &r, float &b);

};

