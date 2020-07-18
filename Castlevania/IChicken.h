#pragma once
#include "GameObject.h"
#include "Item.h"

#define CHICKEN_WIDTH  34
#define CHICKEN_HEIGHT 28

#define ITEM_ANI_CHICKEN 0
class IChicken : public Item
{
public:
	IChicken() {
		AddAnimation("ITEM_ANI_CHICKEN");
		this->hp = 6;
	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

