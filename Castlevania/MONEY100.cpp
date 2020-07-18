#include "Money100.h"
#include "define.h"
void Money100::Render()
{
	if (isDestroy)
	{
		return;
	}
	animations[0]->Render(DIRECTION::DEFAULT, x, y);
}

void Money100::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Effect::Update(dt, scene, coObject);
}
