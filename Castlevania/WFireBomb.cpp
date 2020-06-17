#include "WFireBomb.h"
#include "Enemy.h"
#include "Brick.h"
#include "Torch.h"
#include "Candle.h"
#include "EffectFactory.h"
#include "Simon.h"

void WFireBomb::Render()
{
	animations[0]->Render(nx, x, y);
}

void WFireBomb::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{


	if (this->isDestroy)
	{
		return;
	}
	/*if (nx == DIRECTION::RIGHT)
	{
		this->vx = AXE_SPEED_VX;
	}
	else if (nx == DIRECTION::LEFT) {
		this->vx = -AXE_SPEED_VX;
	}*/
	vx = FIREBOMB_SPEED_VX;
	x += dx;
	y += dy;
	vy += FIREBOMB_GRAVITY * dt;
	CGameObject::Update(dt, scene);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

}

void WFireBomb::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIREBOMB_BBOX_WIDTH;
	b = y + FIREBOMB_BBOX_HEIGHT;
}

WFireBomb::WFireBomb() :Weapon()
{
	AddAnimation("FIREBOMB_ANI");
	this->vx = FIREBOMB_SPEED_VX;
	this->vy = -FIREBOMB_SPEED_VY;
}
