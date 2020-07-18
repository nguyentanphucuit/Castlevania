#include "Money1000.h"
#include "define.h"
void Money1000::Render()
{
	if (isDestroy)
	{
		return;
	}
	animations[0]->Render(DIRECTION::DEFAULT, x, y);
}

void Money1000::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Effect::Update(dt, scene, coObject);
}
