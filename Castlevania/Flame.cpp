#include "Flame.h"

void Flame::Render()
{
	if (isDestroy)
	{
		return;
	}
	animations[0]->Render(0, x, y);
}

void Flame::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Effect::Update(dt, scene, coObject);
}
