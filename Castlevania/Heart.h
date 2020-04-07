#pragma once
#include "GameObject.h"
#include"Item.h"

#define HEART_WIDTH  16
#define HEART_HEIGHT 16

#define SMALL_ANI_HEART 0
class CHeart : public Item
{
	bool isDestroy = false;
public:
	CHeart() {
		AddAnimation("SMALL_ANI_HEART");
	}
	void SetDestroy() { this->isDestroy = true; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

