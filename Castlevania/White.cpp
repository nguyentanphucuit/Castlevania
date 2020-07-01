#include "White.h"
#include "Debug.h"
#include "Ground.h"
#include "Simon.h"
#include "WeaponFactory.h"
#include "EnemyFactory.h"


void White::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y + 2;
	right = left + WHITE_BBOX_WIDTH;
	bottom = top + WHITE_BBOX_HEIGHT - 2;
}

void White::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt, scene);
	if (this->isMotionless)
	{
		return;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	vy += WHITE_GRAVITY * dt;

	auto enemy = EnemyFactory::SpawnEnemy<Enemy*>(CEnemy::BONE);

	if (numWeapon  < 3 && GetTickCount() - timeSpawn > TIME_WAIT) {
		timeSpawn = GetTickCount();
		enemy->SetPosition(this->x, this->y + NEARLY_WEAPON);
		enemy->SetNx(this->nx);
		if (dynamic_cast<PlayScene*>(scene)) {
			PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
			pScene->SpawnObject(enemy);
		}
		numWeapon++;
	}
	if (numWeapon == 3) {
		if (loadTimeSpawn ==0)
		{
			loadTimeSpawn = GetTickCount();
		}
		
	}
	if (loadTimeSpawn!=0 && GetTickCount()-loadTimeSpawn> TIME_WAIT_BONE){
		loadTimeSpawn = 0;
		numWeapon = 0;
	}

	if (dynamic_cast<PlayScene*>(scene) && !this->isJump) {
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		if (x > pScene->GetSimon()->x) {
			if (x > pScene->GetSimon()->x + DISTANCE_FAR_SIMON + DISTANCE_WALKING_FAR_SIMON) {
				vx = -WHITE_WALKING_SPEED;
				nx = DIRECTION::LEFT;
			}
			else if (x < pScene->GetSimon()->x + DISTANCE_FAR_SIMON) {
				vx = WHITE_WALKING_SPEED;
				nx = DIRECTION::LEFT;
			}
		}
		else {
			if (x < pScene->GetSimon()->x - DISTANCE_FAR_SIMON - DISTANCE_WALKING_FAR_SIMON) {
				vx = WHITE_WALKING_SPEED;
				nx = DIRECTION::RIGHT;
			}
			else if (x > pScene->GetSimon()->x - DISTANCE_FAR_SIMON) {
				vx = -WHITE_WALKING_SPEED;
				nx = DIRECTION::RIGHT;
			}
		}
		
		if (x > 120 && x < 200 || x > 630 && x < 710 || x > 1080 && x < 1220) {
			if(isJumpRight)	this->SetState(WHITESTATE::JUPM);
			else this->SetState(WHITESTATE::JUPMBACK);
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
			if (dynamic_cast<Ground*>(e->obj)) {
				float gl, gt, gr, gb;
				e->obj->GetBoundingBox(gl, gt, gr, gb);
				if (x > gr) {
					isJumpRight = true;
				}else if(x < gr && x + WHITE_BBOX_WIDTH*2 < gr)
					isJumpRight = false;
				

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
				this->isJump = false;
			}
			else {
				if (e->nx != 0)
					x += dx;
				else if (e->ny < 0) {
					y += dy;
				}

			}
			DebugOut(L"e->nx %d\n", e->nx);
			DebugOut(L"e->ny %d\n", e->ny);
		}

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void White::Render()
{
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}

void White::SetState(WHITESTATE state)
{
	switch (state) {
	case WHITESTATE::WALKING:
		
		break;
	case WHITESTATE::JUPM:
		vx = WHITE_WALKING_SPEED;
		vy = -.5;
		this->isJump = true;
		break;
	case WHITESTATE::JUPMBACK:
		vx = -WHITE_WALKING_SPEED*2;
		vy = -.4;
		this->isJump = true;
		break;
	}
	this->state = state;
}
White::White() :Enemy()
{
	AddAnimation("WHITE_ANI_JUMP");
	this->isMotionless = false;
}

