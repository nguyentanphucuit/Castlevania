#include "Raven.h"
#include "Debug.h"
#include "Ground.h"
#include "Simon.h"
#include "EffectFactory.h"


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
	if (this->isMotionless)
	{
		return;
	}
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
		if ((this->x - pScene->GetSimon()->x < ACTIVE_RAVEN_X)
			&& GetTickCount() - waitTimeFly > WAIT_TIME)
		{
			this->SetState(RAVENSTATE::FLY);
			waitTimeFly = 0;
		}
		float left, top,right, bottom;
		pScene->GetSimon()->GetBoundingBox(left, top, right, bottom);
		if (CGameObject::AABB(left, top, right, bottom, this->x, this->y, this->x + RAVEN_BBOX_WIDTH, this->y + RAVEN_BBOX_HEIGHT))
		{
			auto effect = EffectFactory::SpawnEffect<Effect*>(CEffect::STAR);
			if (dynamic_cast<PlayScene*>(scene)) {
				PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
				effect->SetPosition(x + DISTANCE_DIE, y);
				pScene->SpawnObject(effect);
			}
			this->isDestroy = true;
		}
			
		if (x > pScene->GetSimon()->x + _startPos) {
			nx = DIRECTION::LEFT;
			this->SetState(RAVENSTATE::IDLE);
			if (waitTimeFly == 0)
				waitTimeFly = GetTickCount();
		}

		if (x < pScene->GetSimon()->x - _endPos) {
			nx = DIRECTION::RIGHT;
			this->SetState(RAVENSTATE::IDLE);
			if (waitTimeFly == 0)
				waitTimeFly = GetTickCount();
		}

		if (y > pScene->GetSimon()->y) {
			fly_straight = true;
		}
		else
			fly_straight = false;
			
	}
	if (!fly) {
		_y = y;
	}
	
	if (fly && y - _y < MAX_DISTANCE_Y) {
		if (!fly_straight)
			vy = RAVEN_FLY_SPEED;
		else {
			vy = 0;
			x += dx;
		}
	}
	else {
		this->SetState(RAVENSTATE::IDLE);
		if(waitTimeFly == 0)
			waitTimeFly = GetTickCount();
	}
	
	

	x += dx;
	y += dy;
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Raven::Render()
{
	int ani = 0;
	switch (this->state)
	{
	case RAVENSTATE::IDLE:
		ani = RAVEN_ANI_IDLE;
		animations[ani]->Render(nx, x, y);
		break;
	case RAVENSTATE::FLY:
		ani = RAVEN_ANI_FLY;
		animations[ani]->Render(nx, x, y);
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
		vy = 0;
		fly = false;
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

