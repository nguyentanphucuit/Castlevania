#include "BrickWall.h"

void CBrickWall::Render()
{
	if (isDestroy)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void CBrickWall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICKWALL_WIDTH;
	b = y + BRICKWALL_HEIGHT;
}
