#pragma once
#include "GameObject.h"
#include"Item.h"

#define BHEART_WIDTH  32
#define BHEART_HEIGHT 32

#define SMALL_ANI_HEART 0
class BHeart : public Item
{
	bool isDestroy = false;
public:
	BHeart() {
		AddAnimation("BIG_ANI_HEART");
	}
	void SetDestroy() { this->isDestroy = true; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

