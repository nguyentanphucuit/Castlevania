#pragma once
#include "GameObject.h"
#include "Item.h"

#define AXE_WIDTH 32
#define AXE_HEIGHT 32

class IAXE : public Item
{
public:
	IAXE() {
		AddAnimation("ITEM_ANI_AXE");
	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

