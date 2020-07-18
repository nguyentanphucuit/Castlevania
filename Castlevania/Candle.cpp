#include "Candle.h"

void CCandle::Render()
{
	if (isDestroy)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	////RenderBoundingBox();
}

void CCandle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CANDLE_WIDTH;
	b = y + CANDLE_HEIGHT;
}
