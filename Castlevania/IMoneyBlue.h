#pragma once
#include "GameObject.h"
#include "Item.h"

#define MONEYBLUE_WIDTH  30
#define MONEYBLUE_HEIGHT 30

class IMoneyBlue : public Item
{
public:
	IMoneyBlue() {
		AddAnimation("MONEYBAG_ANI_BLUE");
		this->score = 400;
	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

