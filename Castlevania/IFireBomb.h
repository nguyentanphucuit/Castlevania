#pragma once
#include "GameObject.h"
#include "Item.h"

#define FIREBOMB_WIDTH 32
#define FIREBOMB_HEIGHT 32

class IFireBomb : public Item
{
public:
	IFireBomb() {
		AddAnimation("ITEM_ANI_FIREBOMB");
	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

