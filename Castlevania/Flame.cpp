#include "Flame.h"

void Flame::Render()
{
	animations[0]->Render(0, x, y);
}

void Flame::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Effect::Update(dt, scene, coObject);
}
