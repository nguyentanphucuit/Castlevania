#include "IInvisible.h"

void IInvisible::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Item::Update(dt, scene, coObject);
}

void IInvisible::Render()
{
	if (isDestroy || time_wait) {
		return;
	}
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void IInvisible::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + INVISIBLE_WIDTH;
	b = y + INVISIBLE_HEIGHT;
}
