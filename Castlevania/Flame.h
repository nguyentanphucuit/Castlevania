#pragma once
#include "Effect.h"
class Flame:public Effect
{
public:
	Flame() :Effect() {
		AddAnimation("FLAME_ANI_BURNING");
	}

	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
};

