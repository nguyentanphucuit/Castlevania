#include "Item.h"
#include "Ground.h"

void Item::Render()
{
}

void Item::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDestroy) {
		return;
	}

	if (time_wait != 0 && GetTickCount() - time_wait > ITEM_HIDING) {
		time_wait = 0;
	}
	
	if (time_wait) {
		return;
	}

	CGameObject::Update(dt, scene);
	vy += ITEM_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		if (ny < 0)
			y += min_ty * dy + ny * 0.4f;

		for (UINT i = 0; i < coEventsResult.size(); i++) {
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground*>(e->obj)) {
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
			else {
				if (e->nx != 0)
					x += dx;
				else if (e->ny !=0) {
					y += dy;
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

