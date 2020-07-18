#pragma once
#include "GameObject.h"
#include "Item.h"

#define DOUBLESHOT_WIDTH  29
#define DOUBLESHOT_HEIGHT 29

class DoubleShot : public Item
{
	int numShot = 2;
public:
	DoubleShot() {
		AddAnimation("ITEM_ANI_DOUBLESHOT");

	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetNumShot() { return this->numShot; };
};

