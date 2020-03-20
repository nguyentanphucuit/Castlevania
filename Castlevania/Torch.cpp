#include "Torch.h"

void CTorch::Render()
{
	if (isDestroy)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	RenderBoundingBox();
}

void CTorch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + TORCH_WIDTH;
	b = y + TORCH_HEIGHT;
}
