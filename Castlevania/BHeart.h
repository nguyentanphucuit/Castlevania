#pragma once
#include "GameObject.h"
#include "Item.h"

#define BHEART_WIDTH  24
#define BHEART_HEIGHT 16

#define SMALL_ANI_HEART 0
class BHeart : public Item
{
public:
	BHeart() {
		AddAnimation("BIG_ANI_HEART");
	}
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

