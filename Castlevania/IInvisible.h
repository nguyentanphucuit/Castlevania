#pragma once
#include "GameObject.h"
#include "Item.h"

#define INVISIBLE_WIDTH 32
#define INVISIBLE_HEIGHT 32

class IInvisible : public Item
{
public:
	IInvisible() {
		AddAnimation("ITEM_ANI_INVISIBLE");
	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

