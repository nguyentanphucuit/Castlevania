#include "Hunchback.h"
#include "Debug.h"
#include "Ground.h"
#include "Simon.h"
#include "debug.h"


void Hunchback::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + HUNCHBACK_BBOX_WIDTH;
	bottom = top + HUNCHBACK_BBOX_HEIGHT;
}

void Hunchback::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{

	//	if (reSpawn) return;
		//DebugOut(L"update \n");
	CGameObject::Update(dt, scene);
	if (this->isMotionless)
	{
		return;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	vy += HUNCHBACK_GRAVITY * dt;
	
	//DebugOut(L"y %d\n", y);
	

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		if (pScene->GetSimon()->x - this->x < ACTIVE_HUNCHBACK_X && !waitTimeActive)
		{
			waitTimeActive = GetTickCount();
			
		}
		if (x > pScene->GetSimon()->x + HUNCHBACK_BBOX_WIDTH*3 ) {
			nx = DIRECTION::LEFT;
		}
		if (x < pScene->GetSimon()->x - HUNCHBACK_BBOX_WIDTH*3 ) {
			nx = DIRECTION::RIGHT;
		}
		if (GetTickCount() - waitTimeActive > TIME_ACTIVE)
			this->SetState(HUNCHBACK::JUMP);
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
				if (jump) {
					int jumpRank = rand() % (2 - 1 + 1) + 1;
					if (jumpRank == 1)
					{
						vy = 0;
					}
					else
					{
						float minvy = -0.20;
						float maxvy = -0.40;
						vy = minvy + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxvy - minvy)));
					}
					float minvx = -0.30;
					float maxvx = 0.30;
					vx = minvx + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxvx - minvx)));
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
}

void Hunchback::Render()
{

	int ani = 0;
	switch (this->state)
	{
	case HUNCHBACK::READY:
		ani = HUNCHBACK_ANI_READY;
		animations[ani]->Render(nx, x, y);
		break;
	case HUNCHBACK::JUMP:
		ani = HUNCHBACK_ANI_JUMP;
		animations[ani]->Render(nx, x, y);
		break;
	default:
		break;
	};

}

void Hunchback::OnTouchingGround()
{
	vy -= .4;
}

void Hunchback::Num(int num)
{
	this->_num = num;
}

void Hunchback::SetState(HUNCHBACK state)
{
	switch (state) {
	case HUNCHBACK::READY:
		vx = 0;
		break;
	case HUNCHBACK::JUMP:
		if (nx == DIRECTION::RIGHT) {
			vx = HUNCHBACK_WALKING_SPEED;
		}
		else if (nx == DIRECTION::LEFT) {
			vx = -HUNCHBACK_WALKING_SPEED;
		}
		jump = true;
		break;
		
	}
	this->state = state;
}

Hunchback::Hunchback() :Enemy()
{
	AddAnimation("HUNCHBACK_ANI_JUMP");
	AddAnimation("HUNCHBACK_ANI_JUMP");
	this->hp = 1;
	this->isMotionless = false;
	this->score = 500;
}

