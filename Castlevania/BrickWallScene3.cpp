#include "BrickWallScene3.h"

void CBrickWallS3::Render()
{
	if (isDestroy)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void CBrickWallS3::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICKWALLS3_WIDTH;
	b = y + BRICKWALLS3_HEIGHT;
}
