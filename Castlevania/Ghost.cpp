#include "Ghost.h"
#include "Debug.h"
#include "Ground.h"
#include "Simon.h"


void Ghost::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y + 2;
	right = left + GHOST_BBOX_WIDTH;
	bottom = top + GHOST_BBOX_HEIGHT - 2;
}

void Ghost::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
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
	vy += GHOST_GRAVITY * dt;
	if (nx == DIRECTION::RIGHT) vx = GHOST_FLY_SPEED;
	else if (nx == DIRECTION::LEFT) vx = -GHOST_FLY_SPEED;

	if (x > _endPos) {
		nx = DIRECTION::LEFT;

	}
	if (x < _startPos) {
		nx = DIRECTION::RIGHT;

	}

	if (coEvents.size() == 0)
	{
		x += dx;
		y = GHOST_OY_HEIGHT * sin(x * GHOST_FLY_SPEED_Y) + oy;
	}
	else
	{
		x += dx;
		y = GHOST_OY_HEIGHT * sin(x * GHOST_FLY_SPEED_Y) + oy;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Ghost::Render()
{

	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void Ghost::Area(int startPos, int endPos)
{
	this->_endPos = endPos;
	this->_startPos = startPos;
}

Ghost::Ghost() :Enemy()
{
	AddAnimation("GHOST_ANI_FLY");

}

