#include "WAxe.h"
#include "Enemy.h"
#include "Brick.h"
#include "Torch.h"
#include "Candle.h"
#include "EffectFactory.h"
#include "Simon.h"
#include "Weapon.h"

void WAxe::Render()
{
	animations[0]->Render(nx, x, y);
}

void WAxe::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{


	if (this->isDestroy)
	{
		return;
	}

	if (nx == DIRECTION::RIGHT)
	{
		this->vx = AXE_SPEED_VX;
	}
	else if (nx == DIRECTION::LEFT) {
		this->vx = -AXE_SPEED_VX;
	}

	vy += AXE_GRAVITY * dt;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	Weapon::Update(dt, scene, coObjects);
	
}

void WAxe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + AXE_BBOX_WIDTH;
	b = y + AXE_BBOX_HEIGHT;
}

WAxe::WAxe() :Weapon()
{
	AddAnimation("AXE_ANI");
	this->nx = DIRECTION::RIGHT;
	this->vx = AXE_SPEED_VX;
	this->vy = -AXE_SPEED_VY;
	this->damage = 2;
}
