#include "BHeart.h"

void BHeart::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Item::Update(dt, scene, coObject);
}

void BHeart::Render()
{
	if (isDestroy || time_wait)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	////RenderBoundingBox();
}

void BHeart::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BHEART_WIDTH;
	b = y + BHEART_HEIGHT;
}
