#include "White.h"
#include "Debug.h"
#include "Ground.h"
#include "Simon.h"
#include "WeaponFactory.h"


void White::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y + 2;
	right = left + WHITE_BBOX_WIDTH;
	bottom = top + WHITE_BBOX_HEIGHT - 2;
}

void White::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
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

	vy += WHITE_GRAVITY * dt;
	/*if (nx == DIRECTION::RIGHT) vx = WHITE_WALKING_SPEED;
	else if (nx == DIRECTION::LEFT) vx = -WHITE_WALKING_SPEED;*/

	/*if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if ((pScene->GetSimon()->x - x < WHITE_BBOX_WIDTH * 4) && (pScene->GetSimon()->y - y) < 1 && x < _endPos - WHITE_BBOX_WIDTH) {
			if (nx == DIRECTION::LEFT) {
				nx = DIRECTION::RIGHT;
			}

			vx = WHITE_WALKING_SPEED * 1.5;
		}


	}

	if (x > _endPos) {
		nx = DIRECTION::LEFT;

	}
	if (x < _startPos) {
		nx = DIRECTION::RIGHT;

	}*/

	auto weapon = WeaponFactory::SpawnWeapon<Weapon*>(EWeapon::SKELETON);
	
	if (numWeapon  < 3 && GetTickCount() - timeSpawn > 450) {
		timeSpawn = GetTickCount();
		weapon->SetPosition(this->x, this->y + 10);
		weapon->SetNx(this->nx);
		if (dynamic_cast<PlayScene*>(scene)) {
			PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
			pScene->SpawnObject(weapon);
		}
		numWeapon++;
	}
	if (weapon->isDestroy)
	{
		this->isSpawnWeapon = false;
		numWeapon--;
	}


	DebugOut(L"spawnWeapon %d \n", isSpawnWeapon);

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
				//vy -= .4;
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

void White::Render()
{

	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void White::Area(int startPos, int endPos)
{
	this->_endPos = endPos;
	this->_startPos = startPos;
}

//void White::SetisSpawnWeapon()
//{
//	if (GetTickCount() - this->timespawnWeapon > TIME_SPAWN_WEAPON && this->timespawnWeapon != 0)
//	{
//		this->spawnweapon = false;
//	}
//}

White::White() :Enemy()
{
	AddAnimation("WHITE_ANI_JUMP");

}

