#include "Platform.h"

void CPlatform::Render()
{
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void CPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PLATFORM_BBOX_WIDTH;
	b = y + PLATFORM_BBOX_HEIGHT;
}