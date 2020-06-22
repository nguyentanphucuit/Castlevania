#pragma once
#include "GameObject.h"
#include "Item.h"

#define STOPWATCH_WIDTH 32
#define STOPWATCH_HEIGHT 32

class IStopWatch : public Item
{
public:
	IStopWatch() {
		AddAnimation("ITEM_ANI_STOPWATCH");
	}

	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

