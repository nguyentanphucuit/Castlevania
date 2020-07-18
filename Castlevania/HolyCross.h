#pragma once
#include "GameObject.h"
#include "Item.h"

#define HOLYCROSS_WIDTH 33
#define HOLYCROSS_HEIGHT 34

class IHolyCross : public Item
{
public:
	IHolyCross() {
		AddAnimation("ITEM_ANI_HOLYCROSS");
	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

