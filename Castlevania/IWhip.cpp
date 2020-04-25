#include "IWhip.h"

void IWhip::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Item::Update(dt, scene, coObject);
}

void IWhip::Render()
{
	if (isDestroy || time_wait) {
		return;
	}
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void IWhip::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + WHIP_WIDTH;
	b = y + WHIP_HEIGHT;
}
