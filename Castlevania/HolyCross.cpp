#include "HolyCross.h"

void IHolyCross::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Item::Update(dt, scene, coObject);
}

void IHolyCross::Render()
{
	if (isDestroy || time_wait) {
		return;
	}
	animations[0]->Render(nx, x, y);
	////RenderBoundingBox();
}

void IHolyCross::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + HOLYCROSS_WIDTH;
	b = y + HOLYCROSS_HEIGHT;
}
