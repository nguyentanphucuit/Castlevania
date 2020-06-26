#include "Heart.h"
#include "Ground.h"
#include "debug.h"
void CHeart::Render()
{
	if (isDestroy)
	{
		return;
	}
	animations[0]->Render(DIRECTION::DEFAULT, x, y);
	//RenderBoundingBox();
}
void CHeart::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObject)
{
	DebugOut(L"x=%f y=%f \n", x, y);
	CGameObject::Update(dt, scene);
	this->vy = HEART_MOVING_VY;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	coEvents.clear();
	CalcPotentialCollisions(coObject, coEvents);

	if (coEvents.size() == 0)
	{
		y += dy;
		x = OX_HEIGHT * sin(y * HEART_MOVING_VX) + ox;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground*>(e->obj)) {
				this->isOnGround = true;
				x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty * dy + ny * 0.1f;
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
			else {
				if (!this->isOnGround)
				{
					y += dy;
					x = OX_HEIGHT * sin(y * HEART_MOVING_VX) + ox;
				}

			}
		}
	}
}
void CHeart::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + HEART_WIDTH;
	b = y + HEART_HEIGHT;
}

CHeart::CHeart(float ox)
{
	AddAnimation("SMALL_ANI_HEART");
	this->ox = ox;
	
}


