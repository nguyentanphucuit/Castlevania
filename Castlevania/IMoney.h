#pragma once
#include "Item.h"
#include "Ground.h"


#define MONEY_WIDTH 30
#define MONEY_HEIGHT 30

#define VELOCITY_Y 0.1f
class IMoney :public Item
{
public:
	IMoney() :Item() {
		AddAnimation("MONEYBAG_ANI_COLOR");
	}
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

