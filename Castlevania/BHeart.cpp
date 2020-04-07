#include "BHeart.h"

void BHeart::Render()
{
	if (isDestroy)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	RenderBoundingBox();
}

void BHeart::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BHEART_WIDTH;
	b = y + BHEART_HEIGHT;
}
