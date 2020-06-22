#include "BlackKnight.h"
#include "Debug.h"
#include "Ground.h"
#include "Simon.h"


void BlackKnight::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + BLACKKNIGHT_BBOX_WIDTH;
	bottom = top + BLACKKNIGHT_BBOX_HEIGHT;
}

void BlackKnight::Update(DWORD dt, Scene* scene , vector<LPGAMEOBJECT>* coObjects)
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

	vy += BLACKKNIGHT_GRAVITY * dt;
	if (nx == DIRECTION::RIGHT) vx = BLACKKNIGHT_WALKING_SPEED;
	else if (nx == DIRECTION::LEFT) vx = -BLACKKNIGHT_WALKING_SPEED;

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();
		auto xSimon = pScene->GetSimon()->x;

		if (pScene->GetSimon()->y <= y && ((xSimon - x > DISTANCE) || (x - xSimon > DISTANCE)) && !pScene->GetSimon()->Untouch()) {
			if ((pScene->GetSimon()->x - x < BLACKKNIGHT_BBOX_WIDTH * 4) && x < _endPos - BLACKKNIGHT_BBOX_WIDTH && pScene->GetSimon()->x - x>0) {
				if (nx == DIRECTION::LEFT) {
					nx = DIRECTION::RIGHT;
				}

				vx = BLACKKNIGHT_WALKING_SPEED * 1.5;
			}
			if ((pScene->GetSimon()->x + BLACKKNIGHT_BBOX_WIDTH * 4 > x) && x > _startPos + BLACKKNIGHT_BBOX_WIDTH && pScene->GetSimon()->x - x < 0) {
				if (nx == DIRECTION::RIGHT) {
					nx = DIRECTION::LEFT;
				}

				vx = -BLACKKNIGHT_WALKING_SPEED * 1.5;
			}
			/*DebugOut(L"xSimon %f\n", xSimon);
			DebugOut(L"x %f\n", x);*/
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

void BlackKnight::Render()
{

	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void BlackKnight::Area(int startPos, int endPos)
{
	this->_endPos = endPos;
	this->_startPos = startPos;
}

BlackKnight::BlackKnight() :Enemy()
{
	AddAnimation("BLACKKNIGHT_ANI_WALK");
	this->hp = 2;
}

