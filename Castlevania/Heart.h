#pragma once
#include "GameObject.h"
#include"Item.h"

#define HEART_WIDTH  16
#define HEART_HEIGHT 16

#define SMALL_ANI_HEART 0

#define HEART_MOVING_VX 0.15f
#define HEART_MOVING_VY 0.05f
#define OX_HEIGHT 20 
class CHeart : public Item
{
	
	bool isOnGround = false;
public:
	CHeart() {
		AddAnimation("SMALL_ANI_HEART");
	}
	float ox;// tọa độ trục ox
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	CHeart(float ox);
};

