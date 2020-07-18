#pragma once
#include "GameObject.h"
#include "Item.h"

#define MONEYRED_WIDTH  30
#define MONEYRED_HEIGHT 30

class IMoneyRed : public Item
{
public:
	IMoneyRed() {
		AddAnimation("MONEYBAG_ANI_RED");
		this->score = 1000;
	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

