#include "IMoney.h"

void IMoney::Render()
{
	if (isDestroy) {
		return;
	}
	animations[0]->Render(0, x, y);
	//RenderBoundingBox();
}

void IMoney::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	CGameObject::Update(dt, scene);
	vy = -0.1f;

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

void IMoney::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MONEY_WIDTH;
	b = y + MONEY_HEIGHT;
}
