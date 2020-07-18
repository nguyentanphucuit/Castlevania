#pragma once
#include "GameObject.h"
#include "Item.h"

#define MONEYWHITE_WIDTH  30
#define MONEYWHITE_HEIGHT 30

class IMoneyWhite : public Item
{
public:
	IMoneyWhite() {
		AddAnimation("MONEYBAG_ANI_WHITE");
		this->score = 700;
	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

