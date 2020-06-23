#include "Bone.h"
#include "Enemy.h"
#include "Brick.h"
#include "Torch.h"
#include "Candle.h"
#include "EffectFactory.h"
#include "Simon.h"

void Bone::Render()
{
	animations[0]->Render(nx, x, y);
}

void Bone::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{

	if (this->isDestroy)
	{
		return;
	}
	if (nx == DIRECTION::RIGHT)
	{
		this->vx = AXE_SPEED_VX;
	}
	else if (nx == DIRECTION::LEFT) {
		this->vx = -AXE_SPEED_VX;
	}
	x += dx;
	y += dy;
	vy += AXE_GRAVITY * dt;
	CGameObject::Update(dt, scene);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

}

void Bone::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + AXE_BBOX_WIDTH;
	b = y + AXE_BBOX_HEIGHT;
}

Bone::Bone() :Enemy()
{
	AddAnimation("BONE_ANI_WHITE");
	this->vx = AXE_SPEED_VX;
	this->vy = -AXE_SPEED_VY;
}
