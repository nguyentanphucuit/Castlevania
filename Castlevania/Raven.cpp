#include "Raven.h"
#include "Debug.h"
#include "Ground.h"
#include "Simon.h"


void Raven::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y + 2;
	right = left + RAVEN_BBOX_WIDTH;
	bottom = top + RAVEN_BBOX_HEIGHT - 2;
}

void Raven::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
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

	//DebugOut(L"y %d\n", y);

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		if (this->x - pScene->GetSimon()->x < ACTIVE_RAVEN_X)
		{
			this->SetState(RAVENSTATE::FLY);
		}
		if (x > pScene->GetSimon()->x + _endPos) {
			nx = DIRECTION::LEFT;
		}
		if (x < pScene->GetSimon()->x - _startPos) {
			nx = DIRECTION::RIGHT;
		}
			
	}

	if (fly) {
		int jumpRank = rand() % (2 - 1 + 1) + 1;
		if (jumpRank == 1)
		{
			vy = 0;
		}
		else
		{
			float minvy = -0.40;
			float maxvy = -0.60;
			vy = minvy + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxvy - minvy)));
		}
		float minvx = -0.20;
		float maxvx = 0.20;
		vx = minvx + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxvx - minvx)));
	}

	
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Raven::Render()
{
	int ani = 0;
	switch (this->state)
	{
	case RAVENSTATE::IDLE:
		ani = RAVEN_ANI_IDLE;
		animations[ani]->Render(nx = DIRECTION::LEFT, x, y);
		break;
	case RAVENSTATE::FLY:
		ani = RAVEN_ANI_FLY;
		animations[ani]->Render(nx = DIRECTION::LEFT, x, y);
		break;
	default:
		break;
	};
}

void Raven::Area(int startPos, int endPos)
{
	this->_endPos = endPos;
	this->_startPos = startPos;
}

void Raven::SetState(RAVENSTATE state)
{
	switch (state) {
	case RAVENSTATE::IDLE:
		vx = 0;
		break;
	case RAVENSTATE::FLY:
		if (nx == DIRECTION::RIGHT) {
			vx = RAVEN_FLY_SPEED;
		}
		else if (nx == DIRECTION::LEFT) {
			vx = -RAVEN_FLY_SPEED;
		}
		fly = true;
		break;

	}
	this->state = state;
}

Raven::Raven() :Enemy()
{
	AddAnimation("RAVEN_ANI_IDLE");
	AddAnimation("RAVEN_ANI_FLY");
}

