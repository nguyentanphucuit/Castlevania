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

	vy += RAVEN_GRAVITY * dt;
	if (nx == DIRECTION::RIGHT) vx = RAVEN_FLY_SPEED;
	else if (nx == DIRECTION::LEFT) vx = -RAVEN_FLY_SPEED;

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if ((pScene->GetSimon()->x - x < RAVEN_BBOX_WIDTH * 4) && (pScene->GetSimon()->y - y) < 1 && x < _endPos - RAVEN_BBOX_WIDTH) {
			if (nx == DIRECTION::LEFT) {
				nx = DIRECTION::RIGHT;
			}

			vx = RAVEN_FLY_SPEED * 1.5;
		}


	}
	if (x > _endPos) {
		nx = DIRECTION::LEFT;

	}
	if (x < _startPos) {
		nx = DIRECTION::RIGHT;

	}

	if (coEvents.size() == 0)
	{
		x += dx;
		y = RAVEN_OY_HEIGHT * sin(x * RAVEN_FLY_SPEED_Y) + oy;
	}
	else
	{
		x += dx;
		y = RAVEN_OY_HEIGHT * sin(x * RAVEN_FLY_SPEED_Y) + oy;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Raven::Render()
{

	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void Raven::Area(int startPos, int endPos)
{
	this->_endPos = endPos;
	this->_startPos = startPos;
}

Raven::Raven() :Enemy()
{
	AddAnimation("RAVEN_ANI_FLY");

}

