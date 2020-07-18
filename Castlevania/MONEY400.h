#pragma once
#include "Effect.h"
class Money400 :public Effect
{
public:
	Money400() :Effect() {
		AddAnimation("400_ANI");
	}

	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject = NULL);
};

