#include "IBoomerang.h"

void IBoomerang::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Item::Update(dt, scene, coObject);
}

void IBoomerang::Render()
{
	if (isDestroy || time_wait) {
		return;
	}
	animations[0]->Render(nx, x, y);
	////RenderBoundingBox();
}

void IBoomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BOOMERANG_WIDTH;
	b = y + BOOMERANG_HEIGHT;
}
