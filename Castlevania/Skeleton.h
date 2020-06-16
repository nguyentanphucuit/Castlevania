#pragma once
#include "Weapon.h"

#define SKELETON_BBOX_WIDTH 32
#define SKELETON_BBOX_HEIGHT 18

#define SKELETON_VX 0.35f

class Skeleton :public Weapon
{
private:
	bool checkup = false;
	bool up = true;
public:
	Skeleton() :Weapon() {
		AddAnimation("ITEM_ANI_DAGGER");
	}

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
};

