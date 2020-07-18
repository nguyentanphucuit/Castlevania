#pragma once
#include "GameObject.h"
#include "Item.h"

#define TRIPLESHOT_WIDTH  29
#define TRIPLESHOT_HEIGHT 29

class TripleShot : public Item
{
	int numShot = 3;
public:
	TripleShot() {
		AddAnimation("ITEM_ANI_TRIPLESHOT");

	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetNumShot() { return this->numShot; };
};

