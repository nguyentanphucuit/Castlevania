#pragma once
#include "HiddenObject.h"
#include "Item.h"

class HMoney:public HiddenObject
{
	Item* money;
public:
	HMoney() {};
	void SetItem(Item* i) { this->money = i; }
	Item* GetItem() { return this->money; }
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL) {};
};

