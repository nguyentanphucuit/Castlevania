#include "WFireBomb.h"
#include "Enemy.h"
#include "Brick.h"
#include "Torch.h"
#include "Candle.h"
#include "EffectFactory.h"
#include "Simon.h"

void WFireBomb::Render()
{
	int ani = 0;
	switch (this->state)
	{
	case FIREBOMBSTATE::NORMAL:
		ani = FIREBOMB_ANI_NORMAL;
		animations[ani]->Render(nx, x, y);
		break;
	case FIREBOMBSTATE::BURN:
		ani = FIREBOMB_ANI_BURN;
		animations[ani]->Render(nx, x, y);
		break;
	default:
		break;
	}
}

void WFireBomb::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{

	RenderBoundingBox();
	if (this->isDestroy)
	{
		return;
	}
	
	if (GetTickCount() - time_exist > TIME_FIREBOMB && time_exist !=0) {
		this->isDestroy = true;
		time_exist = 0;
		SetState(FIREBOMBSTATE::NORMAL);
	}
	if (this->state == FIREBOMBSTATE::NORMAL) {
		if (nx == DIRECTION::RIGHT)
		{
			vx = FIREBOMB_SPEED_VX;
		}
		else if (nx == DIRECTION::LEFT) {
			vx = -FIREBOMB_SPEED_VX;
		}
	}
	
	if (this->state == FIREBOMBSTATE::NORMAL) {
		vy += FIREBOMB_GRAVITY * dt;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		if (ny <= 0)
			y += min_ty * dy + ny * 0.4f;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground*>(e->obj)) {
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
				this->SetState(FIREBOMBSTATE::BURN);
				if (time_exist == 0) {
					time_exist = GetTickCount();
				}
				
			}
			else {
				if (e->nx != 0)
					x += dx;
				else if (e->ny < 0) {
					y += dy;
				}

			}
		}

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	for (size_t i = 0; i < coObjects->size(); i++) {
		if (dynamic_cast<Ground*>(coObjects->at(i)))
		{
			auto ground = dynamic_cast<Ground*>(coObjects->at(i));
			if (this->isColliding(ground))
			{
				vx = 0;
				vy = 0;
				this->SetState(FIREBOMBSTATE::BURN);
				if (time_exist == 0) {
					time_exist = GetTickCount();
				}
			}

		}

	}
	Weapon::Update(dt, scene, coObjects);
}

void WFireBomb::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIREBOMB_BBOX_WIDTH;
	b = y + FIREBOMB_BBOX_HEIGHT;
}

void WFireBomb::SetState(FIREBOMBSTATE state)
{
	switch (state) {
	case FIREBOMBSTATE::NORMAL:
		
		break;
	case FIREBOMBSTATE::BURN:
		vy = 0;
		vx = 0;
		break;
	}
	this->state = state;
}

WFireBomb::WFireBomb() :Weapon()
{
	AddAnimation("FIREBOMB_ANI_NORMAL");
	AddAnimation("FIREBOMB_ANI_BURN");
	this->vx = FIREBOMB_SPEED_VX;
	this->vy = -FIREBOMB_SPEED_VY;
}
