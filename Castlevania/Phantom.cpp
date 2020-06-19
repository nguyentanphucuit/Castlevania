#include "Phantom.h"



void Phantom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + PHANTOM_BBOX_WIDTH;
	bottom = top + PHANTOM_BBOX_HEIGHT;
}

void Phantom::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, scene);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		oy = pScene->GetSimon()->y;
		if (this->x - pScene->GetSimon()->x < ACTIVE_PHANTOM_Y)
		{
			this->SetState(PHANTOMSTATE::FLY);

		}

	}

	if (coEvents.size() == 0)
	{
		x -= dx;
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
			if (e->nx != 0)
				x += dx;
			else if (e->ny < 0)
				y += dy;
		}


	}

	// clean up collision events
	for (std::size_t i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Phantom::Render()
{
	int ani = 0;
	switch (this->state)
	{
	case PHANTOMSTATE::IDLE:
		ani = PHANTOM_ANI_IDLE;
		animations[ani]->Render(nx, x, y);
		break;
	case PHANTOMSTATE::FLY:
		ani = PHANTOM_ANI_FLY;
		animations[ani]->Render(nx, x, y);
		break;
	default:
		break;
	};

}


void Phantom::SetState(PHANTOMSTATE state)
{
	switch (state) {
	case PHANTOMSTATE::IDLE:
		vx = 0;
		vy = 0;
		break;
	case PHANTOMSTATE::FLY:
		vx = PHANTOM_FLY_SPEED_X;
		if (y > oy) {
			vy = 0;
		}
		else
			vy = PHANTOM_FLY_SPEED_Y;

		break;
	}
	this->state = state;
}

Phantom::Phantom() :Enemy()
{
	AddAnimation("PHANTOM_ANI_IDLE");
	AddAnimation("PHANTOM_ANI_FLY");
	this->hp = 1;
}
