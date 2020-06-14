#include "DebrisBrick.h"



void DebrisBrick::Render()
{
	animations[0]->Render(DIRECTION::DEFAULT, x, y);
}

void DebrisBrick::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = t = r = b = 0;
}

void DebrisBrick::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt,scene);
	if (this->isDestroy) return;
	Effect::Update(dt,scene);

	vy += DEBRIS_GRAVITY * dt;
	x += dx;
	y += dy;

}

DebrisBrick::DebrisBrick()
{
	AddAnimation("DEBRIS_ANI");
}

DebrisBrick::DebrisBrick(float vx, float vy)
{
	AddAnimation("DEBRIS_ANI");
	this->vx = vx;
	this->vy = vy;
}


DebrisBrick::~DebrisBrick()
{
}
