#include "Hunchback.h"
#include "Debug.h"
#include "Ground.h"
#include "Simon.h"
#include "debug.h"


void Hunchback::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y + 2;
	right = left + HUNCHBACK_BBOX_WIDTH;
	bottom = top + HUNCHBACK_BBOX_HEIGHT - 2;
}

void Hunchback::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{

	//	if (reSpawn) return;
		//DebugOut(L"update \n");
	CGameObject::Update(dt, scene);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
		// Simple fall down
	vy += HUNCHBACK_GRAVITY * dt;
	if (nx == DIRECTION::RIGHT) {
		vx = HUNCHBACK_WALKING_SPEED;
		
	}
	else if (nx == DIRECTION::LEFT) {
		vx = -HUNCHBACK_WALKING_SPEED;
		
	}
	DebugOut(L"y %d\n", y);
	if (x > _endPos) {
		nx = DIRECTION::LEFT;
	}
	if (x < _startPos) {
		nx = DIRECTION::RIGHT;
	} 

	

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
				OnTouchingGround();
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
}

void Hunchback::Render()
{

	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void Hunchback::OnTouchingGround()
{
	vy -= .4;
}

void Hunchback::Area(int startPos, int endPos)
{
	this->_endPos = endPos;
	this->_startPos = startPos;
}

Hunchback::Hunchback() :Enemy()
{
	AddAnimation("HUNCHBACK_ANI_JUMP");

}

