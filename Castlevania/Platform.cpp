#include "Platform.h"
#include "Ground.h"

void CPlatform::Render()
{
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void CPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PLATFORM_BBOX_WIDTH;
	b = y + PLATFORM_BBOX_HEIGHT;
}

void CPlatform::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, scene);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
		// Simple fall down
	//if (nx == DIRECTION::RIGHT) vx = PLATFORM_SPEED;
	//else if (nx == DIRECTION::LEFT) vx = -PLATFORM_SPEED;

	/*if (x > 2340) {
		nx = DIRECTION::LEFT;

	}
	if (x < 2170){
		nx = DIRECTION::RIGHT;

	}*/
	//if (x > _endPos) {
	//	nx = DIRECTION::LEFT;

	//}
	//if (x < _startPos) {
	//	nx = DIRECTION::RIGHT;

	//}


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
				if(vx > 0) vx = -PLATFORM_SPEED;
				else vx = PLATFORM_SPEED;
				
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
