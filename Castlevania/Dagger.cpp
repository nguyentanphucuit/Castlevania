#include "Dagger.h"

void CDagger::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	Item::Update(dt, scene, coObject);
}

void CDagger::Render()
{
	if (isDestroy || time_wait) {
		return;
	}
	animations[0]->Render(nx, x, y);
	RenderBoundingBox();
}

void CDagger::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + DAGGER_WIDTH;
	b = y + DAGGER_HEIGHT;
}
