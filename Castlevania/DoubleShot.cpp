#include "DoubleShot.h"

void DoubleShot::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Item::Update(dt, scene, coObject);
}

void DoubleShot::Render()
{
	if (isDestroy || time_wait)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	////RenderBoundingBox();
}

void DoubleShot::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + DOUBLESHOT_WIDTH;
	b = y + DOUBLESHOT_HEIGHT;
}
