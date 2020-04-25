#include "WDagger.h"


void WDagger::Render()
{
	if (isDestroy) {
		return;
	}
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void WDagger::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + DAGGER_BBOX_WIDTH;
	b = t + DAGGER_BBOX_HEIGHT;
}

void WDagger::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	if (isDestroy) {
		return;
	}
	
	vx = nx > 0 ? this->vx = DAGGER_VX : this->vx = -DAGGER_VX;

	Weapon::Update(dt, scene, coObject);
	
}

