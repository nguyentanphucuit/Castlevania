#pragma once
#include "HiddenObject.h"
#include "Item.h"

class HCrown :public HiddenObject
{
	Item* money;
public:
	HCrown() {};
	void SetItem(Item* i) { this->money = i; }
	Item* GetItem() { return this->money; }
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL) {};
};

