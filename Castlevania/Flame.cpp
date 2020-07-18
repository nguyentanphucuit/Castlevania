#include "Flame.h"
#include "define.h"
void Flame::Render()
{
	if (isDestroy)
	{
		return;
	}
	animations[0]->Render(DIRECTION::DEFAULT, x, y);
	
}

void Flame::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Effect::Update(dt, scene, coObject);
}
