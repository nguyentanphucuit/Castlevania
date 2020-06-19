#pragma once
#include "GameObject.h"
#include "Item.h"

#define BOOMERANG_WIDTH 32
#define BOOMERANG_HEIGHT 32

class IBoomerang : public Item
{
public:
	IBoomerang() {
		AddAnimation("ITEM_ANI_BOOMERANG");
	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

