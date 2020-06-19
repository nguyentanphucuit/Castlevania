#include "IFireBomb.h"

void IFireBomb::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Item::Update(dt, scene, coObject);
}

void IFireBomb::Render()
{
	if (isDestroy || time_wait) {
		return;
	}
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void IFireBomb::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIREBOMB_WIDTH;
	b = y + FIREBOMB_HEIGHT;
}
