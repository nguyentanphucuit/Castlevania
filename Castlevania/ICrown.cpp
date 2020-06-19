#include "ICrown.h"

void ICrown::Render()
{
	if (isDestroy) {
		return;
	}
	animations[0]->Render(DIRECTION::DEFAULT, x, y);
	//RenderBoundingBox();
}

void ICrown::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	CGameObject::Update(dt, scene);
	vy = -VELOCITY_Y;

	bool isCoGround = false;
	for (std::size_t i = 0; i < coObject->size(); i++) {
		if (dynamic_cast<Ground*>(coObject->at(i))) {
			Ground* g = dynamic_cast<Ground*>(coObject->at(i));
			if (this->isColliding(g)) {
				isCoGround = true;
			}
		}
	}
	if (isCoGround) {
		y += dy;
	}
	else
	{
		vx = 0;
		vy = 0;
	}

}

void ICrown::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CROWN_WIDTH;
	b = y + CROWN_HEIGHT;
}
