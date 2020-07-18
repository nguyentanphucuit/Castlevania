#include "Money700.h"
#include "define.h"
void Money700::Render()
{
	if (isDestroy)
	{
		return;
	}
	animations[0]->Render(DIRECTION::DEFAULT, x, y);
}

void Money700::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Effect::Update(dt, scene, coObject);
}
