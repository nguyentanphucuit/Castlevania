#pragma once
#include "GameObject.h"
#include "Item.h"

#define DAGGER_WIDTH 32
#define DAGGER_HEIGHT 16

class IDagger : public Item
{
public:
	IDagger() {
		AddAnimation("ITEM_ANI_DAGGER");
	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

