#include "Bat.h"



void Bat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + BAT_BBOX_WIDTH;
	bottom = top + BAT_BBOX_HEIGHT;
}

void Bat::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
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
		if (pScene->GetSimon()->y - this->y < ACTIVE_BAT_X &&
			pScene->GetSimon()->x - this->x < ACTIVE_BAT_Y)
		{
			this->SetState(BATSTATE::FLY);
			
		}

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
			if (e->nx != 0)
				x += dx;
			else if (e->ny < 0)
				y += dy;
		}


	}

	// clean up collision events
	for (std::size_t i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Bat::Render()
{
	int ani = 0;
	switch (this->state)
	{
	case BATSTATE::IDLE:
		ani = BAT_ANI_IDLE;
		animations[ani]->Render(nx, x, y);
		break;
	case BATSTATE::FLY:
		ani = BAT_ANI_FLY;
		animations[ani]->Render(nx, x, y);
		break;
	default:
		break;
	};
	
}


void Bat::SetState(BATSTATE state)
{
	switch (state) {
	case BATSTATE::IDLE:
		vx = 0;
		vy = 0;
		break;
	case BATSTATE::FLY:
		vx = BAT_FLY_SPEED_X;
		if (y > oy) {
			vy = 0;
		}
		else
			vy = BAT_FLY_SPEED_Y;

		break;
	}
	this->state = state;
}

Bat::Bat() :Enemy()
{
	AddAnimation("PHANTOM_ANI_IDLE");
	AddAnimation("PHANTOM_ANI_FLY");
	this->hp = 1;
}
