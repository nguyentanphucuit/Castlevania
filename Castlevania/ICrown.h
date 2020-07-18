#pragma once
#include "Item.h"
#include "Ground.h"


#define CROWN_WIDTH 30
#define CROWN_HEIGHT 30

#define VELOCITY_Y 0.1f
class ICrown :public Item
{
public:
	ICrown() :Item() {
		AddAnimation("ITEM_ANI_CROWN");
		this->score = 2000;
	}
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

